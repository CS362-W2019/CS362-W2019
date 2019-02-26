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
  printf("Test 1: positive control, call adventurer effect: ");
  //need a valid game in progress to call adventurerEffect
  //or else it segfaults
  //int myHandPos = 0;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine,
    cutpurse,sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int result, result1;

  //create and initialize a game state
  struct gameState myState;
  struct gameState myState2;
  memset(&myState, 0, sizeof(myState));
  memset(&myState2, 0, sizeof(myState));
  initializeGame(numPlayers, k, seed, &myState);

  //call villiage effect and show result
  result = adventurerEffect(&myState);
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
  int testFail = 0;
  int passedTests = 0;
  int i;
  for (i = 0; i < 100; i++){
    testFail = 0;
    randPlayer = rand() % 3 + 2;
    gameSeed = rand() % 1000;
    //initialize game state
    memset(&myState, 0, sizeof(myState));
    memset(&myState2, 0, sizeof(myState));
    initializeGame(randPlayer, k, gameSeed, &myState);
    //copy initialized game state for testing
    memcpy(&myState2, &myState, sizeof(struct gameState));
    //run advenurerEffect on second game state, compare states in tests
    result1 = adventurerEffect(&myState2);
    if (result1 != 0){
      printf("Test 1: return adventurerEffect: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //check that hand has increase by 2 card
    int currentPlayer = whoseTurn(&myState2);
    int result2 = myState.handCount[currentPlayer];
    int result3 = myState2.handCount[currentPlayer];
    printf("Test 2 - gained 2 treasure to hand: ");
    if ((result3 - result2) != 2){
      printf("Test 2: gained 2 treasure to hand: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;

    }



    //if all tests passed, add to total passed
    if (testFail == 0){
      passedTests += 1;
    }

  }//end for loop (100x)

  printf("Total tests passed: %d out of 100\n", passedTests);
  printf("~~~~~End random testing of adventurer~~~~~\n");

}



//end randomtestadventurer.c
