/* Testing updateCoins()
 * 1. Make sure the relationship between handCount, coins in the player and bonus is correct.
 * 2. COPPER: += 1 coin
 * 3. SILVER: += 2 coins
 * 4. GOLD: += 3 coins
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test_helper.h"
#include "rngs.h"

void testUpdateCoins()
{
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10;
  int maxHandCount = 5;
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  struct gameState G;
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  bool test_result = true;

  /* Assign coins into the array */
  for (int i = 0; i < MAX_HAND; i++)
  {
      coppers[i] = COPPER;
      silvers[i] = SILVER;
      golds[i] = GOLD;
  }

  printf ("TESTING updateCoins():\n");

  for (int p = 0; p < numPlayer; p++)
  {
    for (int handCount = 1; handCount <= maxHandCount; handCount++)
      {
        for (int bonus = 0; bonus <= maxBonus; bonus++)
        {
          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          initializeGame(numPlayer, k, seed, &G);     // initialize a new game
          G.handCount[p] = handCount;                 // set the number of cards on hand

          /* Test1: Set all the cards to copper */
          memcpy(G.hand[p], coppers, sizeof(int) * handCount); 
          updateCoins(p, &G, bonus);
          testEqual("Number of coins after setting all the cards to COPPER.", G.coins, handCount * 1 + bonus, &test_result);

          /* Test2: Set all the cards to silver */
          memcpy(G.hand[p], silvers, sizeof(int) * handCount); 
          updateCoins(p, &G, bonus);
          testEqual("Number of coins after setting all the cards to SILVER.", G.coins, handCount * 2 + bonus, &test_result);  
          
          /* Test3: Set all the cards to gold */
          memcpy(G.hand[p], golds, sizeof(int) * handCount); 
          updateCoins(p, &G, bonus);
          testEqual("Number of coins after setting all the cards to GOLD.", G.coins, handCount * 3 + bonus, &test_result);
          printf("\n");
      }
    }
  }
  testResult(test_result);
}

int main() {
  testUpdateCoins();
  return 0;
}