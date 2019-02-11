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

// updateCoins() is not a part of dominion.h so must note it is external
extern int updateCoins(int player, struct gameState *state, int bonus);

void testUpdateCoins()
{
    int i, j, x, card, bonus, expected;
    printf("\nUNIT TEST 2 START\n");
    // create 2 identical game states to test if updateCoins() modifies other things
    struct gameState G;
    // initialize with all cards available
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador, 
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too

    // TEST ONE
    // test player 0 with hands of all gold, all silver, all copper

    G.whoseTurn = 0; // ensure we're on player 0
    for (i = 1, card = copper; i <= 3; i++, card++)
    {
        x = 0;
        // fill hand with i denomination, don't change hand size
        for (j = 0; j < numHandCards(&G); j++)
        {
            G.hand[0][j] = card;
            x += i;
        }
        // check results for player 0, no bonus
        updateCoins(0, &G, 0);
        if (G.coins != x)
        {
            printf("FAIL --- expected %d for all %d-coin hand; received %d\n", x, i, G.coins);
        }
    }
    G.handCount[1] = card;               // update hand count for player 0
    compareStateFull(&G, &original, ""); 
    G.coins = 0;                         // reset

    // TEST TWO
    // test player 1 with hand of each card in sequence
    G.whoseTurn = 1; // ensure we're on player 1
    x = 0;           // reset running total of coins
    for (card = curse; card <= treasure_map; card++)
    {
        // fill hand sequentially with every card
        G.hand[1][card] = card;
        if (card == 4 || card == 5 || card == 6) // if treasure card
        {
            x += card - 3; // add card value to running total
        }
    }
    // update hand count for player
    G.handCount[1] = card;
    if (numHandCards(&G) != card)
    {
        printf("FAIL --- num cards = %d, numHandCards = %d\n", card, numHandCards(&G));
    }

    // check results for player 1, no bonus
    updateCoins(1, &G, 0);
    if (G.coins != x)
    {
        printf("FAIL --- expected %d for all-card hand; received %d\n", x, G.coins);
    }

    compareStateFull(&G, &original, ""); 

    // TEST THREE
    // test bonus values

    // check results for player 1, but this time add various bonuses
    for (i = -5; i < 20; i++)
    {
        bonus = i;
        expected = x + bonus;
        updateCoins(1, &G, bonus);
        if (G.coins != expected)
        {
            printf("FAIL --- expected %d for hand with bonus %d; received %d\n", expected, bonus, G.coins);
        }
        else if (bonus < 0)
        {
            printf("NOTE --- negative value for bonus (%d) was accepted\n", bonus);
        }
    }

    compareStateFull(&G, &original, "");
    printf("\nUNIT TEST 2 COMPLETE\n");

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
    testUpdateCoins();
    return 0;
}
