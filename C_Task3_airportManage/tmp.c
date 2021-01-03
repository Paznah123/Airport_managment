#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

typedef enum
{
	eUnsorted, eSortByHour, eSortByDate, eSortBySrc, eSortByDest, eNumOfSortFlights
} eSortFlights;

const char* sortFlightsArr[eNumOfSortFlights] = { "","Sort Flight By Hour", "Sort Flights By Date","Sort By Src IATA","Sort By Dest IATA" };

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightsDates.head.next = NULL;
	pComp->flightCount = 0;
	initList(&pComp->flightsDates);
	pComp->sortType = eUnsorted;
}

int	addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	char* date = initFlight(pComp->flightArr[pComp->flightCount], pManager);
	pComp->flightCount++;
	addLNodeToList(&pComp->flightsDates.head, date, inputLocationOfDate);
	return 1;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	printf("printing LinkedList of dates:\n");
	printList(&pComp->flightsDates.head, printDateLinkedList);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
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

	printf("from %s to %s\n", codeOrigin, codeDestination);
}



void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
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

LNode* inputLocationOfDate(const LNode* head, const void* data) {
	// if date exists in Linked List return NULL else return the last node that is not NULL
	if (head->next == NULL)
		return head;
	LNode* current = head;
	// in case there is only one date in LL
	if (current->next)
	{
		current = current->next;
		if (strcmp(current->data, data) == 0)
		{
			return NULL;
		}
	}
	while (current->next)
	{
		if (strcmp(current->data, data) == 0)
		{
			return NULL;
		}
		current = current->next;
	}
	return current;
}

void sortFlightsMenu(Company* pComp) {
	int option;
	int stop = 0;
	do
	{
		printf("\n\n");
		printf("Please choose one of the following options\n");
		for (int i = 1; i < eNumOfSortFlights; i++)
			printf("%d - %s\n", i, sortFlightsArr[i]);
		printf("%d - Quit\n", EXIT);
		scanf("%d", &option);
		//clean buffer
		char tav;
		scanf("%c", &tav);

		switch (option)
		{
		case eSortByHour:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByHour);
			pComp->sortType = eSortByHour;
			stop = 1;
			break;

		case eSortByDate:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByDate);
			pComp->sortType = eSortByDate;
			stop = 1;
			break;

		case eSortBySrc:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareBySrcIATA);
			pComp->sortType = eSortBySrc;
			stop = 1;
			break;

		case eSortByDest:
			qsort(pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByDestIATA);
			pComp->sortType = eSortByDest;
			stop = 1;
			break;


		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);


}

int compareByHour(const void* data1, const void* data2) {
	Flight* f1 = *(Flight**)data1;
	Flight* f2 = *(Flight**)data2;
	if (f1->hour < f2->hour)
		return -1;
	if (f1->hour > f2->hour)
		return 1;
	return 0;
}
int compareByDate(const void* data1, const void* data2) {
	Flight* f1 = *(Flight**)data1;
	Flight* f2 = *(Flight**)data2;
	return compare_dates(&f1->date, &f2->date);
}
int compareBySrcIATA(const void* data1, const void* data2) {
	Flight* f1 = *(Flight**)data1;
	Flight* f2 = *(Flight**)data2;
	return strcmp(&f1->originCode, &f2->originCode);
}

int compareByDestIATA(const void* data1, const void* data2) {
	Flight* f1 = *(Flight**)data1;
	Flight* f2 = *(Flight**)data2;
	return strcmp(&f1->destCode, &f2->destCode);

}

Flight* findFlight(const AirportManager* pManager, Company* pComp) {

	switch (pComp->sortType)
	{
	case eUnsorted:
		printf("the array is not sorted");

		break;

	case eSortByHour:
	{
		int hour;
		hour = getFlightHour();
		Flight f;
		Flight* fP = &f;
		Flight** fPP = &fP;
		if (!fP)
			break;
		if (!fPP)
			break;
		fP->hour = hour;
		fPP = (Flight**)bsearch(fPP, pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByHour);
		printFlight(*fPP);
		break;
	}


	case eSortByDate:
	{
		Date date;
		getCorrectDate(&date);
		Flight f;
		Flight* fP = &f;
		Flight** fPP = &fP;
		if (!fP)
			break;
		if (!fPP)
			break;
		fP->date = date;
		fPP = (Flight**)bsearch(fPP, pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByDate);
		printFlight(*fPP);
		break;
	}
	case eSortBySrc:
	{
		Airport* pPortOr = setAiportToFlight(pManager, "Enter code of origin airport:");
		Flight f;
		Flight* fP = &f;
		Flight** fPP = &fP;
		if (!fP)
			break;
		if (!fPP)
			break;
		strcpy(fP->originCode, pPortOr->code);
		fPP = (Flight**)bsearch(fPP, pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareBySrcIATA);
		printFlight(*fPP);
		break;
	}


	case eSortByDest:
	{
		Airport* pPortDes = setAiportToFlight(pManager, "Enter code of destination airport:");
		Flight f;
		Flight* fP = &f;
		Flight** fPP = &fP;
		if (!fP)
			break;
		if (!fPP)
			break;
		strcpy(fP->destCode, pPortDes->code);
		fPP = (Flight**)bsearch(fPP, pComp->flightArr, pComp->flightCount, sizeof(pComp->flightArr), compareByDestIATA);
		printFlight(*fPP);
		break;
	}

	}
}
