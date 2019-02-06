/* Testing Village
 * +1 card, +2 Action
 * 1. After playing Village, player should get 1 more card ///bug
 * 2. After playing Village, player should get 2 more Actions
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#include "dominion_cards_helpers.h"
#define SEED 1000

void testCardFeast()
{
  int currentPlayer, villagePosition = 0, currentHandCount, currentAction;
  int numPlayers = 2;
  int k[10] = {ADVENTURER, GARDENS, COUNCIL_ROOM, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState* G = newGame();
  bool test_result = true;


	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  gainCard(VILLAGE, G, 2, currentPlayer);
  currentAction = G->numActions;
  currentHandCount = G->handCount[currentPlayer];

  /* get Village position */
  for(int i = 0; i < G->handCount[currentPlayer]; i++) 
  {
    if(G->hand[currentPlayer][i] == VILLAGE)
    {
      villagePosition = i;
      break;
    }
  }

  playVILLAGE(G, currentPlayer, villagePosition);

  testEqual("Check VILLAGE has been played.", VILLAGE, G->playedCards[0], &test_result);
  testEqual("Current player should get 1 more cards", 1, G->handCount[currentPlayer] - currentHandCount, &test_result);
  testEqual("There should have 2 more actions", 2, G->numActions - currentAction, &test_result);
  
  testResult(test_result);
}

int main() {
  testCardFeast();
  return 0;
}