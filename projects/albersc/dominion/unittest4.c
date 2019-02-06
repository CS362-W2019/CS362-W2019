#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include "interface.h"

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
    // Test buyCard()

    // Initialization and setup
    struct gameState g1 = {0};
    struct gameState g2 = {0};
    int player = 0;
    enum TOFLAG {discard=0, deck=1, hand=2};

    printf("TESTING buyCard():\n----------\n");

    // Setup g1 with pre-function values
    g1.numBuys = 0;

    // Execute function on g1 and test results
    assertEquals(buyCard(adventurer, &g1), -1, "buyCard(): Cannot buy if player has less than 1 buy remaining.");

    // Setup g2 with expected post-function values
    g2.numBuys = 0;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "buyCard(): No other changes to gameState.");

    // Setup g1 with pre-function values
    g1.numBuys = 1;
    g1.supplyCount[adventurer] = 0;

    // Execute function on g1 and test results
    assertEquals(buyCard(adventurer, &g1), -1, "buyCard(): Cannot buy if selected supply pile is empty.");

    // Setup g2 with expected post-function values
    g2.numBuys = 1;
    g2.supplyCount[adventurer] = 0;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "buyCard(): No other changes to gameState.");

    // Setup g1 with pre-function values
    g1.numBuys = 1;
    g1.supplyCount[adventurer] = 1;
    g1.coins = 0;

    // Execute function on g1 and test results
    assertEquals(buyCard(adventurer, &g1), -1, "buyCard(): Cannot buy if player has less coins than selected card cost.");

    // Setup g2 with expected post-function values
    g2.numBuys = 1;
    g2.supplyCount[adventurer] = 1;
    g2.coins = 0;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "buyCard(): No other changes to gameState.");

    // Setup g1 with pre-function values
    g1.numBuys = 1;
    g1.supplyCount[adventurer] = 1;
    g1.coins = 10; 

    // Execute function on g1 and test results
    int result = buyCard(adventurer, &g1);
    assertEquals(result, 0, "buyCard(): Card bought successfully.");
    assertEquals(g1.phase, 1, "buyCard(): Phase is now 1.");
    assertEquals(g1.numBuys, 0, "buyCard(): Player has 0 buys left.");
    assertEquals(g1.coins, 10-ADVENTURER_COST, "buyCard(): Player has 4 coins left.");

    // Setup g2 with expected post-function values
    gainCard(adventurer, &g2, discard, player);
    g2.phase = 1;
    g2.numBuys = 0;
    g2.coins = 10-ADVENTURER_COST;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "buyCard(): No other changes to gameState.");

    printf("----------\n");

    return 0;
}
