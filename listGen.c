#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"
#include "Airport.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(NODE* pList)
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
NODE* L_insertLast(NODE* pNode, DATA Value)
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


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode,void (*freeFunc)(void*))
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
NODE* L_find(NODE* pNode, DATA value, int(*compare)(const void*, const void*))
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
//BOOL L_free(NODE* pList, void (*freeFunc)(void*))
//{
//	NODE *tmp;
//
//	if ( !pList ) return False;
//	tmp = &(pList->head);
//	BOOL res=True;
//	while (res)
//	{
//		res = L_delete(tmp, freeFunc);
//	}
//	
//	return True;
//}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
//int L_print(NODE* pList, void(*print)(const void*))
//{
//	NODE	*tmp;
//	int		c = 0;
//
//	if ( !pList ) return 0;
//
//	printf("\n");
//	for ( tmp = pList->head.next;  tmp;  tmp = tmp->next, c++ )
//		print(tmp->key);
//	printf("\n");
//	return c;
//}
void* copyAirport(void* val)
{
	Airport* src = (Airport*)val;
	Airport* dst = (Airport*)malloc(sizeof(Airport));
	if (!dst)
	{
		return NULL;
	}
	dst->name = _strdup(src->name);
	dst->country = _strdup(src->country);
	strcpy(dst->code, src->code);
	return dst;
}

void push( NODE** head, DATA data) {
	NODE* new_node = (struct NODE*)malloc(sizeof( NODE));

	new_node->key = data;
	new_node->next = *head;

	*head = new_node;
}











void insert(NODE* lastPtrNode, DATA x, void* (*copyValue)(DATA src))
{
	NODE* nQ = (NODE*)malloc(sizeof(NODE));
	if (!nQ)  //case allocation failed
	{
		printf("Null");
		return;
	}
	//NODE* q = Q;
	//while (q->next != NULL)
	//{
	//	q = q->next;
	//}
	nQ->key = copyValue(x);
	nQ->next = NULL;
	lastPtrNode->next = nQ;
}


