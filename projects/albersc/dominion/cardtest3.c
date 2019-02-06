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
    // Test outpost

    // Initialization and setup
    struct gameState g1 = {0};
    struct gameState g2 = {0};
    int card = outpost;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int bonus = 0;
    int player = 0;

    printf("TESTING outpost:\n----------\n");
  
    // Setup g1 with pre-function values
    g1.hand[player][handPos] = outpost;
    g1.handCount[player] = 1;

    // Execute function on g1 and test results
    int result = cardEffect(card, choice1, choice2, choice3, &g1, handPos, &bonus);
    assertEquals(result, 0, "outpost: Successfully returned with 0.");
    assertEquals(g1.playedCardCount, 1, "outpost: Played card pile contains 1 card.");
    assertEquals(g1.handCount[player], 0, "outpost: Player hand contains 0 cards.");
    assertEquals(g1.outpostPlayed, 1, "outpost: outpost flag set to 1.");

    // Setup g2 with expected post-function values
    g2.handCount[player] = 0;
    g2.hand[player][g2.handCount[player]] = -1;

    g2.playedCardCount = 1;
    g2.playedCards[0] = outpost;

    g2.outpostPlayed = 1;

    // Compare g1 and g2 to ensure no unexpected changes
    assertEquals(deepEquals(g1, g2), 1, "outpost: No other changes to gameState.");

    printf("----------\n");

    return 0;
}
