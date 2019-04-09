#pragma once

#include <QString>
#include <windows.h>


typedef struct tagTImageInfo
{
	HBITMAP hBitmap;
	LPBYTE pBits;
	LPBYTE pSrcBits;
	int nX;
	int nY;
	bool bAlpha;
	bool bUseHSL;
	QString sResType;
	DWORD dwMask;
} TImageInfo;
class CValArray
{
public:
	CValArray(int iElementSize, int iPreallocSize = 0);
	~CValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex, int iCount = 1);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};

class CShadow
{
public:
	CShadow();
public:
	virtual ~CShadow();
protected:
	static HINSTANCE s_hInstance;
	static CValArray s_ShadowArray;

	typedef BOOL(WINAPI * pfnUpdateLayeredWindow)(HWND hWnd, HDC hdcDst, POINT *pptDst,
		SIZE *psize, HDC hdcSrc, POINT * pptSrc, COLORREF crKey,
		BLENDFUNCTION *pblend, DWORD dwFlags);
	static pfnUpdateLayeredWindow s_UpdateLayeredWindow;
	HWND m_hWnd;
	WNDPROC m_OriParentProc;

	enum ShadowStatus
	{
		SS_ENABLED = 1,
		SS_VISABLE = 1 << 1,
		SS_PARENTVISIBLE = 1 << 2
	};

	BYTE m_Status;
	unsigned char m_nDarkness;
	unsigned char m_nSharpness;
	signed char m_nSize;
	signed char m_nxOffset;
	signed char m_nyOffset;
	LPARAM m_WndSize;
	bool m_bUpdate;
	COLORREF m_Color;
	TImageInfo * m_pImageInfo;
	RECT m_rcCorner;
	RECT m_rcHoleOffset;
public:
	static bool Initialize(HINSTANCE hInstance);
	HWND GetHWND() const;
	operator HWND() const;
	void Create(HWND hParentWnd);
	bool SetImage(LPCTSTR image, RECT rcCorner, RECT rcHoleOffset);
	bool SetSize(int NewSize = 0);
	bool SetSharpness(unsigned int NewSharpness = 5);
	bool SetDarkness(unsigned int NewDarkness = 200);
	bool SetPosition(int NewXOffset = 5, int NewYOffset = 5);
	bool SetColor(COLORREF NewColor = 0);
protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ParentProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static CShadow* FindShadowWindow(HWND hWnd);
	static int GetShadowWindowIndex(HWND hWnd);
	void Update(HWND hParent);
	void MakeShadow(UINT32* pShadBits, HWND hParent, RECT *rcParent);
	inline DWORD PreMultiply(COLORREF c1, unsigned char nAlpha)
	{
		return (GetRValue(c1)*(DWORD)nAlpha / 255) << 16 |
			(GetGValue(c1)*(DWORD)nAlpha / 255) << 8 |
			(GetBValue(c1)*(DWORD)nAlpha / 255);
	}
};












