/* unittest1.c
 * Function tested: int* kingdomCards */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
	int k[10] = {adventurer, feast, gardens, mine, smithy, village, baron, steward, outpost, treasure_map};
	int *r = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);

	char info[20];
	for (int i=0; i<10; i++)
	{
		memset(info, '\0', sizeof(info));
		sprintf(info, "k[%d]=%d, r[%d]=%d\n", i,k[i],i,r[i]);
		assertTrue(k[i], r[i],info);
	}
	free(r);
	return 0;
}


