/* -----------------------------------------------------------------------
 * Unit test for getcost() function.
 *
 * unittest2: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING getcost():\n");
    int validator = 0;
    struct gameState G;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    enum CARD {curse, estate, duchy, province,
                copper, silver, gold, adventurer, council_room,
                feast, gardens, mine, remodel, smithy, village,
                baron, great_hall, minion, steward, tribute,
                ambassador, cutpurse, embargo, outpost,
                salvager, sea_hag, treasure_map};
    int values[27] = {0, 2, 5, 8,
                    0, 3, 6, 6, 5,
                    4, 4, 5, 4, 4, 3,
                    4, 3, 5, 3, 5,
                    3, 4, 2, 5,
                    4, 4, 4};
    int seed = 1000;
    int i;
    int r;

    r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
    if (r == -1)
    {
        validator = 1;
        printf("getcost(): FAIL when initialize a new game.\n");
    }

    for (i = curse; i < treasure_map; i++)
    {
        if (getCost(i) != values[i])
        {
            validator = 1;
            printf("getcost(): FAIL - cost is %d but resulted %d\n", getCost(i), values[i]);
        }
        else {
            printf("getcost(): PASS - cost is %d and resulted %d\n", getCost(i), values[i]);
        }
    }

    if (validator == 0)
    {
        printf("\n\n");
        printf("***************************************\n");
        printf("*** All tests passed for getcost()! ***\n");
        printf("***************************************\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("**********************************\n");
        printf("*** There is BUG in getcost()! ***\n");
        printf("**********************************\n");
        printf("\n\n");
    }

    return 0;
}