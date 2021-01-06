#pragma once

#include "AirportManager.h"
#include "Company.h"

// ==============================


void	readFiles(AirportManager* pManager, Company* pComp);
void	writeManagerToTextFile(AirportManager* pManager);
void	readManagerFromTextFile(AirportManager* pManager);
int		readCompanyFromBinFile(Company* pComp);
int		writeCompanyToBinFile(Company* pComp);
char* getValueFromFile(FILE* file);

// ====================================
