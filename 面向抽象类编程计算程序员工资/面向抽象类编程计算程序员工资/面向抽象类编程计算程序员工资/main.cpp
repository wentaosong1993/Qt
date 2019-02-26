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

void display(Programmer *base) //�����̬ʵ�ֵ��������̳У�����ָ�룬ָ��ָ���������
{
	base->calProgIncome(); 
}

int main(void )
{
	HighProgrammer high("����","����",20000);

	MidProgrammer mid("����","�м�����ʦ",8500);

	JuniorProgrammer junior("��������","��������ʦ",5000);


	//ϵͳ��չ--��Ӽܹ�ʦ�Ĺ��ʼ���
	TopProgrammer top("�θ�","�ܹ�ʦ",40000);


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
HighProgrammer income: ��������:20000
MidProgrammer income: �����м�����ʦ:8500
JuniorProgrammer income: �������ӳ�������ʦ:5000
TopProgrammer income: �θ�ܹ�ʦ:40000
Hello world
�밴���������. . .
*/