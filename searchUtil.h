#pragma once

#include "Company.h"
#include "Flight.h"

// ==========================

void	searchFlight(Company* pComp, eSortType searchType);
void	bSearchByHour(Company* pComp, Flight* flight);
void	bSearchByDate(Company* pComp, Flight* flight);
void	bSearchByOriginCode(Company* pComp, Flight* flight);
void	bSearchByDestCode(Company* pComp, Flight* flight);

// ==========================
