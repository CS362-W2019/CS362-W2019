/* -----------------------------------------------------------------------
 * Random test for Smithy Card.
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TESTCARD "smithy"
#define MAXRUN 1000

int main()
{
    printf("\n----------------- Random Testing Card: %s ----------------\n", TESTCARD);
    int validator = 1;
    struct gameState G, testG;
    int i, n, r;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int handPos = 0;
    int currentPlayer;
    int addedCards = 3;
    int discard = 1;
    int totalCards, testtotalCards;
    int deckFailure = 0;
    int handFailure = 0;
    int discardFailure = 0;
    int testPassed = 0;

    // initialize random number
    srand(time(NULL));

    // randomize hand size
    for (i = 0; i < MAXRUN; i++)
    {
        for (n = 0; n < sizeof(struct gameState) / sizeof(int); n++)
        {
            ((int *)&G)[n] = rand() % 128;
        }
        // generate random number of player from 2 to 4
        G.numPlayers = (rand() % 3) + 2;
        G.whoseTurn = rand() % G.numPlayers;
        currentPlayer = whoseTurn(&G);
        G.handCount[currentPlayer] = (rand() % (MAX_HAND / 2)) + 1;

        G.deckCount[currentPlayer] = (rand() % (MAX_DECK / 2)) + 1;
        G.discardCount[currentPlayer] = (rand() % (MAX_DECK / 2)) + 1;
        handPos = (rand() % G.handCount[currentPlayer]);
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        // play Smithy
        r = cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
        if (r != 0)
        {
            validator = 0;
            printf("FAIL when initializing playing %s card.\n", TESTCARD);
        }
        if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + addedCards - discard)
        {
            printf("Test FAILED - incorrect number of cards drawn!\n");
            handFailure++;
            validator = 0;
        }

        totalCards = G.deckCount[currentPlayer] + G.discardCount[currentPlayer];
        testtotalCards = testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer];
        if (testtotalCards != totalCards - addedCards)
        {
            printf("Test Failed - incorrect number of cards removed!\n");
            deckFailure++;
            validator = 0;
        };

        if (validator)
        {
            printf("\n\n");
            printf("*****************************************\n");
            printf("*** All tests passed for %s card! ***\n", TESTCARD);
            printf("*****************************************\n");
            printf("\n\n");
        }
        else
        {
            printf("\n\n");
            printf("************************************\n");
            printf("*** There is BUG in %s card! ***\n", TESTCARD);
            printf("************************************\n");
            printf("\n\n");
        }
    }

    printf("Number of Tests Passed: %d\n", testPassed);
    printf("Number of Cards Drawn To Hand Failed: %d\n", handFailure);
    printf("Number of Smithy Discarded Fails: %d\n\n", discardFailure);

    return 0;
};