/* cardtest1.c
 * Card tested: feast */

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

	printf("----------------------- Testing feast ----------------------\n");
	fflush(stdout);

	printf("Pick a card that is out of supply\n");
	fflush(stdout);
	//initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&preG, &G, sizeof(struct gameState));
	int player = preG.whoseTurn;
//	G.hand[player][0] = council_room;
	choice1 = great_hall; //supply is 0
	cardEffect(feast, choice1, choice2, choice3, &G, handPos, &bonus);
	//check whether the state has changed
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "State should not change\n");


	printf("Pick a card that is too expensive\n");
	initializeGame(numPlayers, k, seed, &G);
	player = G.whoseTurn; 
	choice1 = province;
	for (int i=0; i<5; i++)
		G.hand[player][i] = adventurer;
	memcpy(&preG, &G, sizeof(struct gameState));
	cardEffect(feast, choice1, choice2, choice3, &G, handPos, &bonus);
	//check whether the state has changed
	assertTrue(memcmp(&preG, &G, sizeof(struct gameState)), 0, "State should not change\n");
	
	printf("Player is able to buy a card\n");
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&preG, &G, sizeof(struct gameState));
	player = preG.whoseTurn; 
	choice1 = silver;
	cardEffect(feast, choice1, choice2, choice3, &G, handPos, &bonus);
	//check whether the player gained one card to the discard pile
	assertTrue(preG.discardCount[player]+1, G.discardCount[player], "Player adds one card to discard pile\n");
	int preTotal = preG.handCount[player] + preG.deckCount[player] + preG.discardCount[player] + preG.playedCardCount;
	int postTotal = G.handCount[player] + G.deckCount[player] + G.discardCount[player] + G.playedCardCount;
	assertTrue(preTotal+1, postTotal, "Player's total card count increases by 1\n");
	
	return 0;
}


