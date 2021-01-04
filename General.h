#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#define CODE_LENGTH 3

// a value not supposed in stack and queue
#define		EMPTY	0x7FFFFFFF
#define		EXIT	-1

// new types
typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

//==============================

void	generalArrayFunction(void* arr, int length, int elementSize, void(*func)(void*));
char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str,int* pCount,int* pTotalLength);

#endif

