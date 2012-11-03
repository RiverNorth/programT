#ifndef MEMORY_POOL.H
#define MEMORY_POOL.H
extern "C"{  
#include "stdlib.h"
}
#include "stdio.h"
#include <iostream>


struct Point
{
	Point *next;
	void *pointer;
};

template<class Type> class Memory_Pool
{
	typedef struct Point Point;
	public:
		void* allocate();
		void deallocate(void *p);
		Memory_Pool<Type>(int init_size_t=5,int max_size_t=20);
	private:
		int init_size;
		int max_size;
		int used_size;
		Type *beginMemory;
		Type *endMemory;
		Point *temp;
		Point *head;
		Point *end;
		#ifdef DEBUG
		int allco_num;
		#endif

		// void Request_More_Memory(int size)
		// {
		// 	Type*
		// 	head=(Point*)malloc(sizeof(Point))
		// 	head->pointer=first;
		// 	end=head;
		// 	for(int i=0;i<init_size-1;i++)
		// 	{
		// 		end->next=(point*)malloc(sizeof(point))
		// 		end=end->next;
		// 		end->pointer=first+i+1;
		// 	}
		// 	end->next=NULL;
		// }
};



template<class Type> void* Memory_Pool<Type>::allocate()
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
	if(end->next=0)
		std::cout<<"error when dellocate"<<std::endl;
	end=end->next;
	end->pointer=p;
};
#endif