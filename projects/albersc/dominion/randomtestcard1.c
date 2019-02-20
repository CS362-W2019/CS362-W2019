#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SILENT 1

int assertEquals(int a, int b, char* msg)
{   
    if (a==b) {
        if (!SILENT) {
            printf("PASS: %s\n", msg);
        }
        return 1;
    }
    else {
        printf("FAIL: %s\n", msg);
        return 0;
    }
}

int deepEquals(struct gameState* g1, struct gameState* g2)
{
    if (g1->numPlayers != g2->numPlayers) {
        return 0;
    }
    for (int i=0; i<treasure_map+1; i++) {
        if (g1->supplyCount[i] != g2->supplyCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<treasure_map+1; i++) {
        if (g1->embargoTokens[i] != g2->embargoTokens[i]) {
            return 0;
        }
    }
    if (g1->outpostPlayed != g2->outpostPlayed) {
        return 0;
    }
    if (g1->outpostTurn != g2->outpostTurn) {
        return 0;
    }
    if (g1->whoseTurn != g2->whoseTurn) {
        return 0;
    }
    if (g1->phase != g2->phase) {
        return 0;
    }
    if (g1->numActions != g2->numActions) {
        return 0;
    }
    if (g1->coins != g2->coins) {
        return 0;
    }
    if (g1->numBuys != g2->numBuys) {
        return 0;
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_HAND; j++) {
            if (g1->hand[i][j] != g2->hand[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1->handCount[i] != g2->handCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            if (g1->deck[i][j] != g2->deck[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1->deckCount[i] != g2->deckCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            if (g1->discard[i][j] != g2->discard[i][j]) {
                return 0;
            }
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        if (g1->discardCount[i] != g2->discardCount[i]) {
            return 0;
        }
    }
    for (int i=0; i<MAX_DECK; i++) {
        if (g1->playedCards[i] != g2->playedCards[i]) {
            return 0;
        }
    }
    if (g1->playedCardCount != g2->playedCardCount) {
        return 0;
    }
    return 1;
}

struct gameState generateGameState()
{
    struct gameState g;

    srand(time(0));

    g.numPlayers = rand() % 3 + 2; // Between 2-4 players

    for (int i=0; i<treasure_map+1; i++) {
        g.supplyCount[i] = rand() % 100; // Between 0-99 cards in each pile
    }

    for (int i=0; i<treasure_map+1; i++) {
        g.embargoTokens[i] = rand() % 2; // Binary
    }

    g.outpostPlayed = rand() % 2; // Binary

    g.outpostTurn = rand() % g.numPlayers; // Random player

    g.whoseTurn = rand() % g.numPlayers;  // Random player

    g.phase = rand() % 3; // Between 0-2

    g.numActions = rand() % 4; // Between 0-3 actions

    g.coins = rand() % 11; // Between 0-10 coins

    g.numBuys = rand() % 4; // Between 0-3 buys

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_HAND; j++) {
            g.hand[i][j] = rand() % (treasure_map + 1); // Assign random card to each spot in hand
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g.handCount[i] = rand() % 11 + 5; // Between 5-15 cards in hand
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            if (j < 10) {
                g.deck[i][j] = rand() % 3 + 4; // First ten cards are treasure
            }
            else {
                g.deck[i][j] = rand() % (treasure_map + 1); // Assign random card to rest of deck
            }
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g.deckCount[i] = rand() % 11 + 5; // Between 5-15 cards in deck
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            g.discard[i][j] = rand() % (treasure_map + 1); // Assign random card to each spot in discard
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g.discardCount[i] = rand() % 11 + 5; // Between 5-15 cards in discard
    }

    for (int i=0; i<MAX_DECK; i++) {
        g.playedCards[i] = rand() % (treasure_map + 1); // Assign random card to each spot in played cards
    }

    g.playedCardCount = rand() % 11; // Between 0-10 cards in played cards

    return g;
}

void deepCopy(struct gameState* g1, struct gameState* g2)
{
    g2->numPlayers = g1->numPlayers;

    for (int i=0; i<treasure_map+1; i++) {
        g2->supplyCount[i] = g1->supplyCount[i];
    }

    for (int i=0; i<treasure_map+1; i++) {
        g2->embargoTokens[i] = g1->embargoTokens[i];
    }

    g2->outpostPlayed = g1->outpostPlayed;

    g2->outpostTurn = g1->outpostTurn;

    g2->whoseTurn = g1->whoseTurn;

    g2->phase = g1->phase;

    g2->numActions = g1->numActions;

    g2->coins = g1->coins;

    g2->numBuys = g1->numBuys;

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_HAND; j++) {
            g2->hand[i][j] = g1->hand[i][j];
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g2->handCount[i] = g1->handCount[i];
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            g2->deck[i][j] = g1->deck[i][j];
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g2->deckCount[i] = g1->deckCount[i];
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            g2->discard[i][j] = g1->discard[i][j];
        }
    }

    for (int i=0; i<MAX_PLAYERS; i++) {
        g2->discardCount[i] = g1->discardCount[i];
    }

    for (int i=0; i<MAX_DECK; i++) {
        g2->playedCards[i] = g1->playedCards[i];
    }

    g2->playedCardCount = g1->playedCardCount;
}

void printComp(struct gameState* g1, struct gameState* g2)
{
    printf("gameState Before\tgameState After\n");

    printf("Num players: %d\t%d\n", g1->numPlayers, g2->numPlayers);
    for (int i=0; i<treasure_map+1; i++) {
        printf("Supply count %d: %d\t%d\n", i, g1->supplyCount[i], g2->supplyCount[i]);
    }
    for (int i=0; i<treasure_map+1; i++) {
        printf("Embargo tokens %d: %d\t%d\n", i, g1->embargoTokens[i], g2->embargoTokens[i]);
    }
    printf("Outpost played: %d\t%d\n", g1->outpostPlayed, g2->outpostPlayed);
    printf("Outpost turn: %d\t%d\n", g1->outpostTurn, g2->outpostTurn);
    printf("WhoseTurn: %d\t%d\n", g1->whoseTurn, g2->whoseTurn);
    printf("Phase: %d\t%d\n", g1->phase, g2->phase);
    printf("NumActions: %d\t%d\n", g1->numActions, g2->numActions);
    printf("Coins: %d\t%d\n", g1->coins, g2->coins);
    printf("NumBuys: %d\t%d\n", g1->numBuys, g2->numBuys);
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_HAND; j++) {
            printf("Hand - player %d - position %d: %d\t%d\n", i, j, g1->hand[i][j], g2->hand[i][j]);
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        printf("HandCount - player %d: %d\t%d\n", i, g1->handCount[i], g2->handCount[i]);
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            printf("Deck - player %d - position %d: %d\t%d\n", i, j, g1->deck[i][j], g2->deck[i][j]);
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        printf("DeckCount - player %d: %d\t%d\n", i, g1->deckCount[i], g2->deckCount[i]);
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        for (int j=0; j<MAX_DECK; j++) {
            printf("Discard - player %d - position %d: %d\t%d\n", i, j, g1->discard[i][j], g2->discard[i][j]);
        }
    }
    for (int i=0; i<MAX_PLAYERS; i++) {
        printf("DiscardCount - player %d: %d\t%d\n", i, g1->discardCount[i], g2->discardCount[i]);
    }
    for (int i=0; i<MAX_DECK; i++) {
        printf("PlayedCard - position %d: %d\t%d\n", i, g1->playedCards[i], g2->playedCards[i]);
    }
    printf("PlayedCardCount: %d\t%d\n", g1->playedCardCount, g2->playedCardCount);
}

int main()
{
    srand(time(0));

    int passCount = 0;
    int testCount = 1000;

    for (int i=0; i<testCount; i++) {

        struct gameState g = generateGameState();

        int player = rand() % g.numPlayers;
        int handPos = rand() % g.handCount[player];

        // Setup g with pre-function values
        g.hand[player][handPos] = outpost;
        g.whoseTurn = player;

        // Save old values
        int oldHandCount = g.handCount[player];
        int oldPlayedCardCount = g.playedCardCount;
        struct gameState before = g;

        // Execute function on g and test results
        int result = cardEffect(outpost, 0, 0, 0, &g, handPos, NULL);

        printf("TESTING outpost ITERATION %d:\n----------\n", i+1);

        int pass = 1;

        if (!assertEquals(result, 0, "outpost: Successfully returned with 0.")) {
            pass = 0;
        }
        if (!assertEquals(g.playedCardCount, oldPlayedCardCount + 1, "outpost: Played card pile contains 1 more card.")) {
            pass = 0;
        }
        if (!assertEquals(g.handCount[player], oldHandCount - 1, "outpost: Player hand contains 1 less card.")) {
            pass = 0;
        }
        if (!assertEquals(g.outpostPlayed, 1, "outpost: outpost flag set to 1.")) {
            pass = 0;
        }

        if (pass) {
            printf("ALL TESTS PASSED\n");
            passCount++;
        }
        else {
            // If test fails, print all data in gameState before and after function is called
            printComp(&before, &g);
        }

        printf("----------\n");
    }

    printf("Tests passed: %d\n", passCount);
    printf("Total tests: %d\n", testCount);

    return 0;
}