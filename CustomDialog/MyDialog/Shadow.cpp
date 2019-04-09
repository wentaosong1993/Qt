
#include "Shadow.h"

#include <assert.h>

const char *strWndClassName = "JPShadowWnd";
CShadow::pfnUpdateLayeredWindow CShadow::s_UpdateLayeredWindow = NULL;
HINSTANCE CShadow::s_hInstance = (HINSTANCE)INVALID_HANDLE_VALUE;
typedef struct HWNDSHADOW
{
	HWND hWnd;
	CShadow *pWndShadow;
} HwndShadow;

CValArray CShadow::s_ShadowArray(sizeof(HwndShadow), 10);

CValArray::CValArray(int iElementSize, int iPreallocSize):
	m_pVoid(nullptr),
	m_nCount(0),
	m_iElementSize(iElementSize),
	m_nAllocated(iPreallocSize)
{
	assert(iElementSize > 0);
	assert(iPreallocSize >= 0);
	if (iPreallocSize > 0)
	{
		m_pVoid = static_cast<LPBYTE>(malloc(iElementSize*iPreallocSize));
	}
}

CValArray::~CValArray()
{
	if (m_pVoid)
	{
		free(m_pVoid);
	}
}

void CValArray::Empty()
{
	m_nCount = 0;
}

bool CValArray::IsEmpty() const
{
	return m_nCount == 0;
}

bool CValArray::Add(LPCVOID pData)
{
	if (++m_nCount >= m_nAllocated)
	{
		int nAllocated = m_nAllocated * 2;
		if (nAllocated == 0)
			nAllocated = 11;
		LPBYTE pVoid = static_cast<LPBYTE>(realloc(m_pVoid, nAllocated*m_iElementSize));
		if (pVoid)
		{
			m_nAllocated = nAllocated;
			m_pVoid = pVoid;
		}
		else
		{
			--m_nCount;
			return false;
		}
	}
	::CopyMemory(m_pVoid + ((m_nCount - 1)*m_iElementSize), pData, m_iElementSize);
	return true;
}

bool CValArray::Remove(int iIndex, int iCount)
{
	if (iIndex<0 || iCount <= 0 || iIndex + iCount >m_nCount)
		return false;
	if (iIndex + iCount < m_nCount)
	{
		::CopyMemory(m_pVoid + (iIndex*m_iElementSize), m_pVoid + (iIndex + iCount)*m_iElementSize,(m_nCount-iIndex-iCount)*m_iElementSize);
	}
	m_nCount -= iCount;
	return true;
}

int CValArray::GetSize() const
{
	return m_nCount;
}

LPVOID CValArray::GetData()
{
	return static_cast<LPVOID>(m_pVoid);
}

LPVOID CValArray::GetAt(int iIndex) const
{
	if (iIndex < 0 || iIndex >= m_nCount)
		return nullptr;
	return m_pVoid + iIndex*m_iElementSize;
}

LPVOID CValArray::operator[](int nIndex) const
{
	assert(nIndex >= 0 && nIndex < m_nCount);
	return m_pVoid + (nIndex * m_iElementSize);
}

CShadow::CShadow():
	m_hWnd((HWND)INVALID_HANDLE_VALUE),
	m_OriParentProc(NULL),
	m_nDarkness(150),
	m_nSharpness(5),
	m_nSize(0),
	m_nxOffset(5),
	m_nyOffset(5),
	m_Color(RGB(0,0,0)),
	m_pImageInfo(NULL),
	m_WndSize(0),
	m_bUpdate(false)
{
	::ZeroMemory(&m_rcCorner, sizeof(m_rcCorner));
}


CShadow::~CShadow()
{
	if (::IsWindow(m_hWnd))
		PostMessageA(m_hWnd, WM_CLOSE, (WPARAM)0, 0L);
	if (m_pImageInfo)
	{
		//CRenderEngine::FreeImage(m_pImageInfo);
		//m_pImageInfo = NULL;
	}
}

bool CShadow::Initialize(HINSTANCE hInstance)
{
	if (s_UpdateLayeredWindow)
		return false;
	HMODULE hUser32 = GetModuleHandleA("USER32.DLL");
	s_UpdateLayeredWindow = (pfnUpdateLayeredWindow)GetProcAddress(hUser32, "UpdateLayeredWindow");
	if (!s_UpdateLayeredWindow)
		return false;

	s_hInstance = hInstance;
	WNDCLASSEXA wcex;
	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CShadow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = strWndClassName;
	wcex.hIconSm = NULL;

	RegisterClassExA(&wcex);
	return true;
}

HWND CShadow::GetHWND() const
{
	return m_hWnd;
}

CShadow::operator HWND() const
{
	return m_hWnd;
}

void CShadow::Create(HWND hParentWnd)
{
	if (!s_UpdateLayeredWindow)
		return;

	assert(s_UpdateLayeredWindow != INVALID_HANDLE_VALUE);
	assert(FindShadowWindow(hParentWnd) == NULL);
	HwndShadow hs = { hParentWnd,this };
	s_ShadowArray.Add(&hs);
	m_hWnd = CreateWindowExA(WS_EX_LAYERED | WS_EX_TRANSPARENT, strWndClassName, NULL,
		WS_POPUPWINDOW, CW_USEDEFAULT, 0, 0, 0, hParentWnd, NULL, s_hInstance, NULL);

	LONG lParentStyle = GetWindowLong(hParentWnd, GWL_STYLE);

	if (!(WS_VISIBLE&lParentStyle))
		m_Status = SS_ENABLED;
	else  if ((WS_MAXIMIZE | WS_MAXIMIZE)&lParentStyle)
		m_Status = SS_ENABLED | SS_PARENTVISIBLE;
	else
	{
		m_Status = SS_ENABLED | SS_VISABLE | SS_PARENTVISIBLE;
		::ShowWindow(m_hWnd, SW_SHOWNA);
		Update(hParentWnd);
	}

	m_OriParentProc = (WNDPROC)GetWindowLongPtr(hParentWnd, GWLP_WNDPROC);
#pragma warning(disable: 4311)	// temporrarily disable the type_cast warning in Win32
	SetWindowLongPtr(hParentWnd, GWLP_WNDPROC, (LONG_PTR)ParentProc);
#pragma warning(default: 4311)
}

bool CShadow::SetImage(LPCTSTR image, RECT rcCorner, RECT rcHoleOffset)
{
	//TImageInfo* pImageInfo = CRenderEngine::LoadImage(image);
	//if (pImageInfo == NULL) return false;

	//if (m_pImageInfo) 
	//	CRenderEngine::FreeImage(m_pImageInfo);
	//m_pImageInfo = pImageInfo;
	//m_rcCorner = rcCorner;
	//m_rcHoleOffset = rcHoleOffset;

	//if (SS_VISABLE & m_Status)
	//	Update(GetParent(m_hWnd));
	return true;
}

bool CShadow::SetSize(int NewSize)
{
	m_nSize = (signed char)NewSize;
	if (SS_VISABLE & m_Status)
		Update(GetParent(m_hWnd));
	return true;
}

bool CShadow::SetSharpness(unsigned int NewSharpness)
{
	if (NewSharpness > 20)
		return false;

	m_nSharpness = (unsigned char)NewSharpness;
	if (SS_VISABLE & m_Status)
		Update(GetParent(m_hWnd));
	return true;
}

bool CShadow::SetDarkness(unsigned int NewDarkness)
{
	if (NewDarkness > 255)
		return false;

	m_nDarkness = (unsigned char)NewDarkness;
	if (SS_VISABLE & m_Status)
		Update(GetParent(m_hWnd));
	return true;
}

bool CShadow::SetPosition(int NewXOffset, int NewYOffset)
{
	if (NewXOffset > 20 || NewXOffset < -20 ||
		NewYOffset > 20 || NewYOffset < -20)
		return false;

	m_nxOffset = (signed char)NewXOffset;
	m_nyOffset = (signed char)NewYOffset;
	if (SS_VISABLE & m_Status)
		Update(GetParent(m_hWnd));
	return true;
}

bool CShadow::SetColor(COLORREF NewColor)
{
	m_Color = NewColor;
	if (SS_VISABLE & m_Status)
		Update(GetParent(m_hWnd));
	return true;
}

LRESULT CShadow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CShadow* pThis = NULL;
	if (uMsg == WM_MOUSEACTIVATE) return MA_NOACTIVATE;
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CShadow::ParentProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CShadow *pThis = FindShadowWindow(hWnd);
	_ASSERT(pThis);

	switch (uMsg)
	{
	case WM_MOVE:
		if (pThis->m_Status & SS_VISABLE)
		{
			RECT WndRect;
			GetWindowRect(hWnd, &WndRect);
			//if (pThis->m_pImageInfo)
			//{
			//	SetWindowPos(pThis->m_hWnd, NULL,
			//		WndRect.left - pThis->m_rcCorner.left, WndRect.top - pThis->m_rcCorner.top,
			//		0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

			//}
			//else
			{
				SetWindowPos(pThis->m_hWnd, NULL,
					WndRect.left + pThis->m_nxOffset - pThis->m_nSize, WndRect.top + pThis->m_nyOffset - pThis->m_nSize,
					0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
			}
		}
		break;

	case WM_SIZE:
		if (pThis->m_Status & SS_ENABLED)
		{
			if (SIZE_MAXIMIZED == wParam || SIZE_MINIMIZED == wParam)
			{
				::ShowWindow(pThis->m_hWnd, SW_HIDE);
				pThis->m_Status &= ~SS_VISABLE;
			}
			else if (pThis->m_Status & SS_PARENTVISIBLE)	// Parent maybe resized even if invisible
			{
				// Awful! It seems that if the window size was not decreased
				// the window region would never be updated until WM_PAINT was sent.
				// So do not Update() until next WM_PAINT is received in this case
				if (LOWORD(lParam) > LOWORD(pThis->m_WndSize) || HIWORD(lParam) > HIWORD(pThis->m_WndSize))
					pThis->m_bUpdate = true;
				else
					pThis->Update(hWnd);
				if (!(pThis->m_Status & SS_VISABLE))
				{
					::ShowWindow(pThis->m_hWnd, SW_SHOWNA);
					pThis->m_Status |= SS_VISABLE;
				}
			}
			pThis->m_WndSize = lParam;
		}
		break;

	case WM_PAINT:
	{
		if (pThis->m_bUpdate)
		{
			pThis->Update(hWnd);
			pThis->m_bUpdate = false;
		}
		//return hr;
		break;
	}

	// In some cases of sizing, the up-right corner of the parent window region would not be properly updated
	// Update() again when sizing is finished
	case WM_EXITSIZEMOVE:
		if (pThis->m_Status & SS_VISABLE)
		{
			pThis->Update(hWnd);
		}
		break;

	case WM_SHOWWINDOW:
		if (pThis->m_Status & SS_ENABLED)
		{
			if (!wParam)	// the window is being hidden
			{
				::ShowWindow(pThis->m_hWnd, SW_HIDE);
				pThis->m_Status &= ~(SS_VISABLE | SS_PARENTVISIBLE);
			}
			else if (!(pThis->m_Status & SS_PARENTVISIBLE))
			{
				//pThis->Update(hwnd);
				pThis->m_bUpdate = true;
				::ShowWindow(pThis->m_hWnd, SW_SHOWNA);
				pThis->m_Status |= SS_VISABLE | SS_PARENTVISIBLE;
			}
		}
		break;

	case WM_DESTROY:
		DestroyWindow(pThis->m_hWnd);	// Destroy the shadow
		break;

	case WM_NCDESTROY:
	{
		int iIndex = GetShadowWindowIndex(hWnd);
		if (iIndex >= 0) s_ShadowArray.Remove(iIndex);
	}
	break;
	}


#pragma warning(disable: 4312)	// temporrarily disable the type_cast warning in Win32
	// Call the default(original) window procedure for other messages or messages processed but not returned
	return ((WNDPROC)pThis->m_OriParentProc)(hWnd, uMsg, wParam, lParam);
#pragma warning(default: 4312)

}

CShadow * CShadow::FindShadowWindow(HWND hWnd)
{
	for (int i = 0; i < s_ShadowArray.GetSize(); ++i)
	{
		HwndShadow* hwndShadow = (HwndShadow*)s_ShadowArray[i];
		if (hwndShadow->hWnd == hWnd) return hwndShadow->pWndShadow;
	}
	return NULL;
}

int CShadow::GetShadowWindowIndex(HWND hWnd)
{
	for (int i = 0; i < s_ShadowArray.GetSize(); ++i)
	{
		HwndShadow* hwndShadow = (HwndShadow*)s_ShadowArray[i];
		if (hwndShadow->hWnd == hWnd) return i;
	}
	return -1;
}

void CShadow::Update(HWND hParent)
{
	//int ShadSize = 5;
	//int Multi = 100 / ShadSize;

	RECT WndRect;
	GetWindowRect(hParent, &WndRect);
	int nShadWndWid = WndRect.right - WndRect.left + m_nSize * 2;
	int nShadWndHei = WndRect.bottom - WndRect.top + m_nSize * 2;
	//if (m_pImageInfo)
	//{
	//	nShadWndWid = WndRect.right - WndRect.left + m_rcCorner.left + m_rcCorner.right;
	//	nShadWndHei = WndRect.bottom - WndRect.top + m_rcCorner.top + m_rcCorner.bottom;
	//}

	// Create the alpha blending bitmap
	BITMAPINFO bmi;        // bitmap header

	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = nShadWndWid;
	bmi.bmiHeader.biHeight = nShadWndHei;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = nShadWndWid * nShadWndHei * 4;
	BYTE *pvBits;          // pointer to DIB section
	HBITMAP hbitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pvBits, NULL, 0);
	ZeroMemory(pvBits, bmi.bmiHeader.biSizeImage);

	HDC hMemDC = CreateCompatibleDC(NULL);
	HBITMAP hOriBmp = NULL;
	//if (m_pImageInfo)
	//{
	//	hOriBmp = (HBITMAP)SelectObject(hMemDC, hbitmap);
	//	RECT rc = { 0, 0, nShadWndWid, nShadWndHei };
	//	RECT rcBmpPart = { 0, 0, m_pImageInfo->nX, m_pImageInfo->nY };
	//	RECT rcCorner = { m_rcCorner.left + m_rcHoleOffset.left, m_rcCorner.top + m_rcHoleOffset.top,
	//		m_rcCorner.right + m_rcHoleOffset.right, m_rcCorner.bottom + m_rcHoleOffset.bottom };
	//	CRenderEngine::DrawImage(hMemDC, m_pImageInfo->hBitmap, rc, rc, rcBmpPart, rcCorner, true, 255, true);
	//}
	//else
	{
		MakeShadow((UINT32 *)pvBits, hParent, &WndRect);
		hOriBmp = (HBITMAP)SelectObject(hMemDC, hbitmap);
	}

	POINT ptDst = { WndRect.left + m_nxOffset - m_nSize, WndRect.top + m_nyOffset - m_nSize };
	//if (m_pImageInfo)
	//{
	//	ptDst.x = WndRect.left - m_rcCorner.left;
	//	ptDst.y = WndRect.top - m_rcCorner.top;
	//}
	POINT ptSrc = { 0, 0 };
	SIZE WndSize = { nShadWndWid, nShadWndHei };
	BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

	MoveWindow(m_hWnd, ptDst.x, ptDst.y, nShadWndWid, nShadWndHei, FALSE);

	BOOL bRet = s_UpdateLayeredWindow(m_hWnd, NULL, &ptDst, &WndSize, hMemDC,
		&ptSrc, 0, &blendPixelFunction, ULW_ALPHA);

	_ASSERT(bRet); // something was wrong....

				   // Delete used resources
	if (hOriBmp) SelectObject(hMemDC, hOriBmp);
	if (hbitmap) DeleteObject(hbitmap);
	DeleteDC(hMemDC);
}

void CShadow::MakeShadow(UINT32 * pShadBits, HWND hParent, RECT * rcParent)
{
	// The shadow algorithm:
	// Get the region of parent window,
	// Apply morphologic erosion to shrink it into the size (ShadowWndSize - Sharpness)
	// Apply modified (with blur effect) morphologic dilation to make the blurred border
	// The algorithm is optimized by assuming parent window is just "one piece" and without "wholes" on it

	// Get the region of parent window,
	HRGN hParentRgn = CreateRectRgn(0, 0, rcParent->right - rcParent->left, rcParent->bottom - rcParent->top);
	GetWindowRgn(hParent, hParentRgn);

	// Determine the Start and end point of each horizontal scan line
	SIZE szParent = { rcParent->right - rcParent->left, rcParent->bottom - rcParent->top };
	SIZE szShadow = { szParent.cx + 2 * m_nSize, szParent.cy + 2 * m_nSize };
	// Extra 2 lines (set to be empty) in ptAnchors are used in dilation
	int nAnchors = max(szParent.cy, szShadow.cy);	// # of anchor points pares
	int(*ptAnchors)[2] = new int[nAnchors + 2][2];
	int(*ptAnchorsOri)[2] = new int[szParent.cy][2];	// anchor points, will not modify during erosion
	ptAnchors[0][0] = szParent.cx;
	ptAnchors[0][1] = 0;
	ptAnchors[nAnchors + 1][0] = szParent.cx;
	ptAnchors[nAnchors + 1][1] = 0;
	if (m_nSize > 0)
	{
		// Put the parent window anchors at the center
		for (int i = 0; i < m_nSize; i++)
		{
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchors[i + 1][1] = 0;
			ptAnchors[szShadow.cy - i][0] = szParent.cx;
			ptAnchors[szShadow.cy - i][1] = 0;
		}
		ptAnchors += m_nSize;
	}
	for (int i = 0; i < szParent.cy; i++)
	{
		// find start point
		int j;
		for (j = 0; j < szParent.cx; j++)
		{
			if (PtInRegion(hParentRgn, j, i))
			{
				ptAnchors[i + 1][0] = j + m_nSize;
				ptAnchorsOri[i][0] = j;
				break;
			}
		}

		if (j >= szParent.cx)	// Start point not found
		{
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchorsOri[i][1] = 0;
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchorsOri[i][1] = 0;
		}
		else
		{
			// find end point
			for (j = szParent.cx - 1; j >= ptAnchors[i + 1][0]; j--)
			{
				if (PtInRegion(hParentRgn, j, i))
				{
					ptAnchors[i + 1][1] = j + 1 + m_nSize;
					ptAnchorsOri[i][1] = j + 1;
					break;
				}
			}
		}
	}

	if (m_nSize > 0)
		ptAnchors -= m_nSize;	// Restore pos of ptAnchors for erosion
	int(*ptAnchorsTmp)[2] = new int[nAnchors + 2][2];	// Store the result of erosion
														// First and last line should be empty
	ptAnchorsTmp[0][0] = szParent.cx;
	ptAnchorsTmp[0][1] = 0;
	ptAnchorsTmp[nAnchors + 1][0] = szParent.cx;
	ptAnchorsTmp[nAnchors + 1][1] = 0;
	int nEroTimes = 0;
	// morphologic erosion
	for (int i = 0; i < m_nSharpness - m_nSize; i++)
	{
		nEroTimes++;
		//ptAnchorsTmp[1][0] = szParent.cx;
		//ptAnchorsTmp[1][1] = 0;
		//ptAnchorsTmp[szParent.cy + 1][0] = szParent.cx;
		//ptAnchorsTmp[szParent.cy + 1][1] = 0;
		for (int j = 1; j < nAnchors + 1; j++)
		{
			ptAnchorsTmp[j][0] = max(ptAnchors[j - 1][0], max(ptAnchors[j][0], ptAnchors[j + 1][0])) + 1;
			ptAnchorsTmp[j][1] = min(ptAnchors[j - 1][1], min(ptAnchors[j][1], ptAnchors[j + 1][1])) - 1;
		}
		// Exchange ptAnchors and ptAnchorsTmp;
		int(*ptAnchorsXange)[2] = ptAnchorsTmp;
		ptAnchorsTmp = ptAnchors;
		ptAnchors = ptAnchorsXange;
	}

	// morphologic dilation
	ptAnchors += (m_nSize < 0 ? -m_nSize : 0) + 1;	// now coordinates in ptAnchors are same as in shadow window
													// Generate the kernel
	int nKernelSize = m_nSize > m_nSharpness ? m_nSize : m_nSharpness;
	int nCenterSize = m_nSize > m_nSharpness ? (m_nSize - m_nSharpness) : 0;
	UINT32 *pKernel = new UINT32[(2 * nKernelSize + 1) * (2 * nKernelSize + 1)];
	UINT32 *pKernelIter = pKernel;
	for (int i = 0; i <= 2 * nKernelSize; i++)
	{
		for (int j = 0; j <= 2 * nKernelSize; j++)
		{
			double dLength = sqrt((i - nKernelSize) * (i - nKernelSize) + (j - nKernelSize) * (double)(j - nKernelSize));
			if (dLength < nCenterSize)
				*pKernelIter = m_nDarkness << 24 | PreMultiply(m_Color, m_nDarkness);
			else if (dLength <= nKernelSize)
			{
				UINT32 nFactor = ((UINT32)((1 - (dLength - nCenterSize) / (m_nSharpness + 1)) * m_nDarkness));
				*pKernelIter = nFactor << 24 | PreMultiply(m_Color, nFactor);
			}
			else
				*pKernelIter = 0;
			//TRACE("%d ", *pKernelIter >> 24);
			pKernelIter++;
		}
		//TRACE("\n");
	}
	// Generate blurred border
	for (int i = nKernelSize; i < szShadow.cy - nKernelSize; i++)
	{
		int j;
		if (ptAnchors[i][0] < ptAnchors[i][1])
		{

			// Start of line
			for (j = ptAnchors[i][0];
				j < min(max(ptAnchors[i - 1][0], ptAnchors[i + 1][0]) + 1, ptAnchors[i][1]);
				j++)
			{
				for (int k = 0; k <= 2 * nKernelSize; k++)
				{
					UINT32 *pPixel = pShadBits +
						(szShadow.cy - i - 1 + nKernelSize - k) * szShadow.cx + j - nKernelSize;
					UINT32 *pKernelPixel = pKernel + k * (2 * nKernelSize + 1);
					for (int l = 0; l <= 2 * nKernelSize; l++)
					{
						if (*pPixel < *pKernelPixel)
							*pPixel = *pKernelPixel;
						pPixel++;
						pKernelPixel++;
					}
				}
			}	// for() start of line

				// End of line
			for (j = max(j, min(ptAnchors[i - 1][1], ptAnchors[i + 1][1]) - 1);
				j < ptAnchors[i][1];
				j++)
			{
				for (int k = 0; k <= 2 * nKernelSize; k++)
				{
					UINT32 *pPixel = pShadBits +
						(szShadow.cy - i - 1 + nKernelSize - k) * szShadow.cx + j - nKernelSize;
					UINT32 *pKernelPixel = pKernel + k * (2 * nKernelSize + 1);
					for (int l = 0; l <= 2 * nKernelSize; l++)
					{
						if (*pPixel < *pKernelPixel)
							*pPixel = *pKernelPixel;
						pPixel++;
						pKernelPixel++;
					}
				}
			}	// for() end of line

		}
	}	// for() Generate blurred border

		// Erase unwanted parts and complement missing
	UINT32 clCenter = m_nDarkness << 24 | PreMultiply(m_Color, m_nDarkness);
	for (int i = min(nKernelSize, max(m_nSize - m_nyOffset, 0));
		i < max(szShadow.cy - nKernelSize, min(szParent.cy + m_nSize - m_nyOffset, szParent.cy + 2 * m_nSize));
		i++)
	{
		UINT32 *pLine = pShadBits + (szShadow.cy - i - 1) * szShadow.cx;
		if (i - m_nSize + m_nyOffset < 0 || i - m_nSize + m_nyOffset >= szParent.cy)	// Line is not covered by parent window
		{
			for (int j = ptAnchors[i][0]; j < ptAnchors[i][1]; j++)
			{
				*(pLine + j) = clCenter;
			}
		}
		else
		{
			for (int j = ptAnchors[i][0];
				j < min(ptAnchorsOri[i - m_nSize + m_nyOffset][0] + m_nSize - m_nxOffset, ptAnchors[i][1]);
				j++)
				*(pLine + j) = clCenter;
			for (int j = max(ptAnchorsOri[i - m_nSize + m_nyOffset][0] + m_nSize - m_nxOffset, 0);
				j < min(ptAnchorsOri[i - m_nSize + m_nyOffset][1] + m_nSize - m_nxOffset, szShadow.cx);
				j++)
				*(pLine + j) = 0;
			for (int j = max(ptAnchorsOri[i - m_nSize + m_nyOffset][1] + m_nSize - m_nxOffset, ptAnchors[i][0]);
				j < ptAnchors[i][1];
				j++)
				*(pLine + j) = clCenter;
		}
	}

	// Delete used resources
	delete[](ptAnchors - (m_nSize < 0 ? -m_nSize : 0) - 1);
	delete[] ptAnchorsTmp;
	delete[] ptAnchorsOri;
	delete[] pKernel;
	DeleteObject(hParentRgn);
}

