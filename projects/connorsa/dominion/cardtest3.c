#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"


void compareStateFull(struct gameState *g1, struct gameState *g2, char *ignore);

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

    compareStateFull(&G, &original, "");
    printf("\nCARD TEST 3 COMPLETE\n");

}

void compareStateFull(struct gameState *g1, struct gameState *g2, char *ignore)
{
    if (g1->numPlayers != g1->numPlayers && (strcmp(ignore, "numPlayers") != 0))
    {
        printf("numPlayers was modified\n");
    }
    if (g1->coins != g2->coins && (strcmp(ignore, "coins") != 0))
    {
        printf("coins was modified\n");
    }
    if (memcmp(g1->deck, g2->deck, sizeof(g1->deck)) && (strcmp(ignore, "deck") != 0))
    {
        printf("deck was modified\n");
    }
    if (memcmp(g1->deckCount, g2->deckCount, sizeof(g1->deckCount)) && (strcmp(ignore, "deckCount") != 0))
    {
        printf("deckCount was modified\n");
    }
    if (memcmp(g1->discard, g2->discard, sizeof(g1->discard)) && (strcmp(ignore, "discard") != 0))
    {
        printf("discard was modified\n");
    }
    if (memcmp(g1->discardCount, g2->discardCount, sizeof(g1->discardCount)) && (strcmp(ignore, "discardCount") != 0))
    {
        printf("discardCount was modified\n");
    }
    if (memcmp(g1->embargoTokens, g2->embargoTokens, sizeof(g1->embargoTokens)) && (strcmp(ignore, "embargoTokens") != 0))
    {
        printf("embargoTokens was modified\n");
    }
     if (memcmp(g1->hand, g2->hand, sizeof(g1->hand)) && (strcmp(ignore, "hand") != 0))
    {
        printf("hand was modified\n");
    }
    if (memcmp(g1->handCount, g2->handCount, sizeof(g1->handCount)) && (strcmp(ignore, "handCount") != 0))
    {
        printf("handCount was modified\n");
    }
    if (g1->numActions != g2->numActions && (strcmp(ignore, "numActions") != 0))
    {
        printf("numActions was modified\n");
    }
    if (g1->numBuys != g2->numBuys && (strcmp(ignore, "numBuys") != 0))
    {
        printf("numBuys was modified\n");
    }
    if (g1->outpostPlayed != g2->outpostPlayed && (strcmp(ignore, "outpostPlayed") != 0))
    {
        printf("outpostPlayed was modified\n");
    }
    if (g1->outpostTurn != g2->outpostTurn && (strcmp(ignore, "outpostTurn") != 0))
    {
        printf("outpostTurn was modified\n");
    }
    if (g1->phase != g2->phase && (strcmp(ignore, "phase") != 0))
    {
        printf("phase was modified\n");
    }
    if (g1->playedCardCount != g2->playedCardCount && (strcmp(ignore, "playedCardCount") != 0))
    {
        printf("playedCardCount was modified\n");
    }
    if (memcmp(g1->playedCards, g2->playedCards, sizeof(g1->playedCards)) && (strcmp(ignore, "playedCards") != 0))
    {
        printf("playedCards was modified\n");
    }
    if (memcmp(g1->supplyCount, g2->supplyCount, sizeof(g1->supplyCount)) && (strcmp(ignore, "supplyCount") != 0))
    {
        printf("supplyCount was modified\n");
    }
    if (g1->whoseTurn != g2->whoseTurn && (strcmp(ignore, "whoseTurn") != 0))
    {
        printf("whoseTurn was modified\n");
    }
}

int main()
{
    srand(time(NULL));
    testVillage();

    return 0;
}
