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
  int testFail = 0;
  int passedTests = 0;
  for (i = 0; i < 100; i++){
    testFail = 0;
    randPlayer = rand() % 3 + 2;
    gameSeed = rand() % 1000;
    //printf("random player number: %d\n", randPlayer);
    //printf("random seed number: %d\n", gameSeed);
    memset(&myState, 0, sizeof(myState));
    memset(&myState2, 0, sizeof(myState));
    initializeGame(randPlayer, k, gameSeed, &myState);
    //copy game state for testing
    memcpy(&myState2, &myState, sizeof(struct gameState));
    //printf("villiageEffec on random game state: ");
    result1 = villageEffect(&myState2, myHandPos);
    if (result1 != 0){
      printf("Test 1: return villiageEffect: FAILED\n");
      printf("random player number: %d\n", randPlayer);
      printf("random seed number: %d\n", gameSeed);
      testFail = 1;
    }

    //test drawing a card
    //hand - difference should be zero, 1 card drawn & 1 card discarded
    int currentPlayer = whoseTurn(&myState2);
    int result2 = myState.handCount[currentPlayer];
    int result3 = myState2.handCount[currentPlayer];
    //printf("Test 2 - num cards in hand: ");
    if (result3 != result2){
      printf("Test 2: num cards in hand: FAILED\n");
      printf("random player number: %d\n", randPlayer);
      printf("random seed number: %d\n", gameSeed);
      testFail = 1;
    }

    //discard pile
    int result4 = myState.discardCount[currentPlayer];
    int result5 = myState2.discardCount[currentPlayer];
    //printf("Test 3 - num cards in discard pile: ");
    if ((result5 - result4) != 1){
      printf("Test 3: discard pile: FAILED");
      printf("random player number: %d\n", randPlayer);
      printf("random seed number: %d\n", gameSeed);
      testFail = 1;
    }

    //deck
    int result6 = myState.deckCount[currentPlayer];
    int result7 = myState2.deckCount[currentPlayer];
    //printf("Test 4 - num cards in deck: ");
    if ((result7 - result6) != -1){
      printf("Test 4: num cards in deck: FAILED\n");
      printf("random player number: %d\n", randPlayer);
      printf("random seed number: %d\n", gameSeed);
      testFail = 1;
    }


    //if all tests passed, add to total passed
    if (testFail == 0){
      passedTests += 1;
    }
  }


//if tests pass, we dont want to print anything but number of
//tests passed
  printf("Total tests passed: %d out of 100\n", passedTests);





}

//end randomtestcard1.c
