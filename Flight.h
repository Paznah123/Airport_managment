#pragma once

#include "AirportManager.h"
#include "Date.h"
#include "General.h"

//==============================

typedef struct
{
	char		originCode[CODE_LENGTH + 1];
	char		destCode[CODE_LENGTH + 1];
	int			hour;
	Date		date;
} Flight;

//==============================

Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg);
int			isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int			countFlightsInRoute(Flight** arr, int size,const char* codeSource, const char* codeDest);
int			getFlightHour();
void		initFlight(Flight* pFlight, const AirportManager* pManager);
void		printFlight(const DATA data);
void		freeFlight(DATA data);

//==============================
