/* Testing Concil Room
  +4Cards, +1Buy, Each other player draws a card.
 * 1. After playing concil room, current player should get 3 more cards. //bug
 * 2. After playing concil room, there should have one more buy in numBuys 
 * 3. After playing concil room, all other players should get 1 more card. //bug
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"
#include "dominion_cards_helpers.h"
#define SEED 1000

void testCardConcilRoom()
{
  int currentPlayer, concilroomPosition = 0, currentHandCount, currentBuys;
  int numPlayers = 2;
  int k[10] = {ADVENTURER, GARDENS, COUNCIL_ROOM, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState* G = newGame();
  bool test_result = true;


	/* initialize a game state and player cards */
	initializeGame(numPlayers, k, SEED, G);
  currentPlayer = whoseTurn(G);

  gainCard(COUNCIL_ROOM, G, 2, currentPlayer);
  currentBuys = G->numBuys;
  currentHandCount = G->handCount[currentPlayer];

  /* get concil room position */
  for(int i = 0; i < G->handCount[currentPlayer]; i++) 
  {
    if(G->hand[currentPlayer][i] == COUNCIL_ROOM)
    {
      concilroomPosition = i;
      break;
    }
  }

  playCouncilRoom(G, currentPlayer, concilroomPosition);

  testEqual("Check COUNCIL ROOM has been played.", COUNCIL_ROOM, G->playedCards[0], &test_result);
  testEqual("Current player should get 3 more cards", 3, G->handCount[currentPlayer] - currentHandCount, &test_result);
  testEqual("There should have one more buy in numBuys", 1, G->numBuys - currentBuys, &test_result);
  /* Check other players */
  for(int i = 0; i < G->numPlayers; i++) 
  {
    int prevHandCount = G->handCount[i];
    if(i != currentPlayer)
    {
      testEqual("All players expect current player shold get one more card", 1, G->handCount[i] - prevHandCount, &test_result);  
    }
  }
  testResult(test_result);

}

int main() {
  testCardConcilRoom();
  return 0;
}