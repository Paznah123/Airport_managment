#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "General.h"
#include "Airport.h"
#include "Date.h"

//==============================

void L_init(LIST* pList)
{
    pList->head.next = NULL;
}

//==============================

void L_print(const NODE* pHead, void (*print)(void*))
{
    NODE* head = pHead->next;
    while (head != NULL) 
    {
        print(head->key);
        head = head->next;
    }
}

//==============================

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

//==============================

BOOL	L_free(NODE* pList, void (*freeFunc)(void*))
{
    NODE* tmp;

    if (!pList) return False;
    tmp = pList;
    BOOL res = True;
    while (res)
        res = L_delete(tmp, freeFunc);

    return True;
}

//================================

NODE*   chooseAirportPlace(const NODE* head, const DATA data) {
    if (!head->next)
        return head;

    NODE* current = head;
    while (current->next)
    {
        if (strcmp(((Airport*)current->next->key)->code, ((Airport*)data)->code) > 0)
            break;
        current = current->next;
    }
    return current;
}

//==============================

NODE*   chooseDatePlace(const NODE* head, const DATA data) {
    if (!head->next)
    {
        return head;
    }
    NODE* current = head;
    while (current->next)
    {
        if (compareDate((Date*)current->next->key, ((Date*)data)) > 0)
            break;
        current = current->next;
    }
    return current;
}

//==============================

int		insertNodeToList(NODE* head, void* data, NODE* (findPlace)(const NODE*, const DATA)) {
    if (!head)
    {
        printf("List is Empty!\n");
        return 0;
    }
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (!newNode)
        return 0;
    newNode->key = data;
    NODE* correctPlace = (*findPlace)(head, data);
    if (!correctPlace) {
        free(newNode);
        return 0;
    }
    newNode->next = correctPlace->next;
    correctPlace->next = newNode;
    return 1;
}
