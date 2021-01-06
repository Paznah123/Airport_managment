#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Company.h"
#include "searchUtil.h"

// ====================================

void	searchFlight(Company* pComp, eSortType searchType) {

	Flight* flight = (Flight*)malloc(sizeof(Flight));

	switch (searchType)
	{
	case eHour:
		bSearchByHour(pComp, flight);
		break;
	case eDate:
		bSearchByDate(pComp, flight);
		break;
	case eOriginCode:
		bSearchByOriginCode(pComp, flight);
		break;
	case eDestCode:
		bSearchByDestCode(pComp, flight);
		break;
	case eNull:
		printf("Flights Not Sorted!");
		break;
	}
}

// ============================

void	bSearchByHour(Company* pComp, Flight* flight)
{
	flight->hour = getFlightHour();
	Flight** temp = bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight**), compareByHour);
	if (temp != NULL)
		printFlight(temp[0]);
	else
		printf("Flight Not Found!");
}

// ============================

void	bSearchByDate(Company* pComp, Flight* flight)
{
	Date* date = malloc(sizeof(Date));
	getCorrectDate(date);
	flight->date = *date;
	Flight** temp = bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight**), compareByDate);
	if (temp)
		printFlight(temp[0]);
	else
		printf("Flight Not Found!");
}

// ============================

void	bSearchByOriginCode(Company* pComp, Flight* flight)
{
	char code[CODE_LENGTH + 1];
	getAirportCode(code);
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		flight->originCode[i] = code[i];
	}
	flight->originCode[CODE_LENGTH] = '\0';
	Flight** temp = bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight**), compareByOriginCode);
	if (temp)
		printFlight(temp[0]);
	else
		printf("Flight Not Found!");
}

// ============================

void	bSearchByDestCode(Company* pComp, Flight* flight)
{
	char code[CODE_LENGTH + 1];
	getAirportCode(code);
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		flight->destCode[i] = code[i];
	}
	flight->destCode[CODE_LENGTH] = '\0';
	Flight** temp = bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight**), compareByDestCode);
	if (temp)
		printFlight(temp[0]);
	else
		printf("Flight Not Found!");
}

// ============================
