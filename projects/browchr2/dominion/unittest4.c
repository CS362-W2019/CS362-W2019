#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testDrawCard() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing drawCard====\n");

	// -------------------------------------------- //
	// Testing empty deck and empty discard
	// -------------------------------------------- //
	printf("\n--Testing empty deck and discard--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.deckCount[0] = 0;
	testState.discardCount[0] = 0;
	int result = drawCard(0, &testState);
	if (result == -1) {
		printf("PASSED - Empty deck and discard, returned -1\n");
		passed++;
	}
	else
		printf("FAILED - Attempted to draw card from empty deck and discard\n");

	// -------------------------------------------- //
	// Testing empty deck and with discard
	// -------------------------------------------- //
	printf("\n--Testing empty deck with discard--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.deckCount[0] = 0;
	testState.discardCount[0] = 2;
	testState.discard[0][0] = copper;
	testState.discard[0][1] = copper;
	drawCard(0, &testState);
	if (testState.deckCount[0] == 1 && testState.discardCount[0] == 0) {
		printf("PASSED - Added discard to deck and then drew card into hand\n");
		passed++;
	}
	else
		printf("FAILED - Discard count: %d, deck count: %d\n", testState.discardCount[0], testState.deckCount[0]);	

	if (testState.discard[0][0] == -1 && testState.discard[0][1] == -1) {
		printf("PASSED - All discard set to -1\n");
		passed++;	
	}
	else
		printf("FAILED - Discard not set to -1\n");

	// -------------------------------------------- //
	// Testing with deck and increased hand count
	// -------------------------------------------- //
	printf("\n--Testing with deck and increased hand count--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.deckCount[0] = 1;
	testState.deck[0][0] = copper;
	drawCard(0, &testState);
	if (testState.deckCount[0] == 0 && testState.handCount[0] == originalState.handCount[0] + 1) {
		printf("PASSED - Deck cound decreased and hand count increased by 1\n");
		passed++;
	}
	else
		printf("FAILED - Deck count: %d, hand count: %d\n", testState.deckCount[0], testState.handCount[0]);

	printf("\nTests passed: %d/4\n\n", passed);
}

int main(int argc, char** argv) {
	testDrawCard();
	return 0;
}