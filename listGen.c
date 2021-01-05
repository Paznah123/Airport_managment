#include <stdio.h>
#include <stdlib.h>

#include "sortUtil.h"
#include "listGen.h"
#include "Airport.h"

//================================

BOOL	L_init(NODE* pList)
{
	pList->key = (Airport*)malloc(sizeof(Airport));
	if (pList == NULL) return False;	// no list to initialize
	pList->next = NULL;
	return True;
}

//================================

NODE*	L_insertLast(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		pNode->next = tmp;
		tmp->next = NULL;
	}
	return tmp;
}

//================================

int		addLNodeToList(NODE* head, void* data, NODE* (whereToAdd)(const *NODE, const void*)) {
	if (!head)
	{
		printf("List hasn't been initiated!\n");
		return 0;
	}
	// Allocate new node
	NODE* newLNode = (NODE*)malloc(sizeof(NODE));
	if (!newLNode)
	{
		return 0;
	}
	newLNode->key = data; 
	NODE* wTA = (*whereToAdd)(head, data);
	if (!wTA) {
		free(newLNode);
		return 0;
	}
	newLNode->next = wTA->next;
	wTA->next = newLNode;
	return 1;
}

//================================

// Create a node with the data equal value and place it at the head of the list
void	L_push(NODE** head, DATA data) {
	
	NODE* new_node = (NODE*)malloc(sizeof(NODE));

	new_node->key = data;
	new_node->next = *head;

	*head = new_node;
}

//================================

BOOL	L_delete(NODE* pNode,void (*freeFunc)(void*))
{
	NODE* tmp;

	if ( !pNode || !(tmp = pNode->next) ) return False;

	pNode->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->key);
	free(tmp);
	return True;
}

//================================

BOOL	L_free(NODE* pList, void (*freeFunc)(void*))
{
	NODE *tmp;

	if ( !pList ) return False;
	tmp = &(pList->next);
	BOOL res=True;
	while (res)
	{
		res = L_delete(tmp, freeFunc);
	}
	
	return True;
}

//================================

int		L_print(NODE* pList, void(*print)(const void*))
{
	NODE	*tmp = pList;
	int		c = 0;

	if ( !pList ) return 0;

	printf("\n");
	while (tmp != NULL) {
		print(tmp->key);
		tmp = tmp->next;
	}
	printf("\n");
	return c;
}

//================================

NODE*	inputLocationOfAirport(const NODE* head, const void* data) {
	if (!head->next)
	{
		return head;
	}
	NODE* current = head;
	while (current->next)
	{
		if (strcmp(((Airport*)current->next->key)->code, ((Airport*)data)->code) > 0)
		{
			break;
		}
		current = current->next;
	}
	return current;
}

//==============================
