#include "Event.h"
#include "Memory_Pool.h"

Memory_Pool<Event> temp;
Memory_Pool<Event> Event::pool=temp;
int main(int argc,char **argv)
{
	int i=0;
	while(i<1000)
	{
		Event *e=new(std::nothrow)Event;
		if(e==0)
			break;
	}
	return 0;
}