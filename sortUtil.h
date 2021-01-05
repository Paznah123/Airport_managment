#pragma once

#include "General.h"

//==============================

typedef enum
{
	eHour = 1, eDate, eOriginCode, eDestCode, eNull
} eSortType;

//==============================

int		sortMenu();
int		compareByHour(const DATA a, const DATA b);
int		compareByDate(const DATA a, const DATA b);
int		compareByOriginCode(const DATA a, const DATA b);
int		compareByDestCode(const DATA a, const DATA b);
int		compareAirportsByIATA(const DATA p1, const DATA p2);

// ====================================
