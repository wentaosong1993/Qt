#include<iostream>

using namespace std;

/*
3
4
�밴���������. .
*/

//void swap(int *a,int *b)
//{
//	int *t = a;
//	a = b;
//	b = t;
//}
//
// int main()
//{
//	 int i = 3, j = 4;
//	 swap(&i,&j);
//	 cout << i << "\n" << j << endl;
//}


/*
4
3
�밴���������. .
*/
//void swap(int &a, int  &b)
//{
//	int t = a;
//	a = b;
//	b = t;
//}
//
//int main()
//{
//	int i = 3, j = 4;
//	swap(i, j);
//	cout << i << "\n" << j << endl;
//}




/*
4
3
�밴���������. . .
*/
void swap(int **a, int  **b)
{
	int *t = *a;
	a = b;
	*b = t;
}

int main()
{
	int i = 3, j = 4;
	swap(i, j);
	cout << i << "\n" << j << endl;
}






