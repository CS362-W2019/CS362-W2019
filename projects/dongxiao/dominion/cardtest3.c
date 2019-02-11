/* cardtest3.c
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
	int numPlayers = 4;
	int seed = 0;
	int k[10] = {adventurer, feast, gardens, mine, smithy, council_room, baron, feast, outpost, treasure_map};
	struct gameState G,preG;
	int handPos = 0;
	int choice1 = 1;
	int choice2 = 2;
	int choice3 = 4;
	int bonus = 0;
	char info[100];

	printf("----------------------- Testing Council_room ----------------------\n");
	fflush(stdout);
	int i;
	//test 10 times
	for (i=0; i<10; i++)
	{
		//initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		G.hand[0][0] = council_room;
		memcpy(&preG,&G, sizeof(struct gameState));
		int player = preG.whoseTurn;
		cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);
		
		/************************** DEBUG ***********************************/
		printf("********************preG****************************\n");
		printf("handcount: %d\tplayedCardCount: %d\tplayedCard:%d\tdeckCount%d\tdiscardCount%d\n",preG.handCount[0], preG.playedCardCount, preG.playedCards[0], preG.deckCount[0], preG.discardCount[0]);
		printf("********************G****************************\n");
		printf("handcount: %d\tplayedCardCount: %d\tplayedCard:%d\tdeckCount%d\tdiscardCount%d\n",G.handCount[0], G.playedCardCount, G.playedCards[0], G.deckCount[0], G.discardCount[0]);

		//check whether three more cards are added to the hand
		assertTrue(preG.handCount[player]+3, G.handCount[player], "3 cards added to hand\n");
		
		//check whether the council_room card is played
		assertTrue(G.playedCardCount,1, "1 card is played\n");
		assertTrue(G.playedCards[0], council_room, "The played card is council_room\n");

		//check whether the current player's total card count remains unchanged
		int preTotal = preG.handCount[player] + preG.deckCount[player] + preG.discardCount[player] + preG.playedCardCount;
		int postTotal = G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount;
		assertTrue(preTotal, postTotal, "Player's total card count remains unchanged\n");
		
		//check whether the current player has one more buy
		assertTrue(preG.numBuys+1, G.numBuys, "Player gained one more buy\n");

		//check whether every other player adds one card to hand
		for (i=0; i<numPlayers; i++)
		{
			if (i != player)
			{
				memset(info, '\0', sizeof(info));
				sprintf(info, "player %d adds one card to hand\n", i);
				assertTrue(preG.handCount[i]+1, G.handCount[i], info);
				preTotal = preG.handCount[i] + preG.deckCount[i] + preG.discardCount[i];
				postTotal = G.handCount[i] + G.deckCount[i] + G.discardCount[i];
				memset(info, '\0', sizeof(info));
				sprintf(info, "player %d's total card count remains unchanged\n", i);
				assertTrue(preTotal, postTotal, info);
			}
		}

	}
	return 0;
}


