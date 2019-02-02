/* Testing Shuffle
 * 1. Test the feature checking when deckCount is smaller then 0.
 * 2. Test the return value in the normal situation.
 * 3. Test the shuffle function in different card set with same number of player.
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#define DECK_COUNT 10
#define SEED 1000

void testShuffle()
{
  int numPlayer = 1;
  struct gameState *G ;
  struct gameState *G_test;
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  int difference = 0;
  bool test_result = true;

  printf ("TESTING shuffle():\n");
  G = newGame();
  testEqual("When the deck of player is empty, it should return -1.", -1, shuffle(numPlayer, G), &test_result);

  G->deckCount[numPlayer] = DECK_COUNT;
  testEqual("When the deck Count is not empty, it should return 0.", 0, shuffle(numPlayer, G), &test_result);

  shuffle(numPlayer, G);

  G_test = newGame();
  G_test->deckCount[numPlayer] = 10;

  initializeGame(numPlayer, k, SEED, G);
  initializeGame(numPlayer, k, SEED, G_test);
  shuffle(numPlayer, G);
  shuffle(numPlayer, G_test);

  for(int i = 0; i < DECK_COUNT; i++)
  {
    difference += (G->deck[0][i] - G_test->deck[0][i]); 
  }

  testEqual("Shuffle should have the same result for every game in one player.", 0, difference, &test_result);
  testResult(test_result);
}

int main() {
  testShuffle();
  return 0;
}