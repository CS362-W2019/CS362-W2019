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

	printf("====Testing adventurer====\n");

	// -------------------------------------------- //
	// Testing shuffle required
	// -------------------------------------------- //
	printf("\n--Testing shuffle required--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));

	testState.discardCount[0] = 1;
	testState.deck[0][0] = copper;

	testState.deckCount[0] = 3;
	testState.deck[0][0] = baron;		// 15
	testState.deck[0][1] = feast;		//  9
	testState.deck[0][2] = copper;		//  4

	testState.handCount[0] = 2;
	testState.hand[0][0] = smithy;		// 13
	testState.hand[0][1] = adventurer;	//  7

	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  4) {
		printf("PASSED - 2 treasure cards added to hand\n");
		passed++;
	}
	else
		printf("FAILED - 6 cards available but discard count: %d, deck: %d, hand: %d, played: %d\n",
			testState.discardCount[0], testState.deckCount[0], testState.handCount[0], testState.playedCardCount);

	// -------------------------------------------- //
	// Testing 2 treasures on top
	// -------------------------------------------- //
	printf("\n--Testing 2 treasures on top of deck--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));

	testState.discardCount[0] = 0;

	testState.deckCount[0] = 4;
	testState.deck[0][0] = baron;		// 15
	testState.deck[0][1] = feast;		//  9
	testState.deck[0][2] = copper;		//  4
	testState.deck[0][3] = copper;		//  4

	testState.handCount[0] = 2;
	testState.hand[0][0] = smithy;		// 13
	testState.hand[0][1] = adventurer;	//  7

	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  4) {
		printf("PASSED - 2 treasure cards added to hand\n");
		passed++;
	}
	else
		printf("FAILED - Hand count: %d\n", testState.handCount[0]);

	printf("\n--Testing discard count when 2 treasures on top of deck--\n");
	if (testState.discardCount[0] ==  2) {
		printf("PASSED - 2 non-treasure cards added to discard\n");
		passed++;
	}
	else {
		printf("FAILED - 6 cards available but discard count: %d, deck: %d, hand: %d, played: %d\n",
			testState.discardCount[0], testState.deckCount[0], testState.handCount[0], testState.playedCardCount);
		printf("         Hand[0]: %d\tHand[1]: %d\tHand[2]: %d\tHand[3]: %d\n",
			testState.hand[0][0], testState.hand[0][1], testState.hand[0][2], testState.hand[0][3]);
		printf("         Deck[0]: %d\tDeck[1]: %d\n", testState.deck[0][0], testState.deck[0][1]);
		printf("         Discard[0]: %d\n", testState.discard[0][0]);
	}	

	// -------------------------------------------- //
	// Testing 1 treasure on top, 1 on bottom
	// -------------------------------------------- //
	printf("\n--Testing 1 treasure on top of deck, 1 on bottom--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));

	testState.discardCount[0] = 0;

	testState.deckCount[0] = 4;
	testState.deck[0][0] = copper;
	testState.deck[0][1] = feast;
	testState.deck[0][2] = baron;
	testState.deck[0][3] = copper;

	testState.handCount[0] = 2;
	testState.hand[0][0] = smithy;
	testState.hand[0][1] = adventurer;

	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  4) {
		printf("PASSED - 2 treasure cards added to hand\n");
		passed++;
	}
	else
		printf("FAILED - Hand count: %d\n", testState.handCount[0]);

	printf("\n--Testing discard count when 1 treasure on top and bottom--\n");
	if (testState.discardCount[0] ==  2) {
		printf("PASSED - 2 non-treasure cards added to discard\n");
		passed++;
	}
	else {
		printf("FAILED - 6 cards available but discard count: %d, deck: %d, hand: %d, played: %d\n",
			testState.discardCount[0], testState.deckCount[0], testState.handCount[0], testState.playedCardCount);
		printf("         Hand[0]: %d\tHand[1]: %d\tHand[2]: %d\tHand[3]: %d\n",
			testState.hand[0][0], testState.hand[0][1], testState.hand[0][2], testState.hand[0][3]);
		printf("         Deck[0]: %d\tDeck[1]: %d\n", testState.deck[0][0], testState.deck[0][1]);
		printf("         Discard[0]: %d\n", testState.discard[0][0]);
	}

	// -------------------------------------------- //
	// Testing 2 treasures on bottom
	// -------------------------------------------- //
	printf("\n--Testing 2 treasures on bottom of deck--\n");
	memcpy(&testState, &originalState, sizeof(struct gameState));

	testState.discardCount[0] = 0;

	testState.deckCount[0] = 4;
	testState.deck[0][0] = copper;
	testState.deck[0][1] = copper;
	testState.deck[0][2] = baron;
	testState.deck[0][3] = feast;

	testState.handCount[0] = 2;
	testState.hand[0][0] = smithy;
	testState.hand[0][1] = adventurer;

	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	
	if (testState.handCount[0] ==  4) {
		printf("PASSED - 2 treasure cards added to hand\n");
		passed++;
	}
	else
		printf("FAILED - Hand count: %d\n", testState.handCount[0]);

	printf("\n--Testing discard count when 2 treasures on bottom of deck--\n");
	if (testState.discardCount[0] ==  2) {
		printf("PASSED - 2 non-treasure cards added to discard\n");
		passed++;
	}
	else {
		printf("FAILED - 6 cards available but discard count: %d, deck: %d, hand: %d, played: %d\n",
			testState.discardCount[0], testState.deckCount[0], testState.handCount[0], testState.playedCardCount);
		printf("         Hand[0]: %d\tHand[1]: %d\tHand[2]: %d\tHand[3]: %d\n",
			testState.hand[0][0], testState.hand[0][1], testState.hand[0][2], testState.hand[0][3]);
		printf("         Deck[0]: %d\tDeck[1]: %d\n", testState.deck[0][0], testState.deck[0][1]);
		printf("         Discard[0]: %d\n", testState.discard[0][0]);
	}

	printf("\nTests passed: %d/7\n\n", passed);
}

int main(int argc, char** argv) {
	testSmithy();
	return 0;
}