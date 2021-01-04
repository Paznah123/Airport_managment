#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	fwrite(&pComp->name, sizeof(char) * nameLen, 1, fp);
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
	*/
	fclose(fp);
}


// needs fix !
void readManagerFromTextFile(AirportManager* pManager)
{
	char* fileName = "airport_authority.txt";
	FILE* fp;

	// Open file for writing
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}
	fscanf(fp, "%d \n", &pManager->count);

	for (int i = 0; i < pManager->count; i++)
	{
		Airport* airport = (Airport*)malloc(sizeof(Airport));
		char temp1[MAX_STR_LEN];
		char temp2[MAX_STR_LEN];

		fgets(temp1, MAX_STR_LEN, fp);
		fgets(temp2, MAX_STR_LEN, fp);

		temp1[strlen(temp1) - 1] = '\0';
		temp2[strlen(temp2) - 1] = '\0';

		fscanf(fp, "%s \n", airport->code);

		airport->name = _strdup(&temp1);
		airport->country = _strdup(&temp2);

		pManager->listPtr = L_insertLast(pManager->listPtr, airport);
	}

	fclose(fp);
}
