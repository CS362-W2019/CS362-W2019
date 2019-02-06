/* Testing Smithy
 * 1. Should gain 3 cards from deck to player's hand
 * 2. After playing Smity, make sure total cards on hand will + 3 - 1 = +2
 * 3. After playing Smity, make sure total cards on deck will - 3 + 1 = -2
 * 4. After playing Smity, the top value of playedCard should be SMITHY
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

void testCardSmithy()
{
  int currentPlayer, smithyPosition = 0, currentHandCount, currentDeckCount;
  int numPlayers = 2;
  int handHold[MAX_HAND];
  int deckHold[MAX_DECK];
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState* G = newGame();
  bool test_result = true;


	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  /* Get the cards on both deck and hand */
  for(int i = 0; i < G->handCount[currentPlayer]; i++) 
  {
    handHold[i] = G->hand[currentPlayer][i];
  }
  
  for(int i = 0; i < G->deckCount[currentPlayer]; i++)
  {
    deckHold[i] = G->deck[currentPlayer][i];
  }

  /* Add Smith to hand */
  gainCard(SMITHY, G, 2, currentPlayer);

  /* Get Smithy position */
  for(int i = 0; i < G->handCount[currentPlayer]; i++) 
  {
    if(G->hand[currentPlayer][i] == SMITHY)
    {
      smithyPosition = i;
      break;
    }
  }

  currentHandCount = G->handCount[currentPlayer];
  currentDeckCount = G->deckCount[currentPlayer];
  playSmithy(G, currentPlayer, smithyPosition);
  testEqual("Number of cards in hand should + 3 - 1 after playing Smithy", 2, G->handCount[currentPlayer] - currentHandCount, &test_result);
  testEqual("Number of cards in deck should - 3 + 1 after playing Smithy", 2, currentDeckCount - G->deckCount[currentPlayer], &test_result);
  testEqual("Check SMITHY has been played.", SMITHY, G->playedCards[0], &test_result);
  testEqual("Difference between hand and deck should increase by 4",
             currentHandCount - currentDeckCount + 4,  G->handCount[currentPlayer] - G->deckCount[currentPlayer], &test_result);
  testResult(test_result);
}

int main() {
  testCardSmithy();
  return 0;
}