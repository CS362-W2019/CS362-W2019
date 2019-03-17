/* -----------------------------------------------------------------------
 * Unit test for isGameOver() function.
 * 
 * unittest2: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    printf("TESTING isGameOver():\n");
    int validator = 0;
    struct gameState G;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int r;
    int i;

    r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1) {
        validator = 1;
        printf("isGameOver(): FAIL when initialize a new game.\n");
    }
    int provinceCards = G.supplyCount[province];

    // game continues when supply of province is more than 0
    for (i = 0; i < provinceCards; i++)
    {
        printf("Number of Province Cards: %d\n", G.supplyCount[province]);
        if (isGameOver(&G) == 1)
        {
            validator = 1;
            printf("isGameOver(): FAIL when there is %d cards.\n", G.supplyCount[province]);
        }
        else
        {
            printf("isGameOver(): PASS when there is %d cards.\n", G.supplyCount[province]);
        }
        G.supplyCount[province]--;

        if (G.supplyCount[province] == 0) {
            printf("NO MORE PROVINCE CARDS!\n");
            if (isGameOver(&G) == 0)
            {
                validator = 1;
                printf("isGameOver(): FAIL when there is %d cards.\n", G.supplyCount[province]);
            }
            else
            {
                printf("isGameOver(): PASS when there is %d cards.\n", G.supplyCount[province]);
            }
        }
    }

    if (validator == 0)
    {
        printf("\n\n");
        printf("******************************************\n");
        printf("*** All tests passed for isGameOver()! ***\n");
        printf("******************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("*************************************\n");
        printf("*** There is BUG in isGameOver()! ***\n");
        printf("*************************************\n");
        printf("\n\n");
    }

    return 0;
}