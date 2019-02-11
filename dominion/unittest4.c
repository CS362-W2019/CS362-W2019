/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1





int main() {
    //int i;
    int seed = 1000;
    int maxPlayers = 5;
    int p, r;
    //int currentPlayer;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    //srand((unsigned) time(&t)); //initialize random number generator

    printf ("TESTING whoseTurns():\n");
    for (p = 0; p < maxPlayers; p++)
    {
#if (NOISY_TEST == 1)
            printf("Test game with %d players.\n", p);
#endif
            memset(&G, 23, sizeof(struct gameState));  //clear the game gameState
            initializeGame(p, k, seed, &G); //initialize a new gameState
            //currentPlayer = rand() % (p+1); //randomly chooses a player
            for (r = 0; r < p; r++) {
	    	G.whoseTurn = r;    //set currenty player
            	int returnedPlayer = whoseTurn(&G);


#if (NOISY_TEST == 1)
            	printf("whoseTurn = %d, expected = %d\n", returnedPlayer, r);

#endif
    		assert (whoseTurn(&G) == r); //test return value
}
}


    printf("All tests passed!\n");

    return 0;
}
