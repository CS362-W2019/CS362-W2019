#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void testIsGameOver() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int result;
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing isGameOver====\n");

	// -------------------------------------------- //
	// Testing when province card supply is empty
	// -------------------------------------------- //
	printf("\n--Testing province card supply--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.supplyCount[province] = 0;
	result = isGameOver(&testState);
	if (result == 1) {
		printf("PASSED - Game ended when province supply was empty\n");
		passed++;
	}
	else
		printf("FAILED - Province supply is empty but game is not over\n");

	// -------------------------------------------- //
	// Testing fewer than three empty supplies
	// -------------------------------------------- //
	printf("\n--Testing fewer than three empty supplies--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.supplyCount[adventurer] = 0;
	testState.supplyCount[smithy] = 0;
	result = isGameOver(&testState);
	if (result == 0) {
		printf("PASSED - Game did not end\n");
		passed++;
	}
	else
		printf("FAILED - Game ended with fewer than three empty supplies (excluding province)\n");

	// -------------------------------------------- //
	// Testing exactly three empty supplies
	// -------------------------------------------- //
	printf("\n--Testing exactly three empty supplies--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.supplyCount[adventurer] = 0;
	testState.supplyCount[smithy] = 0;
	testState.supplyCount[village] = 0;
	result = isGameOver(&testState);
	if (result == 1) {
		printf("PASSED - Game ended with exactly three empty supplies (excluding province)\n");
		passed++;
	}
	else
		printf("FAILED - Game did not end with exactly three empty supplies (excluding province)\n");

	// -------------------------------------------- //
	// Testing more than three empty supplies
	// -------------------------------------------- //
	printf("\n--Testing more than three empty supplies--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));
	testState.supplyCount[adventurer] = 0;
	testState.supplyCount[smithy] = 0;
	testState.supplyCount[village] = 0;
	testState.supplyCount[mine] = 0;
	result = isGameOver(&testState);
	if (result == 1) {
		printf("PASSED - Game ended with more than three empty supplies (excluding province)\n");
		passed++;
	}
	else
		printf("FAILED - Game did not end with more than three empty supplies (excluding province)\n");

	printf("\nTests passed: %d/4\n\n", passed);
}

int main(int argc, char** argv) {
	testIsGameOver();
	return 0;
}