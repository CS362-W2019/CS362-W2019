#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("Starting game.\n");

  initializeGame(2, k, atoi(argv[1]), &G);

  int money = 0;
  int smithyPos = -1;
  int adventurerPos = -1;
  int i=0;

  int numSmithies = 0;
  int numAdventurers = 0;

  while (!isGameOver(&G)) {
    money = 0;
    smithyPos = -1;
    adventurerPos = -1;
    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper)
    money++;
      else if (handCard(i, &G) == silver)
    money += 2;
      else if (handCard(i, &G) == gold)
    money += 3;
      else if (handCard(i, &G) == smithy)
    smithyPos = i;
      else if (handCard(i, &G) == adventurer)
    adventurerPos = i;
    }

    if (whoseTurn(&G) == 0) {
      if (smithyPos != -1) {
        printf("0: smithy played from position %d\n", smithyPos);
        playCard(smithyPos, -1, -1, -1, &G);
        printf("smithy played.\n");
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("0: bought province\n");
        buyCard(province, &G);
      }
      else if (money >= 6) {
        printf("0: bought gold\n");
        buyCard(gold, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        printf("0: bought smithy\n");
        buyCard(smithy, &G);
        numSmithies++;
      }
      else if (money >= 3) {
        printf("0: bought silver\n");
        buyCard(silver, &G);
      }

      printf("0: end turn\n");
      endTurn(&G);
    }
    else {
      if (adventurerPos != -1) {
        printf("1: adventurer played from position %d\n", adventurerPos);
        playCard(adventurerPos, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("1: bought province\n");
        buyCard(province, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        printf("1: bought adventurer\n");
        buyCard(adventurer, &G);
        numAdventurers++;
      }else if (money >= 6){
        printf("1: bought gold\n");
	    buyCard(gold, &G);
        }
      else if (money >= 3){
        printf("1: bought silver\n");
	    buyCard(silver, &G);
      }
      printf("1: endTurn\n");

      endTurn(&G);
    }
  } // end of While

  printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));

  return 0;
}
