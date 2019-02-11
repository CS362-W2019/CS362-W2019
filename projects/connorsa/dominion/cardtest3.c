#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

void testVillage()
{
    int i, vPos;
    int p1 = 1; // must start with player 1 for coverage purposes
    printf("\nCARD TEST 3 START\n");
    // create 2 identical game states to test if updateCoins() modifies other things
    // copy G into original AFTER preparing for test
    struct gameState G;
    // initialize with all cards available
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador,
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;

    // manually set a hand for P0
    G.handCount[p1] = 5;
    G.whoseTurn = p1;
    
    // put the village in first card spot, fill the rest with curses
    vPos = 0;
    G.hand[p1][vPos] = village;
    for (i = 1; i < G.handCount[p1]; i++)
    {
        G.hand[p1][i] = curse; // curse cards
    }
  
    // empty deck to force reshuffle testing
    G.deckCount[p1] = 0;
  
    // load discard to ensure shuffle can occur 
    G.discardCount[p1] = 5;
    for (i = 0; i < G.discardCount[p1]; i++)
    {
        G.discard[p1][i] = copper;
    }

    // copy for later comparison
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too

    // run that card!
    cardEffect(village, 30, 30, 30, &G, vPos, 0);

    // check that actions were added
    if (G.numActions != (original.numActions + 2))
    {
        printf("FAIL --- Village failed to add +1 action\n");
    }
    // check that 1 card was drawn
    if (G.handCount[p1] != 5)
    {
        printf("FAIL --- Expected deck size %d, got %d\n", 5, G.handCount[p1]);
    }
    // check that played pile contains the Village card
    if (G.playedCards[0] != village)
    {
        printf("FAIL --- Village card wasn't in expected spot in played pile\n");
    }    
    if (G.discardCount[p1] != 0)
    {
        printf("FAIL --- Expected discard count of 0, got %d\n", G.discardCount[p1]);
    }

    printf("\nCARD TEST 3 COMPLETE\n");

}

int main()
{
    srand(time(NULL));
    testVillage();

    return 0;
}
