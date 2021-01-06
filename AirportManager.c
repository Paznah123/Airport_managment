#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileUtil.h"
#include "AirportManager.h"
#include "LinkedList.h"

//==============================

int		initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	L_init(&pManager->airportList);

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

//==============================

int		addAirport(AirportManager* pManager)
{
	Airport* temp = (Airport*)malloc(sizeof(Airport));
	if (!temp)
		return 0;

	setAirport(temp, pManager);
	
	addLNodeToList(&pManager->airportList.head, temp, insertAirportToList);

	pManager->count++;
	return 1;
}

void	setAirport(Airport* pPort, AirportManager* pManager)
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

//==============================

Airport*	findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE* pointerAirport = pManager->airportList.head.next;
	for (int i = 0; i < pManager->count; i++){
		Airport* airport = pointerAirport->key;
		if (isAirportCode(airport, code)) 
			return airport;
		pointerAirport = pointerAirport->next;
	}

	return NULL;
}

int		checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager,code);

	if (port != NULL)
		return 0;

	return 1;
}

//==============================

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	L_print(&pManager->airportList.head, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	for (int i = 0; i < pManager->count; i++)
	{
		L_free(&pManager->airportList.head, freeAirport);
	}
}

//==============================
