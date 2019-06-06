/* cardtest1.c
 * Card tested: adventurer */

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
	memset(info, '\0', sizeof(info));
	int player = preG.whoseTurn;

	printf("----------------------- Testing Adventurer ----------------------\n");
	fflush(stdout);
	//test 10 times
	for (int i=0; i<10; i++)
	{
		//initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);
		memcpy(&preG,&G, sizeof(struct gameState));

//		printf("********************After Initialization: G****************************\n");
//		printf("handcount: %d\tplayedCardCount: %d\tplayedCard:%d\tdeckCount:%d\tdiscardCount%d\n",G.handCount[player], G.playedCardCount, G.playedCards[player], G.deckCount[player], G.discardCount[player]);
	
		cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
		

		//check whether two more cards are added to the hand
		assertTrue(preG.handCount[player]+2, G.handCount[player], "2 cards added to hand\n");
		
		//check whether the total number of cards the player has remains unchanged
		int preTotal = preG.handCount[player] + preG.deckCount[player] + preG.discardCount[player];
		int postTotal = G.handCount[player] + G.deckCount[player] + G.discardCount[player];
		assertTrue(preTotal, postTotal, "Player's total card count should remain unchanged\n");
		printf("Expected total card count: %d; Actual total card count: %d\n", preTotal, postTotal);
		fflush(stdout);

		//check the two cards added to the hand are treasure cards
		int count = G.handCount[player];
		int card1 = G.hand[player][count-2];
		int card2 = G.hand[player][count-1];
		assertTrue(card1==copper || card1==silver || card1==gold,1, "first card added is a treasure card\n");
		assertTrue(card2==copper || card2==silver || card2==gold,1, "second card added is a treasure card\n");
	}
	return 0;
}


