#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main()
{
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    int validator = 0;
    struct gameState G, testG;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int i, r;
    int thisPlayer = 0;
    int cardDrawn1, cardDrawn2;
    int treasureCnt1 = 0;
    int treasureCnt2 = 0;

    r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1)
    {
        validator = 1;
        printf("FAIL when initialize a new game for %s card.\n", TESTCARD);
    }
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("\n----------- TEST 1: set initial cards --------------\n");
    //handcount before adventurer play
    if (G.handCount[thisPlayer] == testG.handCount[thisPlayer])
    {
        printf("PASS - handcount before Adventurer card is %d and expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    }
    else
    {
        validator = 1;
        printf("FAIL - handcount before Adventurer card is %d but expected %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    }

    printf("\n----------- TEST 2: give %s card --------------\n", TESTCARD);
    // set adventurer card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++; // increment number of card due to Adventurer card
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
    {
        printf("PASS - handcount after Adventurer card is %d and %d expected\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    }
    else
    {
        validator = 1;
        printf("FAIL - handcount after Adventurer card is %d but %d expected\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    }

    printf("\n----------- TEST 3: play %s card --------------\n", TESTCARD);
    // play adventurer
    cardEffect(adventurer, 0, 0, 0, &testG, 0, 0); // play the adventurer card
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
    {
        printf("PASS - handcount %d and %d expected.\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    }
    else
    {
        validator = 1;
        printf("FAIL - handcount %d but %d expected.\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3);
    }

    printf("\n----------- TEST 4: check two treasure cards  --------------\n");
    //verify that at least 2 new treasure cards were added to hand
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        cardDrawn1 = testG.hand[thisPlayer][i];
        if (cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold){
            treasureCnt1++;
        }
    }
    for (i = 0; i < G.handCount[thisPlayer]; i++)
    {
        cardDrawn2 = G.hand[thisPlayer][i];
        if (cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold)
            treasureCnt2++;
    }
    if ((treasureCnt1 - treasureCnt2) == 2){
        printf("PASS - %d additional treasure cards drawn.\n", (treasureCnt1 - treasureCnt2));
    }
    else{
        validator = 1;
        printf("FAIL - 2 treasure cards expected but %d treasure cards added.\n", (treasureCnt1 - treasureCnt2));
    }


    if (validator == 0)
    {
        printf("\n\n");
        printf("*********************************************\n");
        printf("*** All tests passed for Adventurer card! ***\n");
        printf("*********************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("****************************************\n");
        printf("*** There is BUG in Adventurer card! ***\n");
        printf("****************************************\n");
        printf("\n\n");
    }

    return 0;
}