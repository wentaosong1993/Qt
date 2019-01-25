#include <iostream>

using namespace std;

class Programmer
{
public :
	virtual void calProgIncome() = 0; 
};


class HighProgrammer: public Programmer
{
public:
	HighProgrammer(const char* name, const char* position, double income)
	{
		this->m_name = name;
		this->m_positon = position;
		this->m_income = income;
	}
	virtual void calProgIncome()
	{
		cout << "HighProgrammer income: " << m_name << m_positon << ":" << m_income << endl;
	}

private:
	const char* m_name;
	const char* m_positon;
	double m_income;
};

class MidProgrammer : public Programmer
{
public:
	MidProgrammer(const char* name,const char* position, double income)
	{
		this->m_name = name;
		this->m_positon = position;
		this->m_income = income;
	}
	virtual void calProgIncome()
	{
		cout << "MidProgrammer income: " << m_name << m_positon << ":" << m_income << endl;
	}

private:
	const char* m_name;
	const char* m_positon;
	double m_income;
};

class JuniorProgrammer : public Programmer
{
public:
	JuniorProgrammer(const char* name, const char* position, double income)
	{
		this->m_name = name;
		this->m_positon = position;
		this->m_income = income;
	}
	virtual void calProgIncome()
	{
		cout << "JuniorProgrammer income: " << m_name << m_positon << ":" << m_income << endl;
	}

private:
	const char* m_name;
	const char* m_positon;
	double m_income;
};


class TopProgrammer : public Programmer
{
public:
	TopProgrammer(const char* name, const char* position, double income)
	{
		this->m_name = name;
		this->m_positon = position;
		this->m_income = income;
	}
	virtual void calProgIncome()
	{
		cout << "TopProgrammer income: " << m_name << m_positon << ":" << m_income << endl;
	}

private:
	const char* m_name;
	const char* m_positon;
	double m_income;
};

void display(Programmer *base) //满足多态实现的条件：继承，父类指针，指针指向子类对象
{
	base->calProgIncome(); 
}

int main(void )
{
	HighProgrammer high("张三","经理",20000);

	MidProgrammer mid("李四","中级工程师",8500);

	JuniorProgrammer junior("王二麻子","初级工程师",5000);


	//系统扩展--添加架构师的工资计算
	TopProgrammer top("涛哥","架构师",40000);


	display(&high);

	display(&mid);

	display(&junior);

	display(&top);


	
	cout << "Hello world \n";
	system("pause");
	return 0;
}


/*
the output is :
HighProgrammer income: 张三经理:20000
MidProgrammer income: 李四中级工程师:8500
JuniorProgrammer income: 王二麻子初级工程师:5000
TopProgrammer income: 涛哥架构师:40000
Hello world
请按任意键继续. . .
*/