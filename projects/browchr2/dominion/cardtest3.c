#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testSteward() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing steward====\n");

	// -------------------------------------------- //
	// Testing trash 2 cards
	// -------------------------------------------- //
	printf("\n--Testing trash 2 cards--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  originalState.handCount[0] - 3 &&
		testState.discardCount[0] == originalState.discardCount[0]) {
		printf("PASSED - Net 3 cards removed: 2 trashed, 1 played\n");
		passed++;
	}
	else {
		printf("FAILED - Steward card added to played card but not removed from hand\n");
		printf("         Hand count: %d (originally %d)\n", testState.handCount[0], originalState.handCount[0]);
		printf("         Discard count: %d (originally %d)\n", testState.discardCount[0], originalState.discardCount[0]);
	}

	// -------------------------------------------- //
	// Testing +2 coins
	// -------------------------------------------- //
	printf("\n--Testing +2 coins--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	
	choice1 = 2;

	cardEffect(steward, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.coins ==  originalState.coins + 2) {
		printf("PASSED - Gained 2 coins\n");
		passed++;
	}
	else
		printf("FAILED - Coins: %d (originally %d)\n", testState.coins, originalState.coins);

	// -------------------------------------------- //
	// Testing +2 cards
	// -------------------------------------------- //
	printf("\n--Testing +2 cards--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	
	choice1 = 1;

	cardEffect(steward, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  originalState.handCount[0] + 1) {
		printf("PASSED - Net 1 added to hand. 2 new cards added, 1 moved to played\n");
		passed++;
	}
	else {
		printf("FAILED - Steward card added to played card but not removed from hand\n");
		printf("         Hand count: %d (originally %d)\n", testState.handCount[0], originalState.handCount[0]);
		printf("         Played count: %d (originally %d)\n", testState.playedCardCount, originalState.playedCardCount);
	}

	printf("\n--Testing played card count--\n");
	if (testState.playedCardCount ==  originalState.playedCardCount + 1) {
		printf("PASSED - Steward card added to played cards\n");
		passed++;
	}
	else
		printf("FAILED - Steward card not added to played cards\n");

	printf("\nTests passed: %d/4\n\n", passed);
}

int main(int argc, char** argv) {
	testSteward();
	return 0;
}