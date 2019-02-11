/* cardtest1.c
 * Card tested: council_room */

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
	int bonus = 0;
	char info[100];

	printf("----------------------- Testing council_room ----------------------\n");
	fflush(stdout);
	//test 10 times
	for (int i=0; i<10; i++)
	{
		//initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		int player = preG.whoseTurn;
//		printf("********************After Initialization: G****************************\n");
//		printf("handcount: %d\tplayedCardCount: %d\tplayedCard:%d\tdeckCount:%d\tdiscardCount%d\n",G.handCount[player], G.playedCardCount, G.playedCards[player], G.deckCount[player], G.discardCount[player]);
		G.hand[player][0] = council_room;
		memcpy(&preG,&G, sizeof(struct gameState));
		cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);
		

		//check whether three more cards are added to the hand
		assertTrue(preG.handCount[player]+3, G.handCount[player], "3 cards added to hand\n");
		printf("Old handCount: %d; New handCount: %d\n", preG.handCount[player], G.handCount[player]);
		fflush(stdout);
		
		//check whether council_room has been played
		assertTrue(G.playedCardCount,1, "1 card is played\n");
//		printf("Old playedCardCount: %d; New playedCardCount: %d\n", preG.playedCardCount, G.playedCardCount);
//		fflush(stdout);
		assertTrue(G.playedCards[0], council_room, "The played card is council_room\n");

		//check whether the total number of cards the player has remains unchanged
		int preTotal = preG.handCount[player] + preG.deckCount[player] + preG.discardCount[player] + preG.playedCardCount;
		int postTotal = G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount;
		assertTrue(preTotal, postTotal, "Player's total card count should remain unchanged\n");

		//check whether the player get one more buy
		assertTrue(preG.numBuys + 1, G.numBuys, "The played adds one more buy\n");

		//check whether every other player gets one more card to hand
		for (int j=0; j<numPlayers; j++)
		{
			if (player != j)
			{
				memset(info, '\0', sizeof(info));
				sprintf(info, "Player %d adds one more card to hand\n", j);
				assertTrue(preG.handCount[j]+1, G.handCount[j], info);
			}
		}
	}
	return 0;
}


