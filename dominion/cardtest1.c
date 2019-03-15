/*
 * cardtest1.c
 *

 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int coppers = 0;
    int silvers = 0;
    int golds = 0;
    int treasuresPre;
    int treasuresPost;
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +2 treasure cards --------------
	printf("TEST 1: +2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (handCard(i, &G) == copper) {
      coppers++;
    }
    else if (handCard(i, &G) == silver) {
      silvers++;
    }
    else if (handCard(i, &G) == gold) {
      golds++;
    }

  }
  treasuresPre = (coppers + silvers + golds);
  printf("Starting number of treasure cards = %d\n", treasuresPre);

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  coppers = 0;
  silvers = 0;
  golds = 0;

  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if (handCard(i, &testG) == copper) {
      coppers++;
    }
    else if (handCard(i, &testG) == silver) {
      silvers++;
    }
    else if (handCard(i, &testG) == gold) {
      golds++;
    }
  }
  treasuresPost = (coppers + silvers + golds);

	printf("final treasures = %d, expected = %d\n", treasuresPost, treasuresPre + 2);

  assert(treasuresPost == treasuresPre + 2);




	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
