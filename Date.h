#pragma once

#include "LinkedList.h"

#define MIN_YEAR 2020

//==============================

typedef struct
{
	int			day;
	int			month;
	int			year;
} Date;

//==============================

int		checkDate(char* date, Date* pDate);
void	getCorrectDate(Date* pDate);
void	printDate(const Date* pDate);

//==============================

