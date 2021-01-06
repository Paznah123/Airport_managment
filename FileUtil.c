#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileUtil.h"
#include "AirportManager.h"
#include "Company.h"
#include "LinkedList.h"

void readFiles(AirportManager* pManager, Company* pComp) {
	char* fileName = "airport_authority.txt";
	FILE* f_txt = fopen(fileName, "r");
	char* binFileName = "company.bin";
	FILE* f_bin = fopen(binFileName, "rb");

	if (f_txt)
		readManagerFromTextFile(pManager);
	else
		initManager(pManager);

	if (f_bin)
		readCompanyFromBinFile(pComp);
	else
		initCompany(pComp);
}

// ==========================================

void writeManagerToTextFile(AirportManager* pManager) {
	char* fileName = "airport_authority.txt";
	FILE* fp;

	fp = fopen(fileName, "w+");
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
	char* fileName = "airport_authority.txt";
	FILE* fp;

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

		addLNodeToList(&pManager->airportList.head, airport, insertAirportToList);
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
	char* fileName = "company.bin";
	FILE* fB = fopen(fileName, "rb");
	if (fB == NULL) {
		printf("Cannot open file %s\n", fileName);
		return EXIT_FAILURE;
	}

	int companyNameLength;
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&pComp->dateList);
	pComp->datesNumber = 0;
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
		if (checkDateExists(&f1->date, pComp) == False) {
			L_insertAfter(&pComp->dateList.head, &f1->date);
		}
	}
}

// ==========================================
