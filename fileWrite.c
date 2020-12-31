#include <stdio.h>
#include <stdlib.h>

#include "fileWrite.h"

#include "AirportManager.h"
#include "Company.h"

void writeAirportsToFile(AirportManager* pManager) {
	char* fileName = "airport_authority.txt";
	FILE* fp;

	// Open file for writing
	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}

	fprintf(fp, "%d\n", pManager->count);
	NODE* node = pManager->headList->next;
	for (int i = 0; i < pManager->count; i++) {
		Airport* airport = (Airport*)node->key;
		fprintf(fp, "%s\n%s\n%s\n",
			airport->name, airport->country, airport->code);
		node = node->next;
	}

	fclose(fp);
}

// ==========================================

void writeCompanyToFile(Company* pComp) {
	char* fileName = "comapny.bin";
	FILE* fp;

	// Open file for writing
	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}
	int nameLen = strlen(pComp->name);
	
	fwrite(&nameLen, sizeof(int), 1, fp);
	fwrite(&pComp->name, sizeof(char)* nameLen, 1, fp);
	fwrite(&pComp->flightCount, sizeof(int), 1, fp);
	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (fwrite(&pComp->flightArr[i], sizeof(Flight), 1, fp) != 1) {
			fclose(fp);
			return;
		}
	}

	fclose(fp);
}

void readCompanyFromFile()
{
	char* fileName = "comapny.bin";
	FILE* fp;

	// Open file for writing
	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}
	/*int nameLen = strlen(pComp->name);

	fread(&nameLen, sizeof(int), 1, fp);
	fread(&pComp->name, sizeof(char) * nameLen, 1, fp);
	fread(&pComp->flightCount, sizeof(int), 1, fp);
	*/
	for (int i = 0; i < 4; i++)
	{
		Flight flight;
		if (fread(&flight, sizeof(Flight), 1, fp) != 1) {
			fclose(fp);
			return;
		}
		printf("Flight: %s - %s - %d - %d//%d//%d", flight.originCode, 
			flight.destCode, flight.hour, flight.date.day, flight.date.month, flight.date.year);
	}

	fclose(fp);
}