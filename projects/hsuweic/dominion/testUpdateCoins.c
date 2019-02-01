/* -----------------------------------------------------------------------
* Demonstration of how to write unit tests for dominion-base
* Include the following lines in your makefile:
*
* testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
*      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10;
  int p, r, handCount;
  int bonus;
  int k[10] = {adventurer, council_room, feast, gardens, mine
              , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int maxHandCount = 5;
  // arrays of all coppers, silvers, and golds
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  bool passedTest1 = TRUE;
  bool passedTest2 = TRUE;
  bool passedTest3 = TRUE;

  for (i = 0; i < MAX_HAND; i++)
  {
      coppers[i] = copper;
      silvers[i] = silver;
      golds[i] = gold;
  }

  printf ("TESTING updateCoins():\n");

  for (p = 0; p < numPlayer; p++)
  {
      for (handCount = 1; handCount <= maxHandCount; handCount++)
      {
          for (bonus = 0; bonus <= maxBonus; bonus++)
          {
              printf("Purpose: Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
              memset(&G, 23, sizeof(struct gameState));   // clear the game state
              r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
              G.handCount[p] = handCount;                 // set the number of cards on hand

              /* Test1: Set all the cards to copper */
              memcpy(G.hand[p], coppers, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);
              printf("TEST1: Number of coins after setting all the cards to COPPER\n")
              /* check if the number of coins is correct */
              if(G.coins == handCount * 1 + bonus) 
              {
                printf("TEST1 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
              }
              else 
              {
                 passedTest1 = FALSE;
                 printf("TEST1 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
              }

              /* Test2: Set all the cards to silver */
              memcpy(G.hand[p], silvers, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);
              printf("TEST2: Number of coins after setting all the cards to SILVER\n")
              /* check if the number of coins is correct */
              if(G.coins == handCount * 2 + bonus) 
              {
                printf("TEST2 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
              }
              else 
              {
                passedTest2 = FALSE;
                printf("TEST2 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
              }

              /* Test3: Set all the cards to gold */
              memcpy(G.hand[p], golds, sizeof(int) * handCount); 
              updateCoins(p, &G, bonus);
              printf("TEST3: Number of coins after setting all the cards to GOLD\n")
              if(G.coins == handCount * 3 + bonus) 
              {
                printf("TEST3 PASSED: G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
              }
              else 
              {
                 passedTest3 = FALSE;
                 printf("TEST3 FALID: G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
              }
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