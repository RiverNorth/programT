#ifndef IN_LIST_H
#define IN_LIST_H
#include "stdio.h"
#include "stdlib.h"

struct inList
{
 struct inList *next;
 struct inList *prev;
};

typedef struct inList InList;

const int psize=sizeof(int);

#define INITLIST(name) \
    InList* name=(InList*)malloc(sizeof(InList));\
    name->prev=name;name->next=name;

#define list_entry(node,type,member) \
    (type*)((char*)node-(unsigned long)(&(((type*)0)->member)))

#define DEL_NODE(node,head,type,member) \
    delete(list_entry(node,type,member))

#define LOOP(head,type,member,result) \
    for(InList* i=head;(i=i->next)!=head&&(result=list_entry(i,type,member));)

static void inline add_node_tail(InList* node,InList* head)
{
    head->prev->next=node;
    node->prev=head->prev;
    node->next=head;
    head->prev=node;
}

static void inline delnode(InList* nodename,InList* head)
{
    if(nodename == head)
    {
        return;
    }
    nodename->prev->next= nodename->next;
    nodename->next->prev= nodename->prev;
    return;
}

#endif
