#include <iostream>

class A
{
public:
	class B
	{
	public:
		int *c;
		B(){};
	};
	B *b;
	A()
	{
		b=new B;
	}
};

A a;
void setValue(A *a)
{
	int g=3;
	a->b->c=&g;
};

int main(int argc,char** argv)
{
	setValue(&a);
	std::cout<<a.b->c<<std::endl;
}