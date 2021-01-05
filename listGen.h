#pragma once

#include "General.h"

//==============================

typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

//==============================

int		addLNodeToList(NODE* head, void* data, NODE* (whereToAdd)(const* NODE, const void*));
int		L_print(NODE* pList, void(*print)(const void*));										// print the list content
void	L_push(NODE** head, DATA data);
BOOL	L_init(NODE* pList);																// create new list
BOOL	L_delete(NODE* pNode, void (*freeFunc)(void*));										// erase node after *pNode
BOOL	L_free(NODE* pList, void (*freeFunc)(void*));										// free list memory
NODE*	L_insertLast(NODE*  pNode, DATA Value);												// add new node after *pNode
NODE*	inputLocationOfAirport(const NODE* head, const void* data);

//==============================