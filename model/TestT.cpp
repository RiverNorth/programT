#include <iostream>
using namespace std;

// #pragma pack(1)
// struct A
// {	
// 	char a;
// 	int c;
// };

class A
{
public:
	A()
	{
		cout<<"a.printf"<<endl;
	};

};

class B :public A
{
public:
	B()
	{

	};

	static char a[3];
};

char B::a[3]={'a'};

int main()
{
	// char a[3]={'a','b','c'};
	// char *b;
	// b=a;
//	B b;
	// B::a[3]={'c','b','a'};
//	for(int i=0;i<3;i++)
//	{
//		cout<<b.a[i]<<endl;
//	}
	using namespace std;
	for(int i =0;i<9;i++)
	{
		cout<<i;
	}
	for(int i=0;i<9;i++)
	{
		cout<<i;
	}
}
