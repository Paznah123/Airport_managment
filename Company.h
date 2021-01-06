#pragma once

#include "Date.h"
#include "Flight.h"
#include "AirportManager.h"
#include "sortUtil.h"

//==============================

typedef struct
{
	char*		name;
	LIST		dateList;
	int			datesNumber;
	int			flightCount;
	Flight**	flightArr;
	eSortType	sortType;
} Company;

//==============================

BOOL	checkDateExists(Date* date, Company* pComp);
BOOL	isDateEqual(Date* date, Date* dateInList);
int		addFlight(Company* pComp, const AirportManager* pManager);
void	initCompany(Company* pComp);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
void	searchFlight(Company* pComp, eSortType sortType);
void	sortFlightList(Company* pComp);
void	sort(Company* pComp, eSortType sortType, void (*compare)(void*));

void printDates(Company* pComp);

// ====================================
