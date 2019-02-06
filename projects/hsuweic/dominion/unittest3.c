/* Testing New Game
 * 1. Value of gameState pointer should not be NULL after initialized
 * 2. Size of instance G should be the same as gameState
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#define SEED 1000

void testNewGame()
{
  struct gameState* G = NULL;
  bool test_result = true;
  testEqual("There is no instance when we first create the G pointer.", G == NULL, 1, &test_result);

  G = newGame();
  testEqual("After we call newGame(), G pointer should have value.", G != NULL, 1, &test_result);

  /* Test the size of G pointer */
  testEqual("Size of the new game should equal to gameState.", sizeof(*G), sizeof(struct gameState), &test_result);
  testResult(test_result);

}

int main() {
  testNewGame();
  return 0;
}