//
// Created by noah2017 on 2/10/19.
//

/***************************************************************************
 * Name: myTestSuite
 * Author: Noah Buchen
 * Assignment 3: unit testing
 * Description: Created for OSU postbacc CS362. This testsuite will begin
 * with unit tests of four functions of the dominion.c code, shuffle, drawCard,
 * discardCard, and fullDeckCount. It will also cover four card effects that
 * I refactored and then bugged up in Assignment 2. Code structure includes
 * a custom assert function that will maintain code execution for passing
 * or failing tests.
***************************************************************************/

#include <memory.h>
#include <stdio.h>
#include "myTestSuite.h"
#include "dominion.h"
#include "dominion_helpers.h"



void testDriverDominion(int numPlayers, int testCase){

	struct gameState unmutable;
	struct gameState mutable;
	int testResult;

	int i;

	int start = -1;
	//need more flexibility in card declaration
	int k[10] = {adventurer, gardens, embargo, village, minion, salvager, cutpurse,
				 sea_hag, tribute, smithy};
	//Intialize unmutable gamestate
	initializeGame(numPlayers, k, 30, &unmutable);
	memset(&unmutable, 'z', sizeof(struct gameState));

printf ("Rough guide to locations in structure:\n");
  printf ("0: numPlayers\n");
  printf ("%ld: supplyCount[0]\n", ((long)&(unmutable.supplyCount[0]))-((long)&unmutable));
  printf ("%ld: embargoTokens[0]\n", ((long)&(unmutable.embargoTokens[0]))-((long)&unmutable));
  printf ("%ld: hand[0][0]\n", ((long)&(unmutable.hand[0][0]))-(long)(&unmutable));
  printf ("%ld: deck[0][0]\n", ((long)&(unmutable.deck[0][0]))-(long)(&unmutable));
  printf ("%ld: discard[0][0]\n", ((long)&(unmutable.discard[0][0]))-(long)(&unmutable));
  printf ("%ld: playerCards[0]\n", ((long)&(unmutable.playedCards[0]))-(long)(&unmutable));

  for (int i = 0; i < sizeof(struct gameState); i++) {
    if (((char*)&unmutable)[i] == 'z') {
      if (start == -1) {
	start = i;
      }
    } else{
    if (start != -1) {
	if (start == (i-1)) {
	  printf ("Byte %d uninitialized.\n", start);
	} else {
	  printf ("Bytes %d-%d uninitialized.\n", start, i-1);
	}
	start = -1;
      }
    }
  }

  if (start != -1) {
    if (start == (i-1)) {
      printf ("Byte %d uninitialized.\n", start);
    } else {
      printf ("Bytes %d-%d uninitialized.\n", start, i-1);
    }
  }


}

int main(){

	//Unit testing

	//TODO refactor into reading from function list a.k.a practice function pointers in C
	// https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work/840703#840703
	//test for 2 or 3 players
	for (int numPlayers = 2; numPlayers < 4 ; ++numPlayers) {

		testDriverDominion(numPlayers, SHUFFLE);
		//testDriverDominion(DRAWCARD);
		//testDriverDominion(DISCARDCARD);
		//testDriverDominion(FULLDECKCOUNT);
		//testDriverDominion(SMITHY);
		//testDriverDominion(ADVENTURER);
		//testDriverDominion(EMBARGO);
		//testDriverDominion(SALVAGER);
	}
	return 0;
}