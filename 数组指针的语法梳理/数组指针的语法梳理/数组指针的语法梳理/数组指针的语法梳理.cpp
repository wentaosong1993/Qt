// 数组指针的语法梳理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"


//定义一个数组类型


//定义一个指针数组类型



//定义一个指向 数组类型的指针 数组类的指针

int main()
{

	int a[10]; //a代表的是数组首元素的地址，&a代表的是整个数组的地址 ； a + 1  步长： 4
			   //&a+1  步长为40


	//定义一个数组类型
	{
		typedef  int(myTypeArray)[10];
		myTypeArray myArray;
		myArray[0] = 10;

		printf("%d \n ",myArray[0]);
	}

	//定义一个指针数组类型
	{
		typedef int (*pTypeArray)[10]; //int *p
		pTypeArray mpArray;  //sizeof(int) * 10
		mpArray = &a;
		(*mpArray)[0] = 20;
		printf("a[0]: %d \n",a[0]);
	}

	//定义一个指向 数组类型的指针 数组类的指针
	{
		int(*myPointer)[10];

		myPointer = &a;
		(*myPointer)[1] = 30;
		printf("a[1]: %d \n", a[1]);
	}

	system("pause");
    return 0;
}

