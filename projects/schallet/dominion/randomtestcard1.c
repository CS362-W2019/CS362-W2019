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
  int result, result1;
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
  int randPlayer;
  int gameSeed;
  //repeat 100 times
  //start game with 2-4 players
  //rand() % 3 + 2
  //seed InitializeGame with 1-1000
  //rand() % 1000
  int i;
  for (i = 0; i < 100; i++){
    randPlayer = rand() % 3 + 2;
    gameSeed = rand() % 1000;
    printf("random player number: %d\n", randPlayer;
    printf("random seed number: %d\n", gameSeed;
    memset(&myState, 0, sizeof(myState));
    initializeGame(randPlayer, k, gameSeed, &myState);
    printf("villiageEffec on random game state: ")
    result1 = villageEffect(&myState, myHandPos);
    if (result1 == 0){
      printf("PASSED\n");
    } else {
      printf("FAILED\n");
    }
  }





}

//end randomtestcard1.c
