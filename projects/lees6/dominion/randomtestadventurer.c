/* -----------------------------------------------------------------------
 * Random test for Adventurer Card.
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "adventurer"
#define MAXRUN 1000

int main()
{
    printf("\n----------------- Random Testing Card: %s ----------------\n", TESTCARD);
    int seed;
    int numPlayers;
    int player, j, i, m, n, r;
    int topCard, treasureCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 5;
    int testfailed = 0;
    int testpassed = 0;
    int validator = 1;

    for (i = 0; i < MAXRUN; i++)
    {
        // generate random seed
        seed = rand() % 100000;
        // generate random number of player from 2 to 4
        numPlayers = (rand() % 3) + 2;

        for (j = 0; j < maxHandCount; j++)
        {
            memset(&G, 23, sizeof(struct gameState));     //clear the game state
            memset(&testG, 23, sizeof(struct gameState)); //clear the game state
            r = initializeGame(numPlayers, k, seed, &testG);
            if (r != 0)
            {
                validator = 0;
                printf("FAIL when initializing playing %s card.\n", TESTCARD);
            }
            for (m = 0; m < 2; m++)
            {
                for (player = 0; player < numPlayers; player++)
                {
                    // copy the game state to a test case
                    memcpy(&G, &testG, sizeof(struct gameState));
                    // play the card
                    adventurerCard(player, &testG, maxHandCount);

                    // check the treasure cards
                    treasureCount = 0;
                    for (n = 0; n < 2; n++)
                    {
                        topCard = testG.hand[player][testG.handCount[player] - (n + 1)];
                        if (topCard == copper || topCard == silver || topCard == gold)
                        {
                            treasureCount++;
                        }
                    }
                    if ((testG.handCount[player] == G.handCount[player] + 2) && (testG.deckCount[player] == G.deckCount[player] - 2) && treasureCount == 2)
                    {
                        testpassed++;
                    }
                    else
                    {
                        validator = 0;
                        testfailed++;
                        printf("Test FAILED - incorrect number of Treasure cards!\n");
                        printf("Expected: %d, TreasureCount: %d\n", 2, treasureCount);
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
    }

    printf("Number of Tests Passed: %d\n", testpassed);
    printf("Number of Tests Failed: %d\n", testfailed);

    return 0;
}