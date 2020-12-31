#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	L_init(&pManager->headList);
	L_init(&pManager->listPtr);
	pManager->listPtr = pManager->headList;
	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	if (!pManager)
		return 0;

	for (int i = 0; i < count; i++)
	{
		addAirport(pManager);
	}

	return 1;
}



int	addAirport(AirportManager* pManager)
{
	Airport* temp = (Airport*)malloc(sizeof(Airport));
	if (!temp)
		return 0;
	if (!pManager->listPtr)
		return 0;
	setAirport(temp, pManager);

	 pManager->listPtr=L_insertLast(pManager->listPtr, temp);
	pManager->count++;
	return 1;
}




void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{

	NODE* pointerAirport= pManager->headList;
	for (int i = 0; i < pManager->count-1; i++)
	{
		if (isAirportCode(&pointerAirport, code))
			return pointerAirport;

		pointerAirport = pointerAirport->next;
	}
	return NULL;
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager,code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	NODE* pointerAirport = pManager->headList;
	for (int i = 0; i < pManager->count; i++)
	{
		printAirport(pointerAirport->next->key);
		printf("\n");
		pointerAirport = pointerAirport->next;
	}
}

void freeManager(AirportManager* pManager)
{
	free(pManager->headList);
}
