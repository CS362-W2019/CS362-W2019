/* Testing FullDeck
 * 1. Check the default number of Cooper / Silver in the deck
 * 2. Check the numbe of double coopers in the deck
 * 3. Check if CUTPURSE is in the deck when we start the game (It should not be there)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#define SEED 10

void testFullDeckCount()
{
  int numPlayer = 2;
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState *G;
  bool test_result = true;
  int handCard = 0;

  G = newGame();
  initializeGame(numPlayer, k, SEED, G);

  testEqual("No card: should return 0.", 0, fullDeckCount(handCard, CUTPURSE, G), &test_result);
  testEqual("Defaul SILVER: should return 0.", 0, fullDeckCount(handCard, SILVER, G), &test_result);
  testEqual("Defaul COPPER: should return 0.", 7, fullDeckCount(handCard, COPPER, G), &test_result);

  memcpy(G->discard[0], G->deck[0], sizeof(G->deck[0]));
  G->discardCount[0] = 10;
  testEqual("Double COPPER size: should return 14.", 14, fullDeckCount(handCard, COPPER, G), &test_result);
  testResult(test_result);

}

int main() {
  testFullDeckCount();
  return 0;
}