#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testGainCard() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing gainCard====\n");

	// -------------------------------------------- //
	// Testing when supply is empty
	// -------------------------------------------- //
	printf("\n--Testing empty supply--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.supplyCount[copper] = 0;
	int result = gainCard(copper, &testState, 0, 0);
	if (result == -1) {
		printf("PASSED - Supply is empty, returned -1\n");
		passed++;
	}
	else
		printf("FAILED - Supply is empty, should return -1\n");
	
	// -------------------------------------------- //
	// Testing gainCard into deck
	// -------------------------------------------- //
	printf("\n--Testing deck flag--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	gainCard(smithy, &testState, 1, 0);
	
	// Test deck contains new card
	if (testState.deck[0][originalState.deckCount[0]] == smithy) {
		printf("PASSED - Last card in deck is correct\n");
		passed++;
	}
	else
		printf("FAILED - Last card in deck is incorrect\n");

	// Test deck count
	if (testState.deckCount[0] == originalState.deckCount[0] + 1) {
		printf("PASSED - deck count increased by 1\n");
		passed++;
	}
	else
		printf("FAILED - deck count increased by %d\n", originalState.deckCount[0] - testState.deckCount[0]);

	// -------------------------------------------- //
	// Testing gainCard into hand
	// -------------------------------------------- //
	printf("\n--Testing hand flag--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	gainCard(smithy, &testState, 2, 0);
	
	// Test hand contains new card
	if (testState.hand[0][originalState.handCount[0]] == smithy) {
		printf("PASSED - Last card in hand is correct\n");
		passed++;
	}
	else
		printf("FAILED - Last card in hand is incorrect\n");

	// Test hand count
	if (testState.handCount[0] == originalState.handCount[0] + 1) {
		printf("PASSED - Hand count increased by 1\n");
		passed++;
	}
	else
		printf("FAILED - Hand count increased by %d\n", originalState.handCount[0] - testState.handCount[0]);

	// -------------------------------------------- //
	// Testing gainCard into discard
	// -------------------------------------------- //
	printf("\n--Testing discard flag--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	gainCard(smithy, &testState, 0, 0);
	
	// Test discard contains new card
	if (testState.discard[0][originalState.discardCount[0]] == smithy) {
		printf("PASSED - Last card in discard is correct\n");
		passed++;
	}
	else
		printf("FAILED - Last card in discard is incorrect\n");

	// Test discard count
	if (testState.discardCount[0] == originalState.discardCount[0] + 1) {
		printf("PASSED - Discard count increased by 1\n");
		passed++;
	}
	else
		printf("FAILED - Discard count increased by %d\n", originalState.discardCount[0] - testState.discardCount[0]);

	// -------------------------------------------- //
	// Testing supply count changes
	// -------------------------------------------- //
	printf("\n--Testing supply count decreases--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	gainCard(copper, &testState, 0, 0);
	if (testState.supplyCount[copper] == originalState.supplyCount[copper] - 1) {
		printf("PASSED - Supply Count one fewer\n");
		passed++;
	}
	else
		printf("FAILED - Supply Count is %d instead of %d\n", testState.supplyCount[copper], originalState.supplyCount[copper] - 1);

	printf("\nTests passed: %d/8\n\n", passed);
}

int main(int argc, char** argv) {
	testGainCard();
	return 0;
}