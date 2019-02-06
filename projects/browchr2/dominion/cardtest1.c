#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testSmithy() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing smithy====\n");

	// -------------------------------------------- //
	// Testing smithy card
	// -------------------------------------------- //
	printf("\n--Testing hand count--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.hand[0][0] = smithy;
	cardEffect(smithy, choice1, choice2, choice3, &testState, handpos, &bonus);
	if (testState.handCount[0] ==  originalState.handCount[0] + 2) {
		printf("PASSED - Net 2 added to hand. 3 new cards added, 1 moved to played\n");
		passed++;
	}
	else {
		printf("FAILED - Smithy card added to played card but not removed from hand\n");
		printf("         Hand count: %d (originally %d)\n", testState.handCount[0], originalState.handCount[0]);
		printf("         Played count: %d (originally %d)\n", testState.playedCardCount, originalState.playedCardCount);
	}

	printf("\n--Testing played card count--\n");
	if (testState.playedCardCount ==  originalState.playedCardCount + 1) {
		printf("PASSED - Smithy card added to played cards\n");
		passed++;
	}
	else
		printf("FAILED - Smithy card not added to played cards\n");
		
	printf("\nTests passed: %d/2\n\n", passed);
}

int main(int argc, char** argv) {
	testSmithy();
	return 0;
}