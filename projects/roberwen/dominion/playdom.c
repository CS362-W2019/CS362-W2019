#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;
  int k[10] = {ADVENTURER, GARDENS, EMBARGO, VILLAGE, MINION, MINE, CUTPURSE,
           SEA_HAG, TRIBUTE, SMITHY};

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
      if (handCard(i, &G) == COPPER)
    money++;
      else if (handCard(i, &G) == SILVER)
    money += 2;
      else if (handCard(i, &G) == GOLD)
    money += 3;
      else if (handCard(i, &G) == SMITHY)
    smithyPos = i;
      else if (handCard(i, &G) == ADVENTURER)
    adventurerPos = i;
    }

    if (whoseTurn(&G) == 0) {
      if (smithyPos != -1) {
        printf("0: SMITHY played from position %d\n", smithyPos);
        playCard(smithyPos, -1, -1, -1, &G);
        printf("SMITHY played.\n");
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == COPPER){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == SILVER){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == GOLD){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("0: bought PROVINCE\n");
        buyCard(PROVINCE, &G);
      }
      else if (money >= 6) {
        printf("0: bought GOLD\n");
        buyCard(GOLD, &G);
      }
      else if ((money >= 4) && (numSmithies < 2)) {
        printf("0: bought SMITHY\n");
        buyCard(SMITHY, &G);
        numSmithies++;
      }
      else if (money >= 3) {
        printf("0: bought SILVER\n");
        buyCard(SILVER, &G);
      }

      printf("0: end turn\n");
      endTurn(&G);
    }
    else {
      if (adventurerPos != -1) {
        printf("1: ADVENTURER played from position %d\n", adventurerPos);
        playCard(adventurerPos, -1, -1, -1, &G);
        money = 0;
        i=0;
        while(i<numHandCards(&G)){
          if (handCard(i, &G) == COPPER){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == SILVER){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == GOLD){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      }

      if (money >= 8) {
        printf("1: bought PROVINCE\n");
        buyCard(PROVINCE, &G);
      }
      else if ((money >= 6) && (numAdventurers < 2)) {
        printf("1: bought ADVENTURER\n");
        buyCard(ADVENTURER, &G);
        numAdventurers++;
      }else if (money >= 6){
        printf("1: bought GOLD\n");
	    buyCard(GOLD, &G);
        }
      else if (money >= 3){
        printf("1: bought SILVER\n");
	    buyCard(SILVER, &G);
      }
      printf("1: endTurn\n");

      endTurn(&G);
    }
  } // end of While

  printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));

  return 0;
}
