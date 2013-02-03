/*
define a MARCO that will declare a static memory pool to manage this class;
And this will override the new and delete method to allocate and deallocate
memmory from the pool;
If any class extends this class wants to use pool to manage memory has to 
use this marco in the class define.And use the POOL_IMPLEMENT marco to implent
the memory pool of itsself;
*/
#ifndef EVENT_H
#define EVENT_H

#include "Memory_Pool.h"

#define POOL_DEFINE(CLASSNAME) \
public:\
static Memory_Pool<CLASSNAME> pool;\
void* operator new(size_t size)\
{\
	pool.allocate();\
};\
void operator delete(void *p)\
{\
	pool.deallocate(p);\
};\

class Event
{
public:
	int a;
	char b;
	short c;
	POOL_DEFINE(Event);
};

#endif