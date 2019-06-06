/* unittest4.c
 * Function tested: int supplyCount */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("----------------------------------- Test supplyCount() --------------------------\n");
	fflush(stdout);
	int numPlayers = 4;
	int seed = 0;
	int k[10] = {adventurer, feast, gardens, mine, smithy, village, baron, steward, outpost, treasure_map};
	struct gameState G;
	char info[100];
	memset(info, '\0', sizeof(info));

	printf("-----------------------Testing whoseTurn----------------------\n");
	fflush(stdout);

	//generate an array of random int
	int counts[27];
	srand(time(0));
	int i;
	for (i=0; i< 27; i++)
		counts[i] = rand();

	//copy over the supply counts
	initializeGame(numPlayers, k, seed, &G); 
	for (i=0; i<27; i++)
		G.supplyCount[i] = counts[i];
	
	//check supplyCount function
	for (i=0; i<27; i++)
	{
		memset(info, '\0', sizeof(info));
		sprintf(info, "Card %d with supply of %d\n", i, counts[i]);
		assertTrue(supplyCount(i,&G), counts[i],info);
		
	}
	
	return 0;
}


