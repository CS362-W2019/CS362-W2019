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
extern int updateCoins(int player, struct gameState *state, int bonus);

void testAdventurer()
{
    int i, x, coin, preCoins, postCoins, advPos, preDeck, postDeck;
    int coinsFound = 2; // set this to total coin value Adventurer is expected to add to hand
    int badDiscard = -13; // for checking discard deck for bad contents

    // create 2 identical game states to test if updateCoins() modifies other things
    // copy G into original after preparing for test
    struct gameState G;
    // initialize with all cards available
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador,
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;

    // manually set a hand for P0
    G.handCount[0] = 5;
    G.whoseTurn = 0;
    coin = 4;

    // put the adventurer in first card spot, fill the rest with curses
    advPos = 0;
    G.hand[0][advPos] = adventurer;
    for (i = 0; i < G.handCount[0]; i++)
    {
        if (i != 0)
        {
            G.hand[0][i] = curse; // curse cards
        }
    }

    // fill deck with estates and copper
    G.deckCount[0] = 10;
    for (i = 0; i < G.deckCount[0]; i++)
    {
        if (i > G.deckCount[0] / 3 && i < G.deckCount[0] - 2) // overwrite with some copper
        {
            G.deck[0][i] = copper;
        }
        else
        {
             G.deck[0][i] = estate;
        }
    }

    // poison discard for later checking
    G.discardCount[0] = 5;
    for (i = 0; i < G.discardCount[0]; i++)
    {
        G.discard[0][i] = badDiscard;
    }

    x = G.discard[0][i-1];

    // save off variables for comparison
    updateCoins(0, &G, 0);
    preCoins = G.coins; // treasure the player has in hand before using Adventurer
    preDeck = G.deckCount[0]; // size of deck before playing card

    // copy the struct here so that modifications are included
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too
    //adventurerCard(&G);
    cardEffect(adventurer, 30, 30, 30, &G, advPos, 0);

    // TEST DISCARD PILE
    for (i = 0; i < G.discardCount[0]; i++)
    {
        // only 2 cards should have been discarded, both estates
        if (i > 4 && (G.discard[0][i] != estate)) // last two spots should be estates
        {
            printf("FAIL --- didn't see expected discarded cards\n");
        }
        else if (i <= 4 && (G.discard[0][i] != badDiscard)) // else check they are badDiscard
        {
            printf("FAIL --- unexpected contents found in discard pile %d\n", i);
        }
        
    }
    // TEST HAND value for added treasure
    updateCoins(0, &G, 0);
    postCoins = G.coins;
    if (postCoins != preCoins + coinsFound)
    {
        printf("FAIL --- expected %d coins in hand from Adventurer, but have %d\n", preCoins + 2, postCoins);
    }
    // TEST PLAYED to see if adventurer card was removed from hand and put into played pile
    if (G.playedCards[0] != adventurer || G.hand[0][advPos] == adventurer)
    {
        printf("FAIL --- Adventurer card not moved from hand to played pile\n");
    }

    // TEST DECK - should be 4 down (discard 2 estates, move 2 treasure to hand)
    postDeck = G.deckCount[0];
    if ((preDeck - postDeck) != 4)
    {
        printf("FAIL --- deck size is %d, expected %d\n", postDeck, preDeck - 2);
    }
    compareStateFull(&G, &original, "");
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
    testAdventurer();
    return 0;
}
