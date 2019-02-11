/* unittest2.c
 * Function tested: int whoseTurn */

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
	int numPlayers = 4;
	int seed = 0;
	int k[10] = {adventurer, feast, gardens, mine, smithy, village, baron, steward, outpost, treasure_map};
	struct gameState G;
	char info[100];
	memset(info, '\0', sizeof(info));

	printf("-----------------------Testing whoseTurn----------------------\n");
	fflush(stdout);
	//initialize a game state and player cards
		

	for (int i=0; i<4; i++)
	{
		
		initializeGame(numPlayers, k, seed, &G);
		G.whoseTurn = i;
		memset(info, '\0', sizeof(info));
		sprintf(info, "Whose turn: %d\n", i);
		assertTrue(whoseTurn(&G), i,info);
	}
	return 0;
}


