extern "C"{
#include "Memory_Pool.h"
}
#include <iostream>

template<class Type> Type* Memory_Pool<Type>::allocate()
{
	#ifdef DEBUG
	allco_num++;
	std::cout<<allco_num<<std::endl;
	#endif
	if(head==0||head==end)
		{
			return 0;
		}
	temp=head;
	head=head->next;
	return temp->pointer;
};

template<class Type> Memory_Pool<Type>::Memory_Pool(int init_size_t,int max_size_t):
	init_size(init_size_t),max_size(5),used_size(0)
{
	#ifdef DEBUG
	allco_num=0;
	#endif
	temp=0;
	beginMemory=(Type*)malloc(init_size*sizeof(Type));
	endMemory=beginMemory+init_size_t-1;
	head=(Point*)malloc(sizeof(Point));
	head->pointer=beginMemory;
	end=head;
	for(int i=0;i<init_size-1;i++)
	{
		end->next=(Point*)malloc(sizeof(Point));
		end=end->next;
		end->pointer=beginMemory+i+1;
	}
	end->next=0;
};

template<class Type> void Memory_Pool<Type>::deallocate(void *p)
{
	#ifdef DEBUG
	allco_num--;
	std::cout<<"deallocate "<<allco_num<<endl;
	#endif
	end->next=p;
	end=p;
};