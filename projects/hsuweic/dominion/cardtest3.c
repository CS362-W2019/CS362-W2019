/* Testing Feast
 * 1.  
 * 2. 
 * 3. 
 * 4. 
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#include "dominion_cards_helpers.h"
#define TESTCARD "ADVENTURER"
#define SEED 1000

void testCardFeast()
{
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState *G = newGame()
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  bool test_result = true;

	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	/* ----------- TEST 1:  ------------- */
	printf("TEST 1: \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(ADVENTURER, choice1, choice2, choice3, &testG, handpos, &bonus);


  testEqual("Test Hand Count", , test_result);

  /* ----------- TEST 2:  ------------- */
	printf("TEST 2: \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(ADVENTURER, choice1, choice2, choice3, &testG, handpos, &bonus);


  testEqual("Test Hand Count", , test_result);
}

int main() {
  testCardFeast();
  return 0;
}