/*************************************
Terezie (Tera) Schaller
Assignment 3
Unit tests for dominion.c
**************************************/
/*************************************
cardtest3.c
testing villageEffect function
REFERENCES
Lecture material: https://oregonstate.instructure.com/courses/1706563/files/73152166?module_item_id=18416505
**************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
int main(){
  printf("~~~~~Begining Card Test 3~~~~~\n");
  printf("~~~~~Testing cardEffect(village) function~~~~~\n");
  //initialize a blank game state
  int result;
  int myHandPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int bonus = 0;
  struct gameState myState;
  struct gameState myState2;
  //clear the struct with memset
  memset(&myState, 0, sizeof(myState));
  memset(&myState2, 0, sizeof(myState));

  //need a valid game in progress to call adventurerEffect
  //or else it segfaults
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine,
    cutpurse,sea_hag, tribute, smithy, council_room};
  int seed = 1000;

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &myState);
  //copy game state for testing
  memcpy(&myState2, &myState, sizeof(struct gameState));

  //call villageEffect, should return zero
  /*
  result = villageEffect(&myState, myHandPos);
  printf("Test result: %d\n", result);
  */

  //call cardEffect - village
  result = cardEffect(village, choice1, choice2, choice3, &myState2, myHandPos, &bonus);
  printf("Test 1 - call cardEffect(village): ");
  if (result == 0){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //test drawing a card
  //hand - difference should be zero, 1 card drawn & 1 card discarded
  int currentPlayer = whoseTurn(&myState2);
  int result2 = myState.handCount[currentPlayer];
  int result3 = myState2.handCount[currentPlayer];
  printf("Test 2 - num cards in hand: ");
  if (result3 == result2){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //discard pile
  int result4 = myState.discardCount[currentPlayer];
  int result5 = myState2.discardCount[currentPlayer];
  printf("Test 3 - num cards in discard pile: ");
  if ((result5 - result4) == 1){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //deck
  int result6 = myState.deckCount[currentPlayer];
  int result7 = myState2.deckCount[currentPlayer];
  printf("Test 4 - num cards in deck: ");
  if ((result7 - result6) == -1){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //test other players hand
  int nextPlayer = currentPlayer + 1;
  if (nextPlayer > numPlayers-1){
    nextPlayer = 0;
  }
  int result8 = myState.handCount[nextPlayer];
  int result9 = myState2.handCount[nextPlayer];
  //printf("result4: %d, result5 %d\n", result4, result5);
  printf("Test 5 - other players hand unaffected: ");
  if (result8 == result9){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  //test actions
  int result10 = myState.numActions;
  int result11 = myState2.numActions;
  //printf("result11: %d, result 10: %d\n", result11, result10);
  printf("Test 6 - number of actions: ");
  if ((result11 - result10) == 2){
    printf("PASSED\n");
  } else {
    printf("FAILED\n");
  }

  printf("~~~~~End testing village~~~~~\n");
  printf("~~~~~End Card Test 3~~~~~\n");
  return 0;
}
