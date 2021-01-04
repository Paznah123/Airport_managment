#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sortUtil.h"
#include "Flight.h"
#include "Date.h"

const char* sortTypes[eNull - 1] = { "Sort By Hour", "Sort By Date",
								"Sort By Origin Code", "Sort By Destination Code" };

// ====================================

int sortMenu() {
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");

	for (int i = 0; i < eNull - 1; i++)
		printf("- %d - %s\n", i + 1, sortTypes[i]);

	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);

	//clean buffer
	char tav;
	scanf("%c", &tav);

	return option;
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

// ====================================

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

// ====================================

int compareByOriginCode(const DATA a, const DATA b) {
	Flight** flightA = (Flight**)a;
	Flight** flightB = (Flight**)b;

	return strcmp(&flightA[0]->originCode, &flightB[0]->originCode);
}

int compareByDestCode(const DATA a, const DATA b) {
	Flight** flightA = (Flight**)a;
	Flight** flightB = (Flight**)b;

	return strcmp(&flightA[0]->destCode, &flightB[0]->destCode);
}

// ====================================

int		compareAirportsByIATA(const DATA p1, const DATA p2)
{
	Airport* ap1 = (Airport*)p1;
	Airport* ap2 = (Airport*)p2;

	return strcmp(&ap1->code, &ap2->code);
}

// ====================================
