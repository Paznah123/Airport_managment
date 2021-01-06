#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Flight.h"
#include "Date.h"

//==============================

void	initFlight(Flight* pFlight, const AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager,"Enter code of origin airport:");
	strcpy(pFlight->originCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager,"Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	getCorrectDate(&pFlight->date);
	pFlight->hour = getFlightHour();
}

int		getFlightHour()
{
	int h;
	do {
		printf("Enter flight hour [0-23]:\t");
		scanf("%d", &h);
	} while (h < 0 || h>23);
	return h;
}

//==============================

Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do {
		printf("%s\t", msg);
		myGets(code, MAX_STR_LEN);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while (port == NULL);

	return port;
}

//==============================

int		isFlightInRoute(const Flight* pFlight,const char* codeSource, const char* codeDest)
{
	Flight** flight = (Flight**)pFlight;
	if ((strcmp(flight[0]->originCode, codeSource) == 0) &&
		(strcmp(flight[0]->destCode, codeDest) == 0))
		return 1;

	return 0;
}

int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, 
		const char* codeDest)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isFlightInRoute(arr, codeSource, codeDest))
			count++;
		arr++;
	}
	return count;
}

//==============================

void	printFlight(const Flight* pFlight)
{
	printf("Flight - %s -> %s | ", pFlight->originCode, pFlight->destCode);
	printf("Hour: %d\t", pFlight->hour);
	printDate(&pFlight->date);
}

void	freeFlight(Flight* pFlight)
{
	free(pFlight);
}

//==============================
