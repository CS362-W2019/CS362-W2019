/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int numCards = 10;
    int p, cardCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int MAX_SUPPLY = 10;
    // arrays of all coppers, smities, and estates
    int coppers[MAX_SUPPLY];
    int smithies[MAX_SUPPLY];
    int estates[MAX_SUPPLY];
    for (i = 0; i < MAX_SUPPLY; i++)
    {
        coppers[i] = copper;
        smithies[i] = smithy;
        estates[i] = estate;
    }

    printf ("TESTING supplyCount():\n");
    for (p = 0; p < numCards; p++)
    {


#if (NOISY_TEST == 1)
                printf("Test supply pile with  %d copper card(s).\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game

		G.supplyCount[copper] = p; 
                //memcpy(G.supplyCount[copper], coppers, sizeof(int) * p); // set all the cards to copper
                cardCount = supplyCount(copper, &G);
#if (NOISY_TEST == 1)
                printf("supplyCount = %d, expected = %d\n", cardCount, p);
#endif

                assert(cardCount == p); // check if the number of cards is correct
		
		G.supplyCount[smithy] = p; 
                //memcpy(G.supplyCount[smithy], smithies, sizeof(int) * p); // set all the cards to smithies
                cardCount = supplyCount(smithy, &G);
#if (NOISY_TEST == 1)
                printf("supplyCount = %d, expected = %d\n", cardCount, p);
#endif
                assert(cardCount == p); // check if the number of cards is correct

		G.supplyCount[estate] = p; 
                //memcpy(G.supplyCount[estate], estates, sizeof(int) * p); // set all the cards to estates
                cardCount = supplyCount(estate, &G);
#if (NOISY_TEST == 1)
                printf("supplyCount = %d, expected = %d\n", cardCount, p);
#endif
                assert(cardCount == p); // check if the number of cards is correct
            }
        
    

    printf("All tests passed!\n");

    return 0;
}
