/* -----------------------------------------------------------------------
 * Unit test for whoseTurn() function.
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
#include <assert.h>

int main()
{
    printf("TESTING whoseTurn():\n");
    int validator = 0;
    struct gameState G;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int i;
    int r;

    r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1){
        validator = 1;
        printf("whoseTurn(): FAIL when initialize a new game.\n");
    }

    for (i = 0; i < numPlayers; i++)
    {
        G.whoseTurn = i;
        if (whoseTurn(&G) != i) {
            validator = 1;
            printf("whoseTurn(): FAIL - Player %d's turn but Player %d expected. \n", whoseTurn(&G), i);
        }
        else {
            printf("whoseTurn(): PASS - Player %d's turn and Player %d expected. \n", whoseTurn(&G), i);
        }
    }

    if (validator == 0)
    {
        printf("\n\n");
        printf("*****************************************\n");
        printf("*** All tests passed for whoseTurn()! ***\n");
        printf("*****************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("************************************\n");
        printf("*** There is BUG in whoseTurn()! ***\n");
        printf("************************************\n");
        printf("\n\n");
    }

    return 0;
}