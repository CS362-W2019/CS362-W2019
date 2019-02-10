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

void testIsGameOver()
{
    int i, x;
    // create 2 identical game states to test if isGameOver() modifies other things
    // initialize with all cards available
    struct gameState G;
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador,
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too
    compareStateFull(&G, &original, "");

    // check fresh game
    if (isGameOver(&G))
    {
        printf("FAIL --- unplayed game is 'over'\n");
    }
    compareStateFull(&G, &original, "supplyCount");

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
        compareStateFull(&G, &original, "supplyCount");
    }

    // check that game now ends
    G.supplyCount[province] = 0; // just in case above loop failed to get to 0
    if (!isGameOver(&G))
    {
        printf("FAIL --- game did not end with %d provinces\n", G.supplyCount[province]);
    }
    compareStateFull(&G, &original, "supplyCount");
    // check a negative number of cards
    G.supplyCount[province] = -1;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game did not end with %d provinces\n", G.supplyCount[province]);
    }
    compareStateFull(&G, &original, "supplyCount");
    G.supplyCount[province] = 100; // reset to avoid accidental game over

    // check that 3 empty supply stacks --> game over
    G.supplyCount[curse] = 0;
    if (isGameOver(&G))
    {
        printf("FAIL --- game ended after only exhausting curses\n");
    }
    compareStateFull(&G, &original, "supplyCount");
    G.supplyCount[estate] = 0;
    if (isGameOver(&G))
    {
        printf("FAIL --- game ended after only exhausting curses and estates\n");
    }
    compareStateFull(&G, &original, "supplyCount");
    G.supplyCount[duchy] = 0;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game didn't end after exhausting curses, estates, and duchies\n");
    }
    compareStateFull(&G, &original, "supplyCount");

    G.supplyCount[duchy] = -1;
    if (!isGameOver(&G))
    {
        printf("FAIL --- game didn't end with -1 duchy, 0 curses, 0 estates\n");
    }
    compareStateFull(&G, &original, "supplyCount");

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
        compareStateFull(&G, &original, "supplyCount");
    }

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
    testIsGameOver();
    return 0;
}
