#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    int validator = 0;
    struct gameState G, testG;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int r;
    int thisPlayer = 0;

        r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1)
    {
        validator = 1;
        printf("FAIL when initialize a new game.\n");
    }
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\n----------- TEST 1: set initial cards --------------\n");
    //handcount before smithy play
    if (G.handCount[thisPlayer] == testG.handCount[thisPlayer]){
        printf("PASS - handcount before Smithy card is %d and expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    } else {
        validator = 1;
        printf("FAIL - handcount before Smithy card is %d but expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    }
    printf("\n----------- TEST 2: give Smithy card --------------\n");
    // set Smithy card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++; // increment number of card due to smithy card

    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer]) {
        printf("PASS - handcount after Smithy card is %d and %d expected\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    }
    else {
        validator = 1;
        printf("FAIL - handcount after Smithy card is %d but %d expected\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    }

    printf("\n----------- TEST 3: play Smithy card --------------\n");
    // play Smithy card
    cardEffect(smithy, 0, 0, 0, &testG, 0, 0); //play the smithy card
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer]){
        printf("PASS - handcount %d and %d expected.\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    }
    else {
        validator = 1;
        printf("FAIL - handcount %d but %d expected.\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    }

    if (validator == 0) {
        printf("\n\n");
        printf("*****************************************\n");
        printf("*** All tests passed for Smithy card! ***\n");
        printf("*****************************************\n");
        printf("\n\n");
    } else {
        printf("\n\n");
        printf("************************************\n");
        printf("*** There is BUG in Smithy card! ***\n");
        printf("************************************\n");
        printf("\n\n");
    }

    return 0;
}