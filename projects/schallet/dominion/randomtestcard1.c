/************************************
** randomtestcard1.c
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
#include <time.h>

int main(){
  printf("~~~~~Begining Card 1 Random Testing~~~~~\n");
  printf("~~~~~Random Testing: Village effect~~~~~\n");
  printf("Test 1: positive control, call villageEffect: ");
  //need a valid game in progress to call adventurerEffect
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

  //call villiage effect and show result
  result = villageEffect(&myState, myHandPos);
  //printf("Test result: %d\n", result);
  if (result == 0){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //randomize Testing
  //randomize # players and seed to initializeGame
  srand(time(0));
  int numPlayer;
  int gameSeed;
  //repeat 100 times
  //seed game with 2-4 players
  int i;
  int myNum;
  for (i = 0; i < 10; i++){
    myNum = (rand() % 3 + 2);
    printf("random player number: %d\n", myNum);
  }

  //select random seed to shuffle deck



}

//end randomtestcard1.c
