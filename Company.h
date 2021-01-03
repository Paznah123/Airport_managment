#ifndef __COMP__
#define __COMP__

#include "Date.h"
#include "Flight.h"
#include "AirportManager.h"

//==============================

typedef enum
{
	sortHour=1 , sortDate , sortOriginCode, sortDestCode , sortNull
} eSortType;

typedef struct
{
	char*		name;
	NODE*		headDate;
	NODE*		listDate;
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
void	sortFlightList(Company* pComp);
int		compareByHour(const DATA a, const DATA b);
int		compareByDate(const DATA a, const DATA b);
int		compareByOriginCode(const DATA a, const DATA b);
int		compareByDestCode(const DATA a, const DATA b);

#endif

