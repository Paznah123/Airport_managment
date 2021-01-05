#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileWrite.h"
#include "AirportManager.h"
#include "Company.h"
#include "listGen.h"

void readFiles(AirportManager* pManager, Company* pComp) {
	char* fileName = "airport_authority.txt";
	FILE* fp = fopen(fileName, "r");
	char* binFileName = "company.bin";
	FILE* fBinp = fopen(binFileName, "rb");

	if (fp) {
		readManagerFromTextFile(pManager);
	}
	else
		initManager(pManager);
	if (fBinp) {
		readCompanyFromBinFile(pComp);
	}
	else
		initCompany(pComp);
}

// ==========================================

void writeManagerToTextFile(AirportManager* pManager) {
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

void readManagerFromTextFile(AirportManager* pManager)
{
	pManager->headList = (NODE*)malloc(sizeof(NODE));
	pManager->headList->next = NULL;
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

		addLNodeToList(pManager->headList, airport, inputLocationOfAirport);
	}
	fclose(fp);
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
	FILE* fB = fopen("company.bin", "rb");
	int companyNameLength;
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&pComp->headDate);
	pComp->sortType = 0;
	
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
		L_push(&pComp->headDate->next, &f1->date);
	}
}

// ==========================================
