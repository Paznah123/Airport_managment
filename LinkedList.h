#pragma once

#include "General.h"

//================================

typedef struct Node
{
    DATA key;
    struct Node* next;
} NODE;

typedef struct List
{
    NODE head;
} LIST;

//================================

void    L_init(LIST* pList);
void    L_print(const NODE* pHead, void (*print)(void*));
int     L_delete(NODE* pNode, void (*freeFunc)(void*));
int		insertNodeToList(NODE* head, void* data, NODE* (whereToAdd)(const NODE*, const DATA));
BOOL	L_free(NODE* pList, void (*freeFunc)(void*));
NODE*   chooseAirportPlace(const NODE* head, const DATA data);
NODE*   chooseDatePlace(const NODE* head, const DATA data);

//================================
