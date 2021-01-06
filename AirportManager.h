#pragma once

#include "Airport.h"
#include "LinkedList.h"

//==============================

typedef struct
{
	LIST airportList;
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
