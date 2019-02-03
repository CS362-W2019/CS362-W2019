/* Testing Adventurer
  Reveal cards from your deck until you reveal 2 Treasure
  cards. Put those Treasure cards into your hand and discard
  the other revealed card.
 * 1. After playing Adventurer, there should have 2 Treasure(GOLD/SILVER/COPPER) in hand.
 * 2. After playing Adventurer, there should not have any Treasure in the discard
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
#define SEED 1000

void testCardAdventurer()
{
  int currentPlayer, currentHandCount;
  int numPlayers = 2;
  int handHold[MAX_HAND];
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState* G = newGame();
  bool test_result = true;


	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  /* Test for COPPER */
  G->deck[currentPlayer][0] = ESTATE;
  G->deck[currentPlayer][1] = COPPER;
  G->deck[currentPlayer][2] = ESTATE;
  G->deck[currentPlayer][3] = ESTATE;
  G->deck[currentPlayer][4] = ESTATE;
  G->deck[currentPlayer][5] = COPPER;

  gainCard(ADVENTURER, G, 2, currentPlayer);
  currentHandCount = G->handCount[currentPlayer];
  playAdventurer(G, handHold, currentPlayer);
  printf("=============== TEST COPPER ===============\n");
  printf("In Deck: ESTATE/COPPER/ESTATE/ESTATE/ESTATE/CPPPER \n");
  testEqual("There should have 3 ESTATE were discarded", 4, G->discardCount[currentPlayer], &test_result);
  testEqual("There should have 2 COPPER in HAND", 2, G->handCount[currentPlayer] - currentHandCount, &test_result);

	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  /* Test for SILVER */
  G->deck[currentPlayer][0] = ESTATE;
  G->deck[currentPlayer][1] = SILVER;
  G->deck[currentPlayer][2] = ESTATE;
  G->deck[currentPlayer][3] = ESTATE;
  G->deck[currentPlayer][4] = ESTATE;
  G->deck[currentPlayer][5] = SILVER;

  gainCard(ADVENTURER, G, 2, currentPlayer);
  currentHandCount = G->handCount[currentPlayer];
  playAdventurer(G, handHold, currentPlayer);
  printf("=============== TEST SILVER ===============\n");
  printf("In Deck: ESTATE/SILVER/ESTATE/ESTATE/ESTATE/SILVER \n");
  testEqual("There should have 3 ESTATE were discarded", 4, G->discardCount[currentPlayer], &test_result);
  testEqual("There should have 2 SILVER in HAND", 2, G->handCount[currentPlayer] - currentHandCount, &test_result);

  /* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  /* Test for GOLD */
  G->deck[currentPlayer][0] = ESTATE;
  G->deck[currentPlayer][1] = GOLD;
  G->deck[currentPlayer][2] = ESTATE;
  G->deck[currentPlayer][3] = ESTATE;
  G->deck[currentPlayer][4] = ESTATE;
  G->deck[currentPlayer][5] = GOLD;

  gainCard(ADVENTURER, G, 2, currentPlayer);
  currentHandCount = G->handCount[currentPlayer];
  playAdventurer(G, handHold, currentPlayer);
  printf("=============== TEST GOLD ===============\n");
  printf("In Deck: ESTATE/GOLD/ESTATE/ESTATE/ESTATE/CPPPER \n");
  testEqual("There should have 3 ESTATE were discarded", 4, G->discardCount[currentPlayer], &test_result);
  testEqual("There should have 2 GOLD in HAND", 2, G->handCount[currentPlayer] - currentHandCount, &test_result);

  testResult(test_result);
}

int main() {
  testCardAdventurer();
  return 0;
}