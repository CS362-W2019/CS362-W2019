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
    // Test adventurer

    // Initialization and setup
    struct gameState g1 = {0};
    struct gameState g2 = {0};
    int card = adventurer;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int bonus = 0;
    int player = 0;

    printf("TESTING adventurer:\n----------\n");
  
    // Setup g1 with pre-function values
    g1.hand[player][handPos] = adventurer;
    g1.handCount[player] = 1;
    g1.deck[player][0] = estate;
    g1.deckCount[player] = 1;
    for (int i=0; i<2; i++) {
        g1.discard[player][i] = copper;
    }
    g1.discardCount[player] = 2;
    
    // Execute function on g1 and test results
    int result = cardEffect(card, choice1, choice2, choice3, &g1, handPos, &bonus);
    assertEquals(result, 0, "adventurer: Successfully returned with 0.");
    assertEquals(g1.playedCardCount, 1, "adventurer: Played card pile contains 1 card.");
    assertEquals(g1.handCount[player], 2, "adventurer: Player hand contains 2 cards.");
    assertEquals(g1.hand[player][0], copper, "adventurer: Player hand position 1 contains copper.");
    assertEquals(g1.hand[player][1], copper, "adventurer: Player hand position 2 contains copper.");
    assertEquals(g1.discard[player][0], estate, "adventurer: Discard pile position 1 contains estate.");

    // Setup g2 with expected post-function values
    g2.handCount[player] = 2;
    for (int i=0; i<2; i++) {
        g2.hand[player][i] = copper;
    }
    g2.hand[player][g2.handCount[player]] = -1;

    g2.playedCardCount = 1;
    g2.playedCards[0] = adventurer;

    g2.deckCount[player] = 0;
    for (int i=0; i<2; i++) {
        g2.deck[player][i] = copper;
    }

    g2.discardCount[player] = 1;
    g2.discard[player][0] = estate;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "adventurer: No other changes to gameState.");

    printf("----------\n");

    return 0;
}
