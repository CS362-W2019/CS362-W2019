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
  //printf("Test 1: positive control, call villageEffect: ");
  //timing
  time_t start_t, end_t;
  double diff_t;
  //need a valid game in progress to call adventurerEffect
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
  //result = villageEffect(&myState, myHandPos);

  //call cardEffect instead to make compatible with Annie's Code
  //int myHandPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int bonus = 0;

  //call cardEffect - village
  result = cardEffect(village, choice1, choice2, choice3, &myState, myHandPos, &bonus);
  printf("Test 1 - call cardEffect(village): ");



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
  //repeat 100 times:
  //start game with 2-4 players
  //rand() % 3 + 2
  //seed InitializeGame with 1-1000
  //rand() % 1000
  int i;
  int testFail = 0;
  int passedTests = 0;
  time(&start_t);
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
    //run villiageEffect on second game state, compare states in tests
    //result1 = villageEffect(&myState2, myHandPos);

    //change result1 from adventurerEffect to cardEffect
    result1 = cardEffect(village, choice1, choice2, choice3, &myState2, myHandPos, &bonus);


    if (result1 != 0){
      printf("Test 1: return villiageEffect: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //test drawing a card
    //hand - difference should be zero, 1 card drawn & 1 card discarded
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

    //discard pile
    int result4 = myState.discardCount[currentPlayer];
    int result5 = myState2.discardCount[currentPlayer];
    //printf("Test 3 - num cards in discard pile: ");
    if ((result5 - result4) != 1){
      printf("Test 3: discard pile: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //deck
    int result6 = myState.deckCount[currentPlayer];
    int result7 = myState2.deckCount[currentPlayer];
    //printf("Test 4 - num cards in deck: ");
    if ((result7 - result6) != -1){
      printf("Test 4: num cards in deck: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //test other players hand
    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > numPlayers-1){
      nextPlayer = 0;
    }
    int result8 = myState.handCount[nextPlayer];
    int result9 = myState2.handCount[nextPlayer];
    //printf("result4: %d, result5 %d\n", result4, result5);
    //printf("Test 5: other players hand unaffected: ");
    if (result8 != result9){
      printf("Test 5: other players hand unaffected: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //test actions
    int result10 = myState.numActions;
    int result11 = myState2.numActions;
    //printf("result11: %d, result 10: %d\n", result11, result10);
    //printf("Test 6: number of actions: ");
    if ((result11 - result10) != 2){
      printf("Test 6: number of actions: FAILED - ");
      printf("players: %d, ", randPlayer);
      printf("seed: %d\n", gameSeed);
      testFail = 1;
    }

    //if all tests passed, add to total passed
    if (testFail == 0){
      passedTests += 1;
    }
  }

//if tests pass, we dont want to print anything but number of
//tests passed
  time(&end_t);
  diff_t = difftime(end_t, start_t);
  printf("randomtestcard1.c took %f seconds to execute.\n", diff_t);

  printf("Total tests passed: %d out of 100\n", passedTests);
  printf("~~~~~End Random Testing: village effect~~~~~\n");
}

//end randomtestcard1.c
