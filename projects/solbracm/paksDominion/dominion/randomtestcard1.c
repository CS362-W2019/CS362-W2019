/* Random tests smithy */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"



int main() {
	printf("----------------------- Random Testing: Smithy Card --------------\n");

	srand(time(NULL));

	int randomTestNumber = 0;
	int draw3Cards = 0;

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

		cardEffect(13, choice1, choice2, choice3, &state, handPos, &bonus);
		if (state.handCount[player] != orig.handCount[player] + 2)
		{
			printf("Player %d, handPos %d, Test Failed Draw 3 Cards.\n", player, handPos);
			draw3Cards++;
		}
		randomTestNumber++;
	}
	printf("Number of failed Draw 3 Cards Test: %d\n", draw3Cards);

	return(0);

}
