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
#include <time.h>
#include <unistd.h>

int main(){
  printf("~~~~~Begining Card 2 Random Testing~~~~~\n");
  printf("~~~~~Random Testing: sea_hag effect~~~~~\n");
  printf("Test 1: positive control, call sea_hag effect: ");
  //timing
  time_t start_t, end_t;
  double diff_t;
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
  time(&start_t);
  //sleep(3);
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
    if (result5 != result4){
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

    //test other player
    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > numPlayers-1){
      nextPlayer = 0;
    }
    //hand - other player, should be same
    int result8 = myState.handCount[nextPlayer];
    int result9 = myState2.handCount[nextPlayer];
    //printf("Test 5 - opponent hand: ");
    if (result8 != result9){
      printf("Test 5: opponent hand: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //discard - other player, one card discarded
    int result10 = myState.discardCount[nextPlayer];
    int result11 = myState2.discardCount[nextPlayer];
    //printf("Test 6 - opponent discard: ");
    if ((result11 - result10) != 1){
      printf("Test 6: opponent discard: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //deck - other player, stays same (discard, then add curse)
    int result12 = myState.deckCount[nextPlayer];
    int result13 = myState2.deckCount[nextPlayer];
    //printf("Test 7 - opponent deck: ");
    if (result12 != result13){
      printf("Test 7: opponent deck: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //scores
    //current player should be the same
    int result14 = scoreFor(currentPlayer, &myState);
    int result15 = scoreFor(currentPlayer, &myState2);
    //printf("Test 8 - curent player score: ");
    if (result14 != result15){
      printf("Test 8: curent player score: FAILED -");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //opponent should have -1
    int result16 = scoreFor(nextPlayer, &myState);
    int result17 = scoreFor(nextPlayer, &myState2);
    //printf("Test 9 - opponent score: ");
    if ((result17 - result16) != -1){
      printf("Test 9: opponent score: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //if all tests passed, add to total passed
    if (testFail == 0){
      passedTests += 1;
    }

  } //end of for loop
  time(&end_t);
  diff_t = difftime(end_t, start_t);
  printf("randomtestcard2.c took %f seconds to execute.\n", diff_t);

  printf("Total tests passed: %d out of 100\n", passedTests);
  printf("~~~~~End Random Testing: sea_hag effect~~~~~\n");
}

//end randomtestcard2.c
