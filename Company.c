#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

//==============================

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	
	L_init(&pComp->headDate);
	pComp->listDate = L_insertLast(&(pComp->headDate), NULL);
	pComp->headDate = pComp->listDate;
	pComp->datesNumber = 0;
	
	pComp->sortType = sortNull;
}

//==============================

int		addFlight(Company* pComp,const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enough airports to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount],pManager);
	if (checkDateExists(&pComp->flightArr[pComp->flightCount]->date, pComp) == False) {
		pComp->listDate = L_insertLast(pComp->listDate, &pComp->flightArr[pComp->flightCount]->date);
		pComp->datesNumber++;
	}
	pComp->flightCount++;
	return 1;
}

//==============================

BOOL	checkDateExists(Date* date, Company* pComp) 
{
	NODE* listDate = pComp->headDate->next;
	for (int i = 0; i < pComp->datesNumber; i++)
	{
		Date* dateInList = (Date*)listDate->key;
		if (isDateEqual(date, dateInList) == True) 
			return True;
		listDate = listDate->next;
	}
	return False;
}

BOOL	isDateEqual(Date* date, Date* dateInList) {
	if (dateInList->day == date->day &&
		dateInList->month == date->month &&
		dateInList->year == date->year)
	{
		printf("the date exists");
		return True;
	}
	return False;
}

//==============================

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH+1];
	char codeDestination[CODE_LENGTH + 1];
	
	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n",codeOrigin, codeDestination);
}

void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++) {
		printFlight(pFlight[i]);
	}
}

//==============================

void	printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount); // needs fix!! 
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
}

// ====================================

void sortFlightList(Company* pComp) {

	int by, size = pComp->flightCount;
	printf("Enter 1 to sort by hour\n");
	printf("Enter 2 to sort by date\n");
	printf("Enter 3 to sort by origin code\n");
	printf("Enter 4 to sort by dest code\n");
	
	scanf("%d", &by);
	switch (by)
	{
	case sortHour:
		qsort(pComp->flightArr, size, sizeof(Flight**), compareByHour);
		pComp->sortType = sortHour;
		break;
	case sortDate:
		qsort(pComp->flightArr, size, sizeof(Flight**), compareByDate);
		pComp->sortType = sortDate;
		break;
	case sortOriginCode:
		qsort(pComp->flightArr, size, sizeof(Flight**), compareByOriginCode);
		pComp->sortType = sortHour;
		break;
	case sortDestCode:
		qsort(pComp->flightArr, size, sizeof(Flight**), compareByDestCode);
		pComp->sortType = sortDate;
		break;
	}

}

// ====================================

int compareByHour(const DATA a, const DATA b) {
	Flight* flightA = *(Flight**)a;
	Flight* flightB = *(Flight**)b;

	if (flightA->hour < flightB->hour)
		return -1;
	else if (flightA->hour > flightB->hour)
		return 1;
	else
		return 0;
}

int compareByDate(const DATA a, const DATA b) {
	Flight** flightA = (Flight**)a;
	Flight** flightB = (Flight**)b;

	if (flightA[0]->date.year != flightB[0]->date.year)
		return flightA[0]->date.year - flightB[0]->date.year;
	else if (flightA[0]->date.month != flightB[0]->date.month)
		return flightA[0]->date.month - flightB[0]->date.month;
	else if (flightA[0]->date.day != flightB[0]->date.day)
		return flightA[0]->date.day - flightB[0]->date.day;
	return 0;
}

int compareByOriginCode(const DATA a, const DATA b) {
	Flight** flightA = (Flight**)a;
	Flight** flightB = (Flight**)b;

	return strcmp(&flightA[0]->originCode, &flightB[0]->originCode);
}

int compareByDestCode(const DATA a, const DATA b) {
	Flight** flightA = (Flight**)a;
	Flight** flightB = (Flight**)b;

	return strcmp(&flightA[0]->destCode ,&flightB[0]->destCode);
}

