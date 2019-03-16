/* Random tests village card */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"



int main() {
	printf("----------------------- Random Testing: Village Card --------------\n");

	srand(time(NULL));

	int randomTestNumber = 0;
	int draw1Card = 0;
	int increaseActions = 0;

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };

	while (randomTestNumber < 2000)
	{
		int players = (rand() % MAX_PLAYERS-1) + 2;
		struct gameState state;

		initializeGame(players, k, rand(), &state);

		int player = rand() % players;

		int bonus = -1;
		int choice1 = -1;
		int choice2 = -1;
		int choice3 = -1;
		int handPos = rand() % MAX_HAND;

		struct gameState orig;
		memcpy(&orig, &state, sizeof(struct gameState));

		cardEffect(14, choice1, choice2, choice3, &state, handPos, &bonus);

		if (state.handCount[player] != orig.handCount[player] )
		{
			printf("Player %d, handPos %d, Test Failed Draw 1 Card.\n", player, handPos);
			draw1Card++;
		}

		if(state.numActions != orig.numActions + 2)
		{
			printf("Player %d, handPos %d, Test Failed to increase the number of Actions by 2.\n", player, handPos);
			increaseActions++;
		}	
		
		randomTestNumber++;
	}

	printf("Number of failed Draw 1 Cards Test: %d\nNumber of failed Add 2 actions: %d\n", draw1Card, increaseActions);

	return(0);

}

