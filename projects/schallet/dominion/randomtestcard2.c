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
  printf("Test 1: positive control, call sea_hag effect: ");
  //need a valid game in progress to call sea_hagEffect
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine,
    cutpurse,sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int result, result1;
  //create and initialize a game state
  struct gameState myState;
  struct gameState myState2;
  memset(&myState, 0, sizeof(myState));
  memset(&myState2, 0, sizeof(myState2));
  initializeGame(numPlayers, k, seed, &myState);

  //call villageEffect, should return zero
  result = sea_hagEffect(&myState);
  //printf("Test result: %d\n", result);
  if (result == 0){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }
  //end posiive control

  //randomized testing

  //randomize Testing
  //randomize # players and seed to initializeGame
  srand(time(0));
  int randPlayer;
  int gameSeed;
  //repeat 100 times:
  //start game with 2-4 players
  //rand() % 3 + 2
  //seed InitializeGame with 1-1000
  //rand() % 1000
  int i;
  int testFail = 0;
  int passedTests = 0;
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
    //run vsea_hagEffect on second game state, compare states in tests
    result1 = sea_hagEffect(&myState2);
    if (result1 != 0){
      printf("Test 1: return sea_hagEffect: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //test drawing a card
    //hand - difference should be zero
    int currentPlayer = whoseTurn(&myState2);
    int result2 = myState.handCount[currentPlayer];
    int result3 = myState2.handCount[currentPlayer];
    //printf("Test 2 - num cards in hand: ");
    if (result3 != result2){
      printf("Test 2: num cards in hand: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //discard pile - should be the same before and after
    int result4 = myState.discardCount[currentPlayer];
    int result5 = myState2.discardCount[currentPlayer];
    //printf("Test 3 - num cards in discard pile: ");
    if ((result5 != result4){
      printf("Test 3: discard pile: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //deck - players deck should be same before and after sea_hag
    int result6 = myState.deckCount[currentPlayer];
    int result7 = myState2.deckCount[currentPlayer];
    //printf("Test 4 - num cards in deck: ");
    if (result7 != result6){
      printf("Test 4: num cards in deck: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }


    //if all tests passed, add to total passed
    if (testFail == 0){
      passedTests += 1;
    }

  } //end of for loop

  printf("Total tests passed: %d out of 100\n", passedTests);
  printf("~~~~~End Random Testing: sea_hag effect~~~~~\n");
}

//end randomtestcard2.c
