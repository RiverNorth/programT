#include "Event.h"
#include "Memory_Pool.h"
#include <stdexcept>
#include <iostream>

Memory_Pool<Event> temp;
Memory_Pool<Event> Event::pool=temp;
int main(int argc,char **argv)
{
	int i=0;
	while(i<1000)
	{
		try{
		Event *e=new Event();
		if(e==0)
			break;
		}catch(const std::bad_alloc &e){
			std::cout<<"allocate error"<<std::endl;
		}
	}
	return 0;
}