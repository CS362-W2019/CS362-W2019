/* -----------------------------------------------------------------------
 * Random test for Village Card.
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "village"
#define MAXRUN 1000

int main()
{
    printf("\n----------------- Random Testing Card: %s ----------------\n", TESTCARD);
    int validator = 1;
    struct gameState G, testG;
    int i, n, r;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int currentPlayer;
    int addedCards = 4;
    int discard = 1;
    int addedBuys = 1;
    int otherPlrAdded = 1;
    int playerHand[4];
    int testPlayerHand[4];
    int totalCards, testtotalCards;

    //initialize random
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
        G.numBuys = 0;
        handPos = (rand() % G.handCount[currentPlayer]);
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        // play Village
        r = cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);
        if (r != 0)
        {
            validator = 0;
            printf("FAIL when initializing playing %s card.\n", TESTCARD);
        }

        if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + addedCards - discard)
        {
            validator = 0;
            printf("Test Failed - incorrect number of handcount!\n");
        }

        totalCards = G.deckCount[currentPlayer] + G.discardCount[currentPlayer];
        testtotalCards = testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer];
        if (testtotalCards != totalCards - addedCards)
        {
            validator = 0;
            printf("Test Failed - incorrect number of deckcount\n");
        };

        if (testG.numBuys != G.numBuys + addedBuys)
        {
            validator = 0;
            printf("Test Failed - incorrect number of Buy Card!\n");
        }

        for (n = 0; n < G.numPlayers; n++)
        {
            if (n != currentPlayer)
            {
                testPlayerHand[n] = testG.handCount[n];
                playerHand[n] = G.handCount[n];
            }
        }

        for (n = 0; n < G.numPlayers; n++)
        {
            if (n != currentPlayer)
            {
                if (testPlayerHand[n] != playerHand[n] + otherPlrAdded)
                {
                    validator = 0;
                    printf("Test Failed - incorrect number of other player hand!\n");
                }
            }
        }
    }

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

    return 0;
};