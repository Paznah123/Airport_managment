#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortUtil.h"
#include "searchUtil.h"
#include "LinkedList.h"
#include "Company.h"
#include "Airport.h"
#include "General.h"

//==============================

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	
	L_init(&pComp->dateList);

	pComp->datesNumber = 0;
	pComp->flightCount = 0;
	pComp->flightArr = NULL;
	pComp->sortType = eNull;
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
		insertNodeToList(&pComp->dateList.head, &pComp->flightArr[pComp->flightCount]->date, chooseDatePlace);
		pComp->datesNumber++;
	}
	pComp->flightCount++;
	return 1;
}

//==============================

BOOL	checkDateExists(Date* date, Company* pComp) 
{
	NODE* listDate = &pComp->dateList.head;
	while(listDate->next){
		Date* dateInList = (Date*)listDate->next->key;
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


void printDates(Company* pComp) {
	NODE* pHead = &pComp->dateList.head;
	while (pHead->next) {
		printDate(pHead->next->key);
		pHead = pHead->next;
	}
}

void	printCompany(const Company* pComp)
{
	printf("Company %s: ", pComp->name);
	printf("Has %d flights\n\n", pComp->flightCount);
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), printFlight);
	printf("\n=== Date List ===\n");
	printDates(pComp);
}

//==============================

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void	freeCompany(Company* pComp)
{
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight**), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->dateList.head,NULL);
}

// ====================================

void	sortFlightList(Company* pComp) {

	int by = sortMenu();

	switch (by)
	{
		case eHour:
			sort(pComp, eHour, compareByHour);
			break;
		case eDate:
			sort(pComp, eDate, compareByDate);
			break;
		case eOriginCode:
			sort(pComp, eOriginCode, compareByOriginCode);
			break;
		case eDestCode:
			sort(pComp, eDestCode, compareByDestCode);
			break;
	}
}

void	sort(Company* pComp, eSortType sortType, void (*compare)(void*)) {
	qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight**), compare);
	pComp->sortType = sortType;
}

// ====================================
