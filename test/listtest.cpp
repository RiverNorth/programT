#include "inlist.h"
#include "stdlib.h"
#include "stdio.h"
struct MyList
{
	InList inlist;
	int data;
};
int main(int argc,char** argv)
{
	INITLIST(head);
	for(int i=0;i<10;i++)
    {
        struct MyList* tlist1=(struct MyList*)malloc(sizeof(MyList));
        tlist1->data=i;
        add_node_tail(&(tlist1->inlist),head);
        if(i==5)
        {
            DEL_NODE(&(tlist1->inlist),head,struct MyList,inlist);
        }
    }
    struct MyList* mylist=NULL;
    LOOP(head,struct MyList,inlist,mylist)
    {
        printf("\n%d\n",mylist->data);
    }
}
