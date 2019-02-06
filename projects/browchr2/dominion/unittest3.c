#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void resetTestState(struct gameState* testState, struct gameState* originalState) {
	memcpy(testState, originalState, sizeof(struct gameState));
	int i;

	// Set limits
	testState->handCount[0] = 6;
	testState->discardCount[0] = 6;
	testState->deckCount[0] = 6;

	// Fill with non-scoring copper
	for (i = 0; i < 6; i++) {
		testState->hand[0][i] = copper;
		testState->discard[0][i] = copper;
		testState->deck[0][i] = copper;
	}
}

void testScoreFor() {
	struct gameState originalState, testState;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	int score;
	int passed = 0;
	initializeGame(2, k, 1000, &originalState);

	printf("====Testing scoreFor====\n");

	// -------------------------------------------- //
	// Testing for no score
	// -------------------------------------------- //
	printf("\n--Testing no score--\n");
	resetTestState(&testState, &originalState);
	score = scoreFor(0, &testState);
	if (score == 0) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 0\n", score);

	// -------------------------------------------- //
	// Testing hand only score
	// -------------------------------------------- //
	printf("\n--Testing hand only score--\n");
	resetTestState(&testState, &originalState);

	testState.hand[0][0] = curse;		// -1
	testState.hand[0][1] = estate;		// +1
	testState.hand[0][2] = duchy;		// +3
	testState.hand[0][3] = province;	// +6
	testState.hand[0][4] = great_hall;	// +1
	testState.hand[0][5] = gardens;		// +1 (18 cards/10, rounded down)

	score = scoreFor(0, &testState);
	if (score == 11) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 11\n", score);
	
	// -------------------------------------------- //
	// Testing discard only score
	// -------------------------------------------- //
	printf("\n--Testing discard only score--\n");
	resetTestState(&testState, &originalState);

	testState.discard[0][2] = duchy;

	score = scoreFor(0, &testState);
	if (score == 3) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 3\n", score);

	// -------------------------------------------- //
	// Testing deck only score
	// -------------------------------------------- //
	printf("\n--Testing deck only score--\n");
	resetTestState(&testState, &originalState);

	testState.deck[0][3] = province;

	score = scoreFor(0, &testState);
	if (score == 6) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 6\n", score);

	// -------------------------------------------- //
	// Testing hand and discard score
	// -------------------------------------------- //
	printf("\n--Testing hand and discard score--\n");
	resetTestState(&testState, &originalState);

	testState.hand[0][1] = estate;
	testState.discard[0][2] = duchy;

	score = scoreFor(0, &testState);
	if (score == 4) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 4\n", score);

	// -------------------------------------------- //
	// Testing discard and deck score
	// -------------------------------------------- //
	printf("\n--Testing discard and score--\n");
	resetTestState(&testState, &originalState);

	testState.discard[0][2] = duchy;
	testState.deck[0][3] = province;

	score = scoreFor(0, &testState);
	if (score == 9) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 9\n", score);
	
	// -------------------------------------------- //
	// Testing hand and deck score
	// -------------------------------------------- //
	printf("\n--Testing hand and deck score--\n");
	resetTestState(&testState, &originalState);

	testState.hand[0][1] = estate;
	testState.deck[0][3] = province;

	score = scoreFor(0, &testState);
	if (score == 7) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 7\n", score);

	// -------------------------------------------- //
	// Testing hand, discard, and deck score
	// -------------------------------------------- //
	printf("\n--Testing hand, discard, and deck score--\n");
	resetTestState(&testState, &originalState);

	testState.hand[0][1] = estate;
	testState.discard[0][2] = duchy;
	testState.deck[0][3] = province;

	score = scoreFor(0, &testState);
	if (score == 10) {
		printf("PASSED - Score is %d\n", score);
		passed++;
	}
	else
		printf("FAILED - Score is %d but should be 10\n", score);


	printf("\nTests passed: %d/8\n\n", passed);
}

int main(int argc, char** argv) {
	testScoreFor();
	return 0;
}