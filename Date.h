#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

#include "listGen.h"

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

#endif
