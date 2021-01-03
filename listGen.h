#ifndef _LIST_
#define _LIST_

#include "def.h"

//==============================

typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

//==============================

BOOL	L_init(NODE* pList);					// create new list
BOOL	L_delete(NODE* pNode, void (*freeFunc)(void*));					// erase node after *pNode
BOOL	L_free(NODE* pList, void (*freeFunc)(void*));					// free list memory
NODE*	L_insertLast(NODE*  pNode, DATA Value);	// add new node after *pNode
NODE*	L_find(NODE* pNode, DATA Value,int(*compare)(const void*, const void*));		// return a pointer to the node 
int		L_print(NODE* pList,void(*print)(const void*));					// print the list content
void	L_forEach(NODE* list, int numOfElements, int elementSize, void (*func)(void* data));

#endif