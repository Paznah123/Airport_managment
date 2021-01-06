#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileUtil.h"
#include "AirportManager.h"
#include "Company.h"
#include "LinkedList.h"

void readFiles(AirportManager* pManager, Company* pComp) {

	if (fopen("airport_authority.txt", "r"))
		readManagerFromTextFile(pManager);
	else
		initManager(pManager);

	if (fopen("company.bin", "rb"))
		readCompanyFromBinFile(pComp);
	else
		initCompany(pComp);
}

// ==========================================

void writeManagerToTextFile(AirportManager* pManager) {
	char* fileName = "airport_authority.txt";
	FILE* fp = fopen(fileName, "w+");

	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}

	fprintf(fp, "%d\n", pManager->count);
	NODE* node = &pManager->airportList.head;
	for (int i = 0; i < pManager->count; i++) {
		Airport* airport = (Airport*)node->next->key;
		fprintf(fp, "%s\n%s\n%s\n",
			airport->name, airport->country, airport->code);
		node = node->next;
	}

	fclose(fp);
}

// ==========================================

void readManagerFromTextFile(AirportManager* pManager)
{
	L_init(&pManager->airportList);
	pManager->count = 0;

	char* fileName = "airport_authority.txt";
	FILE* fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}
	fscanf(fp, "%d \n", &pManager->count);

	for (int i = 0; i < pManager->count; i++)
	{
		Airport* airport = (Airport*)malloc(sizeof(Airport));
		
		airport->name = getValueFromFile(fp);
		airport->country = getValueFromFile(fp);
		
		fscanf(fp, "%s \n", airport->code);

		insertNodeToList(&pManager->airportList.head, airport, chooseAirportPlace);
	}
	fclose(fp);
}

char* getValueFromFile(FILE* file) {
	
	char temp[MAX_STR_LEN];
	fgets(temp, MAX_STR_LEN, file);
	temp[strlen(temp) - 1] = '\0';

	return  _strdup(&temp);
}

// ==========================================

int writeCompanyToBinFile(Company* pComp) {
	FILE* fb = fopen("company.bin", "wb");
	if (!fb)return 0;

	int companyNameLength = strlen(pComp->name) + 1;

	fwrite(&companyNameLength, sizeof(int), 1, fb);
	fwrite(pComp->name, sizeof(char), companyNameLength, fb);
	fwrite(&pComp->flightCount, sizeof(int), 1, fb);
	fwrite(&pComp->sortType, sizeof(int), 1, fb);

	for (int i = 0; i < pComp->flightCount; i++)
	{
		fwrite(pComp->flightArr[i], sizeof(Flight), 1, fb);
	}
	fclose(fb);
}

// ==========================================

int readCompanyFromBinFile(Company* pComp) {
	char* fileName = "company.bin";
	FILE* fB = fopen(fileName, "rb");
	if (fB == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}

	int companyNameLength;
	L_init(&pComp->dateList);
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->sortType = eNull;
	
	fread(&companyNameLength, sizeof(int), 1, fB);
	pComp->name = (char*)malloc(companyNameLength * sizeof(char));
	fread(pComp->name, sizeof(char), companyNameLength, fB);
	fread(&pComp->flightCount, sizeof(int), 1, fB);
	fread(&pComp->sortType, sizeof(int), 1, fB);

	pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		Flight* f1 = (Flight*)malloc(sizeof(Flight));
		if (!f1)
			return 0;
		fread(f1, sizeof(Flight), 1, fB);
		pComp->flightArr[i] = f1;
		if (checkDateExists(&f1->date, pComp) == False) {
			insertNodeToList(&pComp->dateList.head, &f1->date, chooseDatePlace);
		}
	}
}

// ==========================================
