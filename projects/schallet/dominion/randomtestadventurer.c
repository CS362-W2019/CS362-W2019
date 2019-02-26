//randomtestadventurer.c
/************************************
** randomtestadventurer.c
** CS362 winter 2019
** Assignment 4
** Terezie (Tera) Schaller
*************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
int main(){
  printf("~~~~~Begining Adventurer Card Random Testing~~~~~\n");
  printf("~~~~~Random Testing: Adventurer Effect~~~~~\n");
  printf("Test 1: positive control, call adventurer effect\n");
  //need a valid game in progress to call adventurerEffect
  //or else it segfaults
  //int myHandPos = 0;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine,
    cutpurse,sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int result;

  //create and initialize a game state
  struct gameState myState;
  struct gameState myState2;
  memset(&myState, 0, sizeof(myState));
  memset(&myState2, 0, sizeof(myState));
  initializeGame(numPlayers, k, seed, &myState);

  //call villiage effect and show result
  result = villageEffect(&myState, myHandPos);
  //printf("Test result: %d\n", result);
  if (result == 0){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }


  printf("~~~~~End random testing of adventurer~~~~~\n");

}



//end randomtestadventurer.c
