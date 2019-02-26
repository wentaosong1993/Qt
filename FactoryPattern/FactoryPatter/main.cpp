#include <iostream>
using namespace std;



class Fruit
{
public:
    virtual void getFruit() = 0;//抽象类
private:

};



class Banana: public Fruit
{
public:
    virtual void getFruit()
    {
		cout << "I'm a banana" << endl;
    }
};

class Apple: public Fruit
{
public:
    virtual void getFruit()
    {
		cout << "I'm an Apple" << endl;
    }
};


///简单工厂模式demo
///优点即缺点
class Factory
{
public:
    Fruit* createFruit(const char *furit)
    {
        if(strcmp(furit,"banana") == 0)
        {
            return new Banana;
        }
        else if(strcmp(furit,"apple") == 0)
        {
            return new Apple;
        }
        else
        {
			cout << "not supported!" << endl;
            return NULL;
        }
    }
};

int main(int argc, char *argv[])
{
    Factory *f = new Factory;

    Fruit *fruit = NULL;

    fruit = f->createFruit("banana");
    fruit->getFruit();
    delete fruit;


    fruit = f->createFruit("apple");
    fruit->getFruit();
    delete fruit;


    delete f;

	system("pause");
	return;
}
///the output
/*
I'm a banana
I'm an Apple
*/

