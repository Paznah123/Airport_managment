#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "General.h"
#include "Airport.h"
#include "Date.h"

void L_init(LIST* pList)
{
   // pList->head = malloc(sizeof(NODE));
    pList->head.next = NULL;
}

void L_print(const NODE* pHead, void (*print)(void*))
{
    NODE* head = pHead->next;
    while (head != NULL) {
        print(head->key);
        head = head->next;
    }
}

void L_push(NODE** head, DATA new_data)
{
    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    new_node->key = new_data;
    new_node->next = *head;

    *head = new_node;
}

void L_insertAfter(NODE* prev_node, DATA new_data)
{
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    new_node->key = new_data;
    new_node->next = prev_node->next;

    prev_node->next = new_node;
}

void L_insertLast(NODE** head_ref, DATA new_data)
{
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    NODE* last = *head_ref;

    new_node->key = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    return;
}

int L_delete(NODE* pNode, void (*freeFunc)(void*))
{
    NODE* tmp;

    if (!pNode || !(tmp = pNode->next)) return 0;

    pNode->next = tmp->next;
    if (freeFunc != NULL)
        freeFunc(tmp->key);
    free(tmp);
    return 1;
}


BOOL	L_free(NODE* pList, void (*freeFunc)(void*))
{
    NODE* tmp;

    if (!pList) return False;
    tmp = pList;
    BOOL res = True;
    while (res)
    {
        res = L_delete(tmp, freeFunc);
    }

    return True;
}

//================================

NODE* insertAirportToList(const NODE* head, const DATA data) {
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

NODE* insertDateToList(const NODE* head, const DATA data) {
    if (!head->next)
    {
        return head;
    }
    NODE* current = head;
    while (current->next)
    {
        if (compareDate((Date*)current->next->key, ((Date*)data)) > 0)
        {
            break;
        }
        current = current->next;
    }
    return current;
}

int		addLNodeToList(NODE* head, void* data, NODE* (whereToAdd)(const NODE*, const DATA)) {
    if (!head)
    {
        printf("List hasn't been initiated!\n");
        return 0;
    }
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (!newNode)
    {
        return 0;
    }
    newNode->key = data;
    NODE* wTA = (*whereToAdd)(head, data);
    if (!wTA) {
        free(newNode);
        return 0;
    }
    newNode->next = wTA->next;
    wTA->next = newNode;
    return 1;
}
