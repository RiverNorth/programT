#ifndef MEMORY_POOL_BASE
#define MEMORY_POOL_BASE
class Memory_Pool_Base
{
	public:
		virtual void* allocate()=0;
		virtual void deallocate(void *p)=0;
		Memory_Pool_Base()
		{
			Memory_Pool_Base *temp=head;
			head=this;
			head->next=temp;
		};
	private:
		static Memory_Pool_Base *head;
		Memory_Pool_Base *next;

};

Memory_Pool_Base* Memory_Pool_Base::head=0;


#endif