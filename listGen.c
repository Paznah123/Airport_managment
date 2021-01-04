#include <stdio.h>
#include <stdlib.h>

#include "sortUtil.h"
#include "listGen.h"
#include "Airport.h"

/* Function to sort the list */
int bubbleSort(NODE** head, int count)
{
	NODE** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {
		h = head;
		swapped = 0;
		for (j = 0; j < count - i - 1; j++) {
			NODE* p1 = *h;
			NODE* p2 = p1->next;
			if (compareAirportsByIATA(p1->key,p2->key)) {
				*h = swap(p1, p2);
				swapped = 1;
			}
			h = &(*h)->next;
		}
		if (swapped == 0)
			break;
	}
}

NODE* swap(NODE* ptr1, NODE* ptr2)
{
	NODE* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL	L_init(NODE* pList)
{
	pList->key = (Airport*)malloc(sizeof(Airport));
	if ( pList == NULL ) return False;	// no list to initialize
	pList->next = NULL;
	return True;
}

/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE*	L_insertLast(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if ( !pNode ) return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if ( tmp != NULL )  {
		tmp->key = Value;
		pNode->next = tmp;
		tmp->next = NULL;
	}
	return tmp;
}

NODE* L_insertAfter(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode) return NULL;

	NODE* secondPointer = pNode;
	NODE* firstPointer = pNode->next;
	
	tmp = (NODE*)malloc(sizeof(NODE));	// new node
	while (firstPointer->next != NULL) {
		if (compareAirportsByIATA(firstPointer->key, (Airport*)Value)) {
			if (tmp != NULL) {
				tmp->key = Value;
				tmp->next = firstPointer;
				secondPointer->next = tmp;
			}
		}
		firstPointer = firstPointer->next;
		secondPointer = secondPointer->next;
	}
	
	return tmp;
}
//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
NODE*	L_find(NODE* pNode, DATA value, int(*compare)(const void*, const void*))
{
	NODE* temp = NULL;
	if ( !pNode ) return NULL;
	while(pNode!= NULL)
	{
		if(compare(pNode->key,value) == 0)
		{
			temp = pNode;
			break;
		}
		pNode = pNode->next;
	}

	return temp;


}

//////////////////////////////////////////////////
//// Free (additional function)
//// Aim:		free the list memory
//// Input:	pointer to the list structure
//// Output:	TRUE if succeeded
//////////////////////////////////////////////////
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

////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
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

// For each member of  Linked List call function func with data as a single argument
void	L_forEach(NODE* list, int numOfElements, int elementSize, void (*func)(void* data)) {
	for (int i = 0; i < numOfElements; i++)
	{
		func(list->key);
		list = list->next;
	}
	while (list != NULL) {
		func(list->key);
		list = list->next;
	}
}

//==============================


