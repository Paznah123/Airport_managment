/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "def.h"


/*** Definitions ***/

// Node
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;




/*** Function prototypes ***/

BOOL L_init(NODE* pList);					// create new list
//NODE* pNode,
NODE* L_insertLast(NODE*  pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode, void (*freeFunc)(void*));					// erase node after *pNode

NODE* L_find(NODE* pNode, DATA Value,int(*compare)(const void*, const void*));		// return a pointer to the node 

BOOL L_free(NODE* pList, void (*freeFunc)(void*));					// free list memory

int L_print(NODE* pList,void(*print)(const void*));					// print the list content

void* copyAirport(void* val);

void insert(NODE* Q, DATA x, void* (*copyValue)(DATA src));

// Create a node with the data equal value and place it at the head of the list
void push(struct Node** head, DATA data);


#endif