#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int assertEquals(int a, int b, char* msg)
{   
    if (a==b) {
        printf("PASS: %s\n", msg);
        return 1;
    }
    else {
        printf("FAIL: %s\n", msg);
        return 0;
    }
}

int deepEquals(struct gameState g1, struct gameState g2)
{
    if (g1.numPlayers != g2.numPlayers) {
        return 0;
    }
    for (int i=0; i<treasure_map+1; i++) {
        if (g1.supplyCount[i] != g2.supplyCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<treasure_map+1; i++) {
        if (g1.embargoTokens[i] != g2.embargoTokens[i]) {
            return 0;
        }
    }
    if (g1.outpostPlayed != g2.outpostPlayed) {
        return 0;
    }
    if (g1.outpostTurn != g2.outpostTurn) {
        return 0;
    }
    if (g1.whoseTurn != g2.whoseTurn) {
        return 0;
    }
    if (g1.phase != g2.phase) {
        return 0;
    }
    if (g1.numActions != g2.numActions) {
        return 0;
    }
    if (g1.coins != g2.coins) {
        return 0;
    }
    if (g1.numBuys != g2.numBuys) {
        return 0;
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_HAND; j++) {
            if (g1.hand[i][j] != g2.hand[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1.handCount[i] != g2.handCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            if (g1.deck[i][j] != g2.deck[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1.deckCount[i] != g2.deckCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            if (g1.discard[i][j] != g2.discard[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1.discardCount[i] != g2.discardCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_DECK; i++) {
        if (g1.playedCards[i] != g2.playedCards[i]) {
            return 0;
        }
    }
    if (g1.playedCardCount != g2.playedCardCount) {
        return 0;
    }
    return 1;
} 

int main()
{
    // Test gainCard()

    // Initialization and setup
    struct gameState g1 = {0};
    struct gameState g2 = {0};
    int player = 0;
    enum TOFLAG {discard=0, deck=1, hand=2};

    printf("TESTING gainCard():\n----------\n");

    // Setup g1 with pre-function values
    g1.supplyCount[adventurer] = 0;

    // Execute function on g1 and test results
    assertEquals(gainCard(adventurer, &g1, discard, player), -1, "gainCard(): Cannot gain from empty supply pile.");

    // Setup g2 with expected post-function values
    g2.supplyCount[adventurer] = 0;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "gainCard(): No other changes to gameState.");

    // Setup g1 with pre-function values
    g1.supplyCount[adventurer] = 1;
    g1.discardCount[player] = 0;
    g1.discard[player][g1.discardCount[player]] = 0;

    // Execute function on g1 and test results
    int result = gainCard(adventurer, &g1, discard, player);
    assertEquals(result, 0, "gainCard(): Can gain successfully from non-empty supply pile.");
    assertEquals(supplyCount(adventurer, &g1), 0, "gainCard(): Supply count decreased by 1.");
    assertEquals(g1.discard[player][g1.discardCount[player]-1], adventurer, "gainCard(): Successfully added adventurer to player's discard pile.");
    assertEquals(g1.discardCount[player], 1, "gainCard(): Discard pile count increased by 1.");
    
    // Setup g2 with expected post-function values
    g2.supplyCount[adventurer] = 0;
    g2.discardCount[player] = 1;
    g2.discard[player][g2.discardCount[player]-1] = adventurer;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "gainCard(): No other changes to gameState.");    

    // Setup g1 with pre-function values
    g1.supplyCount[adventurer] = 1;
    g1.deckCount[player] = 0;
    g1.deck[player][g1.deckCount[player]] = 0;

    // Execute function on g1 and test results
    gainCard(adventurer, &g1, deck, player);
    assertEquals(g1.deck[player][g1.deckCount[player]-1], adventurer, "gainCard(): Successfully added adventurer to player's deck.");
    assertEquals(g1.deckCount[player], 1, "gainCard(): Deck count increased by 1.");

    // Setup g2 with expected post-function values
    g2.supplyCount[adventurer] = 0;
    g2.deckCount[player] = 1;
    g2.deck[player][g1.deckCount[player]-1] = adventurer;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "gainCard(): No other changes to gameState.");   

    // Setup g1 with pre-function values
    g1.supplyCount[adventurer] = 1;
    g1.handCount[player] = 0;
    g1.hand[player][g1.handCount[player]] = 0;

    // Execute function on g1 and test results
    gainCard(adventurer, &g1, hand, player);
    assertEquals(g1.hand[player][g1.handCount[player]-1], adventurer, "gainCard(): Successfully added adventurer to player's hand.");
    assertEquals(g1.handCount[player], 1, "gainCard(): Hand count increased by 1.");

    // Setup g2 with expected post-function values
    g2.supplyCount[adventurer] = 0;
    g2.handCount[player] = 1;
    g2.hand[player][g2.handCount[player]-1] = adventurer;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "gainCard(): No other changes to gameState.");   

    printf("----------\n");

    return 0;
}
