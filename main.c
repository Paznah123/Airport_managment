#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Company.h"
#include "AirportManager.h"
#include "Airport.h"
#include "FileUtil.h"
#include "General.h"
#include "LinkedList.h"
#include "searchUtil.h"

int menu();

//==============================

typedef enum
{
	eAddFlight = 1, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest, eSortList, eSearchFlight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination", "Sort Flights", "Search Flight" };

//==============================

int main()
{
	AirportManager	manager;
	Company			company;

	readFiles(&manager, &company);

	int option;
	int stop = 0;

	do {
		option = menu();
		switch (option) {
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case eSortList:
			sortFlightList(&company);
			break;

		case eSearchFlight:
			searchFlight(&company, company.sortType);
			break;

		case EXIT:
			writeManagerToTextFile(&manager);
			writeCompanyToBinFile(&company);
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	freeManager(&manager);
	freeCompany(&company);

	return 1;
}

//==============================

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");

	for (int i = 0; i < eNofOptions - 1; i++)
		printf("- %d - %s\n", i + 1, str[i]);

	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);

	//clean buffer
	char tav;
	scanf("%c", &tav);

	return option;
}

//==============================

