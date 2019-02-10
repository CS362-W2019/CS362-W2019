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

/*
int smithyCard(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);
  int nextPlayer = currentPlayer + 1;

  if (nextPlayer > (state->numPlayers - 1))
  {
    nextPlayer = 0;
  }
  //+3 Cards
  //for (i = 0; i < 3; i++) //UNBUGGED HERE
  for (i = 0; i <= 3; i++) //INTRODUCED BUG HERE
  {
    drawCard(currentPlayer, state);
  }

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
*/

void testSmithy()
{
    int i, nextCard, handSize, deckSize, allDeckSize, discSize, playedSize, smithyPos;
    int card1, card2, card3;
    const int P0 = 0;
    const int P1 = 1;
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
    
    /*
    printf("P0 & P1 decks = %d, P0 deck = %d, P0 hand = %d, P0 disc = %d\n", allDeckSize, deckSize, handSize, discSize); 
    printf("\ndeck\n");
    for (i = 0; i < deckSize; i++)
    {
        printf("%d\t", G.deck[0][i]);
    }
    printf("\nhand\n");
    for (i = 0; i < handSize; i++)
    {
        printf("%d\t", G.hand[0][i]);
    }
    printf("\ndiscard\n");
    for (i = 0; i < discSize; i++)
    {
        printf("%d\t", G.discard[0][i]);
    }
    */
    //printf("\n\nPLAYING SMITHY\n\n");
    smithyCard(&G, smithyPos); // test the function directly
    //cardEffect(smithy, 30, 30, 30, &G, smithyPos, 0); // test via cardEffect
    /*
    printf("\ndeck\n");
    for (i = 0; i < G.deckCount[P0]; i++)
    {
        printf("%d\t", G.deck[P0][i]);
    }
    printf("\nhand\n");
    for (i = 0; i < G.handCount[P0]; i++)
    {
        printf("%d\t", G.hand[P0][i]);
    }
    printf("\ndiscard\n");
    for (i = 0; i < G.discardCount[P0]; i++)
    {
        printf("%d\t", G.discard[P0][i]);
    }
    printf("\nplayed\n");
    for (i = 0; i < G.playedCardCount; i++)
    {
        printf("%d\t", G.playedCards[i]);
    }
    printf("\n");
    */
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

    //compareStateFull(&G, &original, "");
}

int main()
{
    srand(time(NULL));
    testSmithy();
    return 0;
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