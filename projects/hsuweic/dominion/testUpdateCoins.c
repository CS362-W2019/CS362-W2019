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
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10;
  int maxHandCount = 5;
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE, SEA_HAG, TRIBUTE, SMITHY};
  
  struct gameState G;

  
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];

  bool passedTest1 = true;
  bool passedTest2 = true;
  bool passedTest3 = true;

  /* Assign coins into the array */
  for (int i = 0; i < MAX_HAND; i++)
  {
      coppers[i] = COPPER;
      silvers[i] = SILVER;
      golds[i] = GOLD;
  }

  printf ("TESTING updateCoins():\n");
  printf("TEST1: Number of coins after setting all the cards to COPPER\n");
  printf("TEST2: Number of coins after setting all the cards to SILVER\n");
  printf("TEST3: Number of coins after setting all the cards to GOLD\n");

  for (int p = 0; p < numPlayer; p++)
  {
      for (int handCount = 1; handCount <= maxHandCount; handCount++)
      {
          for (int bonus = 0; bonus <= maxBonus; bonus++)
          {
              printf("Purpose: Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
              memset(&G, 23, sizeof(struct gameState));   // clear the game state
              initializeGame(numPlayer, k, seed, &G);     // initialize a new game
              G.handCount[p] = handCount;                 // set the number of cards on hand

              /* Test1: Set all the cards to copper */
              memcpy(G.hand[p], coppers, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);

              /* check if the number of coins is correct */
              if(G.coins == handCount * 1 + bonus) 
              {
                printf("TEST1 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
              }
              else 
              {
                 passedTest1 = false;
                 printf("TEST1 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
              }

              /* Test2: Set all the cards to silver */
              memcpy(G.hand[p], silvers, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);
              
              /* check if the number of coins is correct */
              if(G.coins == handCount * 2 + bonus) 
              {
                printf("TEST2 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
              }
              else 
              {
                passedTest2 = false;
                printf("TEST2 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
              }

              /* Test3: Set all the cards to gold */
              memcpy(G.hand[p], golds, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);

              if(G.coins == handCount * 3 + bonus) 
              {
                printf("TEST3 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
              }
              else 
              {
                 passedTest3 = false;
                 printf("TEST3 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
              }
              printf("\n");
          }
      }
  }
  if(passedTest1 && passedTest2 && passedTest2)
  {
    printf("All tests passed!\n");
  }
  else
  {
    printf("You got some bugs, please read the error message.\n");
  }
  

  return 0;
}