#ifndef __FILEWRITE__
#define __FILEWRITE__

#include "AirportManager.h"
#include "Company.h"

void writeAirportsToFile(AirportManager* pManager);
void writeCompanyToFile(Company* pComp);

void readCompanyFromFile();

#endif