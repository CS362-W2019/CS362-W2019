/* unittest1.c
 * Function tested: int compare(const void *a, const void* b)*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

/*************************************************************************
 * Function: assertTrue
 * Parameters: testResult: an int; expectedResult: an int; info: a string
 * Description: If testResult is the same as expectedResult, then the "TEST
 * 		SUCCESSFULLY COMPLETED" will be printed to stdout. Otherwise,
 * 		"TEST FAILED" will be printed out. The message is followed
 * 		by the testing conditions stated in info.
 **************************************************************************/

void assertTrue(int testResult, int expectedResult, char* info)
{
	if (testResult == expectedResult) 
	{
		printf("TEST SUCCESSFULLY COMPLETED: ");
		fflush(stdout);
	}
	else
	{
		printf("TEST FAILED: ");
		fflush(stdout);
	}
	printf(info);
}


int main()
{
	int a, b;
	char info[24];

	//a=0 and b=0
	a = 0;
	b = 0;
	sprintf(info,"a = %d, b = %d\n", a, b);
	assertTrue(compare((void*)&a, (void*)&b), 0,info);
/*
	//a=10 and b=0
	a = 10;
	b = 0;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), 1, info);

	//a=0 and b=10
	a = 0;
	b = 10;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), -1, info);

	//a=10 and b=-10
	a = 10;
	b = -10;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), 1, info);

	//a=-10 and b=10
	a = -10;
	b = 10;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), -1, info);

	//a=INT_MIN and b=INT_MIN
	a = INT_MIN;
	b = INT_MIN;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), 0,info);
	
	//a=INT_MAX and b=INT_MAX
	a = INT_MAX;
	b = INT_MAX;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), 0,info);
	
	//a=INT_MAX and b=INT_MIN
	a = INT_MAX;
	b = INT_MIN;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), 1, info);

	//a=INT_MIN and b=INT_MAX
	a = INT_MIN;
	b = INT_MAX;
	info = sprintf("a = %d, b = %d\n", a, b);
	assertTure(compare((void*)&a, (void*)&b), -1, info);
*/	
	return 0;
}


