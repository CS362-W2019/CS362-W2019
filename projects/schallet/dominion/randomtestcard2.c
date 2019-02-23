//randomtestcard2.c
/************************************
** randomtestcard2.c
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
  printf("~~~~~Begining Card 2 Random Testing~~~~~\n");
  printf("~~~~~Random Testing: sea_hag effect~~~~~\n");
  printf("Test 1: positive control, call sea_hag effect\n");
  //need a valid game in progress to call sea_hagEffect
  //or else it segfaults
  int myHandPos = 0;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine,
    cutpurse,sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int result;
  //create and initialize a game state
  struct gameState myState;
  memset(&myState, 0, sizeof(myState));
  initializeGame(numPlayers, k, seed, &myState);

  //call villageEffect, should return zero
  result = sea_hagEffect(&myState);
  printf("Test result: %d\n", result);

}



//end randomtestcard2.c
