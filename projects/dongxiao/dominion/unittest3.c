/* unittest3.c
 * Function tested: int playCard */

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
	int numPlayers = 2;
	int seed = 0;
	int k[10] = {adventurer, feast, gardens, mine, smithy, village, baron, steward, outpost, treasure_map};
	struct gameState G,preG;
	int handPos = 0;
	int choice1 = 1;
	int choice2 = 2;
	int choice3 = 4;
	char info[100];
	memset(info, '\0', sizeof(info));

	printf("-----------------------Testing playCard----------------------\n");
	fflush(stdout);
	//initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	//When the phase is not 0
	G.phase = 1;
	memcpy(&preG,&G, sizeof(struct gameState)); 
	assertTrue(playCard(handPos, choice1, choice2, choice3, &G), -1,"phase is 1\n");
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "phase is 1, state not altered\n");

	//When phase is 0, and numActions is 0
	G.phase = 0; 
	G.numActions = 0;
	memcpy(&preG,&G, sizeof(struct gameState)); 
	assertTrue(playCard(handPos, choice1, choice2, choice3, &G), -1,"numActions is 0\n");
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "numActions is 0, state not altered\n");

	// Play a non-action card
	G.phase = 0;
	G.numActions = 1;
	G.hand[0][0] = estate;
	memcpy(&preG,&G, sizeof(struct gameState)); 
	assertTrue(playCard(handPos, choice1, choice2, choice3, &G), -1,"Not an action card\n");
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "Not an action card, state not altered\n");
	
	//Play gardens
	G.phase = 0;
	G.numActions = 1;
	G.hand[0][0] = gardens;
	memcpy(&preG,&G, sizeof(struct gameState)); 
	assertTrue(playCard(handPos, choice1, choice2, choice3, &G), -1,"Play gardens\n");
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "Play gardens, state not altered\n");
	
	//play 10 random action card
	srand(time(0));
	for (int i=0; i<10; i++)
	{
		initializeGame(numPlayers, k, seed, &G);
		G.numActions = 1;
		G.hand[0][0] = rand()%20 + 7;
		memcpy(&preG,&G, sizeof(struct gameState));
		if (playCard(handPos, choice1, choice2, choice3, &G) == -1)
			assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "Invalid play, state not altered\n");
		else
		{
			int card = handCard(handPos, &preG);
			int bonus = 0;
			cardEffect(card, choice1, choice2, choice3, &preG, handPos, &bonus);
			(preG.numActions)--;
			updateCoins(preG.whoseTurn, &preG, bonus);
			assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "Valid play, state not altered\n");
		}
	}
	return 0;
}


