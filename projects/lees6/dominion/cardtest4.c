#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

int main()
{
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    int validator = 0;
    struct gameState G, testG;
    int numPlayers = 2;
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
    //handcount before council_room play
    if (G.handCount[thisPlayer] == testG.handCount[thisPlayer])
    {
        printf("PASS - handcount before council_room card is %d and expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    }
    else
    {
        validator = 1;
        printf("FAIL - handcount before council_room card is %d but expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    }
    testG.handCount[thisPlayer]++; // increment number of card due to council_room card

    printf("\n----------- TEST 2: check handCount after council_room card --------------\n");
    // play council_room card
    cardEffect(council_room, 0, 0, 0, &testG, 0, 0); //play the council_room card
    if (G.handCount[G.whoseTurn] + 4 == testG.handCount[testG.whoseTurn])
    {
        printf("PASS - Expected: %d, handCount: %d\n", G.handCount[G.whoseTurn] + 4, testG.handCount[testG.whoseTurn]);
    }
    else
    {
        validator = 1;
        printf("FAIL - Expected: %d, handCount: %d\n", G.handCount[G.whoseTurn] + 4, testG.handCount[testG.whoseTurn]);
    }

    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(council_room, 0, 0, 0, &testG, 0, 0); //play the council_room card

    printf("\n----------- TEST 3: check number of buy card --------------\n");
    if (G.numBuys + 1 == testG.numBuys)
    {
        printf("PASS - Expected: %d, Buy card: %d\n", G.numBuys + 1, testG.numBuys);
    }
    else
    {
        validator = 1;
        printf("FAIL - Expected: %d, Buy card: %d\n", G.numBuys + 1, testG.numBuys);
    }

    if (validator == 0)
    {
        printf("\n\n");
        printf("***********************************************\n");
        printf("*** All tests passed for council_room card! ***\n");
        printf("***********************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("******************************************\n");
        printf("*** There is BUG in council_room card! ***\n");
        printf("******************************************\n");
        printf("\n\n");
    }

    return 0;
}