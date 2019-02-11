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

void testSteward()
{
    int i, stewPos;

    struct gameState G;
    struct gameState G2;
    struct gameState G_ORIG;
    // initialize with all cards available
    int k[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                 village, baron, great_hall, minion, steward, tribute, ambassador,
                 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    initializeGame(2, k, 30, &G);

    G.handCount[0] = 5;
    G.whoseTurn = 0;
    stewPos = 0;
    for (i=0; i<G.handCount[0]; i++) {
        G.hand[0][i] = curse;
    }
    G.hand[0][stewPos] = steward;

    // Snapshot the gamestate
    memcpy(&G2, &G, sizeof(G2));
    memcpy(&G_ORIG, &G, sizeof(G2));

    // Kick the card effect
    cardEffect(steward, 1, 0, 0, &G, stewPos, 0);

    // Simulate the effect on the snapshoted gamestate
    drawCard(whoseTurn(&G2), &G2);
    drawCard(whoseTurn(&G2), &G2);
    discardCard(stewPos, whoseTurn(&G2), &G2, 0);

    // Check that the effect is correct.
    if (memcmp(&G, &G2, sizeof(G))) {
        printf("FAIL --- +2 cards. Game state modified in unexpected ways\n");
    }


    // Reset to orginal state
    memcpy(&G, &G_ORIG, sizeof(G2));
    memcpy(&G2, &G_ORIG, sizeof(G2));

    // Run the effect
    cardEffect(steward, 2, 0, 0, &G, stewPos, 0);

    // Check the effect
    if (G.coins != G_ORIG.coins + 2) {
        printf("FAIL --- incorrect number of coins added\n");
    }

    // Reset to orginal state
    memcpy(&G, &G_ORIG, sizeof(G2));
    memcpy(&G2, &G_ORIG, sizeof(G2));

    // Run the effect
    cardEffect(steward, 3, 1, 2, &G, stewPos, 0);

    // Simulate
    discardCard(1, whoseTurn(&G2), &G2, 1);
    discardCard(2, whoseTurn(&G2), &G2, 1);
    discardCard(stewPos, whoseTurn(&G2), &G2, 0);

    // Check that the effect is correct.
    if (memcmp(&G, &G2, sizeof(G))) {
        printf("FAIL --- Trash 2 cards. Game state modified in unexpected ways\n");
    }
}

int main()
{
    srand(time(NULL));
    testSteward();
    return 0;
}
