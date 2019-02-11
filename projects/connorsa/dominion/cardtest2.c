#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

extern int updateCoins(int player, struct gameState *state, int bonus);

void testAdventurer()
{
    int i, preCoins, postCoins, advPos, postDeck, preHand, preDeck, preDisc, cardsFound, badVal;
    printf("\nCARD TEST 2 START\n");
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
    G.handCount[0] = 5;
    G.whoseTurn = 0;
    

    // put the adventurer in first card spot, fill the rest with curses
    advPos = 0;
    G.hand[0][advPos] = adventurer;
    for (i = 0; i < G.handCount[0]; i++)
    {
        if (i != 0)
        {
            G.hand[0][i] = curse; // curse cards
        }
         //printf("%d  ", G.hand[0][i]);
    }
    //printf("hand \n");
    // fill deck with estates and copper
    // only 5 to force reshuffle to get to extra copper in discard
    G.deckCount[0] = 5;
    for (i = 0; i < G.deckCount[0]; i++)
    {
        if (i == 3) // put one copper in the deck
        {
            G.deck[0][i] = copper;
        }
        else
        {
             G.deck[0][i] = estate;
        }
        //printf("%d  ", G.deck[0][i]);
    }
    //printf("deck \n");
    // load discard to ensure shuffle must occur 
    G.discardCount[0] = 5;
    for (i = 0; i < G.discardCount[0]; i++)
    {
        if (i == 2 || i == 4)
        {
            G.discard[0][i] = copper;
        }
        else
        {
            G.discard[0][i] = estate;
        }
        //printf("%d  ", G.discard[0][i]);
    }
    //printf("discard \n");

    // save off variables for comparison
    updateCoins(0, &G, 0);
    preCoins = G.coins; // treasure the player has in hand before using Adventurer
    preDeck = G.deckCount[0]; // size of deck before playing card
    preDisc = G.discardCount[0]; //size of discard deck before playing card
    preHand = G.handCount[0]; //size of hand before playing card

    // copy the struct here so that modifications are included
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too
    //adventurerCard(&G);
    cardEffect(adventurer, 30, 30, 30, &G, advPos, 0);

    // TEST DISCARD PILE - should be estates only
    cardsFound = 0;
    badVal = 0;
    for (i = 0; i < G.discardCount[0]; i++)
    {
        if (G.discard[0][i] == estate)
        {
            cardsFound++;
        }
        else //only estates because 2 copper in hand, 1 copper reshuffled into deck
        {
            badVal = -1; // indicate unexpected contents
        }
        //printf("%d  ", G.discard[0][i]);
        
    }
    //printf("disc\n");
    if (cardsFound < 1 || cardsFound > 7 || badVal == -1)
    {
        printf("FAIL --- unexpected discard pile contents\n");
    }

    // TEST HAND value for added treasure
    updateCoins(0, &G, 0);
    postCoins = G.coins;
    if (postCoins != 2) // should have exactly 2 copper in hand
    {
        printf("FAIL --- expected %d coins in hand from Adventurer, but have %d\n", preCoins + 2, postCoins);
    }
    if (G.handCount[0] - preHand > 2)
    {
        printf("FAIL --- too many cards in hand after Adventurer\n");
    }
    // TEST PLAYED to see if adventurer card was removed from hand and put into played pile
    if (G.playedCards[0] != adventurer || G.hand[0][advPos] == adventurer)
    {
        printf("FAIL --- Adventurer card not moved from hand to played pile\n");
    }

    // TEST DECK - should be 
    postDeck = G.deckCount[0];
    if ((preDeck - postDeck) != 4)
    {
        printf("FAIL --- deck size is %d, expected %d\n", postDeck, preDeck - 2);
    }
    printf("\nCARD TEST 2 COMPLETE\n");

}

int main()
{
    srand(time(NULL));
    testAdventurer();
    return 0;
}
