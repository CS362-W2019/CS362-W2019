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
    //printf("Test 2 - gained 2 treasure to hand: ");
    if ((result3 - result2) != 2){
      printf("Test 2: gained 2 treasure to hand: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //check that coinage has increased by at least 2
    //printf("Test 3 - treasure to correct coinage: ");
    //printf("FAILED\n");
    //See bug report. This needs to be tested but is nothandled by code at all
    //update this test after refactoring

    //check that deck has decreased
    int result4 = myState.deckCount[currentPlayer];
    int result5 = myState2.deckCount[currentPlayer];
    //printf("Test 4 - deck decreased: ");
    if ((result4 - result5) < 2){
      printf("Test 4: deck decreased: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //check that discard has increased (or stayed same)
    int result6 = myState.discardCount[currentPlayer];
    int result7 = myState2.discardCount[currentPlayer];
    //printf("Test 5 - discard : ");
    if ((result7 - result6) < 0){
      printf("Test 5: discard : FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //test other players hand, discard, deck
    //test other player
    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > numPlayers-1){
      nextPlayer = 0;
    }
    //hand
    int result8 = myState.handCount[nextPlayer];
    int result9 = myState2.handCount[nextPlayer];
    //printf("Test 6 - opponent hand: ");
    if (result8 != result9){
      printf("Test 6: opponent hand: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //discard
    int result10 = myState.discardCount[nextPlayer];
    int result11 = myState2.discardCount[nextPlayer];
    //printf("Test 7 - opponent discard: ");
    if ((result11 != result10)){
      printf("Test 7: opponent discard: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //deck
    int result12 = myState.deckCount[nextPlayer];
    int result13 = myState2.deckCount[nextPlayer];
    //printf("Test 8 - opponent deck: ");
    if (result12 != result13){
      printf("est 8: opponent deck: FAILED - ");
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
