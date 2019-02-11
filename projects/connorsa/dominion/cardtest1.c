#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

void testSmithy()
{
    int nextCard, handSize, deckSize, allDeckSize, discSize, playedSize, smithyPos;
    int card1, card2, card3;
    const int P0 = 0;
    const int P1 = 1;
    printf("\nCARD TEST 1 START\n");
    // create 2 identical game states to test if updateCoins() modifies other things
    struct gameState G;
    // initialize with all cards available
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador, 
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);
    struct gameState original;
    memcpy(&original, &G, sizeof(G)); // use memcpy so that memory padding copies too

    // add a smithy to the end of P0's hand 
    G.whoseTurn = P0;
    nextCard = G.handCount[P0];
    G.handCount[P0]++;
    G.hand[P0][nextCard] = smithy;
    smithyPos = nextCard; // keep pointed at smithy
    
    // record for later comparison
    allDeckSize = G.deckCount[P0] + G.deckCount[P1]; // overall deck size
    deckSize = G.deckCount[P0]; // player's total deck size
    handSize = G.handCount[P0]; // cards in player's hand
    discSize = G.discardCount[P0]; // cards in player's discard
    playedSize = G.playedCardCount; // cards player has played
    //cards that should be drawn by Smithy
    card1 = G.deck[0][smithyPos-1];
    card2 = G.deck[0][smithyPos-2];
    card3 = G.deck[0][smithyPos-3];
    
    //printf("\n\nPLAYING SMITHY\n\n");
    //smithyCard(&G, smithyPos); // test the function directly
    cardEffect(smithy, 30, 30, 30, &G, smithyPos, 0); // test via cardEffect

    // test for what we expect
    // deck should have 3 fewer cards due to drawn cards
    if (G.deckCount[P0] != deckSize - 3)
    {
        printf("FAIL --- expected post-Smithy deck size of %d, got %d\n", deckSize - 3, G.deckCount[P0]);
    }
    // hand should have 2 additional cards (+3, then -1 for Smithy)
    if (G.handCount[P0] != handSize + 2)
    {
        printf("FAIL --- expected post-Smithy hand size of %d, got %d\n", handSize + 2, G.handCount[P0]);
    }
    // played should have 1 additional card for discarded Smithy
    if (G.playedCardCount != playedSize + 1)
    {
        printf("FAIL --- expected post-Smithy played size of %d, got %d\n", playedSize + 1, G.playedCards[P0]);
    }
    if (G.playedCards[P0] != smithy)
    {
        printf("FAIL --- Smithy card was not placed in played cards deck\n");
    }
    if (allDeckSize != G.deckCount[P0] + G.deckCount[P1]) 
    {
        printf("FAIL --- Smithy changed total deck size\n");
    }

    printf("\nCARD TEST 1 COMPLETE\n");

}

int main()
{
    srand(time(NULL));
    testSmithy();
    return 0;
}