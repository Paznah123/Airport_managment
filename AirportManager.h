#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "listGen.h"

//==============================

typedef struct
{
	NODE* headList;
	NODE* listPtr;
	int count;
}AirportManager;

//==============================

Airport*	findAirportByCode(const AirportManager* pManager, const char* code);
int			initManager(AirportManager* pManager);
int			addAirport(AirportManager* pManager);
int			checkUniqeCode(const char* code, const AirportManager* pManager);
void		setAirport(Airport* pPort, AirportManager* pManager);
void		freeManager(AirportManager* pManager);
void		printAirports(const AirportManager* pManager);

//==============================

#endif