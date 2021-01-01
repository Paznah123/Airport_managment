#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"
#include "listGen.h"
#include "Airport.h"
#include "fileWrite.h"
#include <string.h>


typedef enum 
{ 
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination"};

#define EXIT			-1
//int menu();

int main()
{
	AirportManager	manager;
	Company			company;

	initManager(&manager);
	initCompany(&company);

	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
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
			//L_print(&manager.headList, printAirport);
			printAirports(&manager);
			//freeManager(&manager);
			//readCompanyFromFile();
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case EXIT:
			writeAirportsToFile(&manager);
			writeCompanyToFile(&company);
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

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}
//int main()
//{
//	Airport* air= malloc(sizeof(Airport));
//	strcpy(air->code,"AAA");
//	air->country = (char*)malloc(sizeof(char) * 6);
//	air->name = (char*)calloc(3, sizeof(char));
//	strcpy(air->country, "Israel");
//	strcpy(air->name, "Paz");
//	printAirport(air);
//	return 0;
//}