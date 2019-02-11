/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p, handCount;
    //int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, smities, and estates
    int coppers[MAX_HAND];
    int smithies[MAX_HAND];
    int estates[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        smithies[i] = smithy;
        estates[i] = estate;
    }

    printf ("TESTING numHandCards():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 0; handCount <= maxHandCount; handCount++)
        {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d copper card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.whoseTurn = p;                    //set turn to current player
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                int currentCards = numHandCards(&G);
#if (NOISY_TEST == 1)
                printf("numHandCards = %d, expected = %d\n", currentCards, handCount);
#endif

                assert(currentCards == handCount); // check if the number of coins is correct

                memcpy(G.hand[p], smithies, sizeof(int) * handCount); // set all the cards to silver
                currentCards = numHandCards(&G);
#if (NOISY_TEST == 1)
                printf("numHandCards = %d, expected = %d\n", currentCards, handCount);
#endif
                assert(currentCards == handCount); // check if the number of coins is correct

                memcpy(G.hand[p], estates, sizeof(int) * handCount); // set all the cards to gold
                currentCards = numHandCards(&G);
#if (NOISY_TEST == 1)
                printf("numHandCards = %d, expected = %d\n", currentCards, handCount);
#endif
                assert(currentCards == handCount); // check if the number of coins is correct
            }
        }
    

    printf("All tests passed!\n");

    return 0;
}
