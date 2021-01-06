#pragma once

#include "General.h"

typedef struct Node
{
    DATA key;
    struct Node* next;
} NODE;

typedef struct List
{
    NODE head;
} LIST;

void L_init(LIST* pList);
void L_print(const NODE* pHead, void (*print)(void*));
void L_push(NODE** head, DATA new_data);
void L_insertAfter(NODE* prev_node, DATA new_data);
int L_delete(NODE* pNode, void (*freeFunc)(void*));

//================================

int		addLNodeToList(NODE* head, void* data, NODE* (whereToAdd)(const NODE*, const DATA));
NODE* insertAirportToList(const NODE* head, const DATA data);
NODE* insertDateToList(const NODE* head, const DATA data);
BOOL	L_free(NODE* pList, void (*freeFunc)(void*));