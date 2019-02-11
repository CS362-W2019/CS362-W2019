/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;

    int MAX_HAND_COUNT = 5;
    int MAX_DECK_COUNT = 30;
    int MAX_DISCARD_COUNT = 30;
    int h, d, c, total, cardCount;
    int numPlayers = 4;
    int p = 0; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int MAX_SUPPLY = 100;
    // arrays of all coppers, smities, and estates
    int coppers[MAX_SUPPLY];
    //int smithies[MAX_SUPPLY];
    //int estates[MAX_SUPPLY];
    for (i = 0; i < MAX_SUPPLY; i++)
    {
        coppers[i] = copper;
       // smithies[i] = smithy;
       // estates[i] = estate;
    }

    printf ("TESTING fullDeckCount():\n");
      //for (p = 0; p < numPlayers; p++ ) {
      for (h = 0; h< MAX_HAND_COUNT; h++) {
        for (d = 0; d < MAX_DECK_COUNT; d++) {
          for (c = 0; c < MAX_DISCARD_COUNT; c++) {
            total = (h+d+c);
            #if (NOISY_TEST == 1)
                            printf("Test a full deck with  %d copper card(s).\n", total);
            #endif
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayers, k, seed, &G); // initialize a new game

            G.whoseTurn = p;                    //set turn to current player
            G.handCount[p] = h;                 // set the number of cards on hand
            memcpy(G.hand[p], coppers, sizeof(int) * h); // set all the cards in the hand to coppers

            //set entire deck to copper
            G.deckCount[p] = d;
            memcpy(G.deck[p], coppers, sizeof(int) * d);

            //set entire discard to coppers
            G.discardCount[p] = c;
            memcpy(G.discard[p], coppers, sizeof(int) * c);

            cardCount = fullDeckCount(p, copper, &G );

            #if (NOISY_TEST == 1)
                        printf("fullDeckCount = %d, expected = %d\n", cardCount, total);
            #endif

                        assert(cardCount == total); // check if the number of cards is correct
            //change hand to estates

            //change top card of deck to smithy


}}}
    printf("All tests passed!\n");

    return 0;
}
