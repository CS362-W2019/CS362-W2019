/* -----------------------------------------------------------------------
 * Unit test for numHandCards() function.
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    printf("TESTING numHandCards():\n");
    int validator = 0;
    struct gameState G;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int i;
    int j;
    int r;

    r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1){
        validator = 1;
        printf("numHandCards(): FAIL when initialize a new game.\n");
    }

    for (i = 0; i < numPlayers; i++)
    {
        printf("Player %d\n", i + 1);
        G.whoseTurn = i;
        for (j = 0; j < 5; j++)
        {
            G.handCount[i] = j;

            if (numHandCards(&G) != j)
            {
                validator = 1;
                printf("numHandCards(): FAIL - %d cards, %d expexted. \n", numHandCards(&G), j);
            }
            else {
                printf("numHandCards(): PASS - %d cards, %d expexted. \n", numHandCards(&G), j);
            }
        }
    }

    if (validator == 0)
    {
        printf("\n\n");
        printf("********************************************\n");
        printf("*** All tests passed for numHandCards()! ***\n");
        printf("********************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("***************************************\n");
        printf("*** There is BUG in numHandCards()! ***\n");
        printf("***************************************\n");
        printf("\n\n");
    }

    return 0;
}