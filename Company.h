#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum
{
	sortHour , sortDate , sortOriginCode, sortDestCode , sortNull
} eSortType;

typedef struct
{
	char*		name;
	NODE* listDate;
	int datesNumber;
	int			flightCount;
	Flight**	flightArr;
	eSortType sortType;
}Company;

void	initCompany(Company* pComp);
int		addFlight(Company* pComp,const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
BOOL    checkDateExists(Date* date, NODE* listDate);
#endif

