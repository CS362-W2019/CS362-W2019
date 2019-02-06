#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testOutpost() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing outpost====\n");

	// -------------------------------------------- //
	// Testing outpost card
	// -------------------------------------------- //
	printf("\n--Testing outpost played--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	cardEffect(outpost, choice1, choice2, choice3, &testState, handpos, &bonus);
	if (testState.outpostPlayed ==  originalState.outpostPlayed + 1) {
		printf("PASSED - Outpost flag set\n");
		passed++;
	}
	else
		printf("FAILED - Outpost flag: %d (originally %d)\n", testState.outpostPlayed, originalState.outpostPlayed);

	printf("\n--Testing outpost discarded--\n");
	if (testState.discardCount[0] ==  originalState.discardCount[0] - 1) {
		printf("PASSED - Outpost dicarded\n");
		passed++;
	}
	else
		printf("FAILED - Discard count: %d (originally %d)\n", testState.discardCount[0], originalState.discardCount[0]);	
		
	printf("\nTests passed: %d/2\n\n", passed);
}

int main(int argc, char** argv) {
	testOutpost();
	return 0;
}