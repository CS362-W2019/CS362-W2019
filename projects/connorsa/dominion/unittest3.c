#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

void testIsGameOver()
{
    int i, x;
    printf("\nUNIT TEST 3 START\n");
    // create 2 identical game states to test if isGameOver() modifies other things
    // initialize with all cards available
    struct gameState G;
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador,
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too

    // check fresh game
    if (isGameOver(&G))
    {
        printf("FAIL --- unplayed game is 'over'\n");
    }

    // ensure positive supply of all cards
    for (i = curse; i <= treasure_map; i++)
    {
        G.supplyCount[i] = 10; // reset
    }

    // check that game doesn't end before provinces are exhausted
    x = G.supplyCount[province];
    for (i = 0; i < x; i++)
    {
        G.supplyCount[province]--;
        if (isGameOver(&G) && G.supplyCount[province] != 0)
        {
            printf("FAIL --- unplayed game is 'over'\n");
        }
    }

    // check that game now ends
    G.supplyCount[province] = 0; // just in case above loop failed to get to 0
    if (!isGameOver(&G))
    {
        printf("FAIL --- game did not end with %d provinces\n", G.supplyCount[province]);
    }
    // check a negative number of cards
    G.supplyCount[province] = -1;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game did not end with %d provinces\n", G.supplyCount[province]);
    }
    G.supplyCount[province] = 100; // reset to avoid accidental game over

    // check that 3 empty supply stacks --> game over
    G.supplyCount[curse] = 0;
    if (isGameOver(&G))
    {
        printf("FAIL --- game ended after only exhausting curses\n");
    }
    G.supplyCount[estate] = 0;
    if (isGameOver(&G))
    {
        printf("FAIL --- game ended after only exhausting curses and estates\n");
    }
    G.supplyCount[duchy] = 0;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game didn't end after exhausting curses, estates, and duchies\n");
    }

    G.supplyCount[duchy] = -1;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game didn't end with -1 duchy, 0 curses, 0 estates\n");
    }

    // let duchy and estate be the first 2 exhausted
    G.supplyCount[curse] = 100;
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;

    // check that all other cards copper through treasure_map can trigger game over
    for (i = copper; i <= treasure_map; i++)
    {
        G.supplyCount[i] = 0; // exhaust the supply
        if (!isGameOver(&G))  // should trigger game over
        {
            printf("FAIL --- game didn't end after exhausting card #%d, duchies, and estates\n", i);
        }
        G.supplyCount[i] = 100; // reset
    }
    printf("\nUNIT TEST 3 COMPLETE\n");
}

int main()
{
    srand(time(NULL));
    testIsGameOver();
    return 0;
}
