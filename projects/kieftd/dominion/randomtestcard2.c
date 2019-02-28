/*********************************
*  Author: Derk Kieft (kieftd)
*  File: randomtestcard2.c testing Village
*
* 
* Include the following lines in makefile:
*
* randomtestcard2: randomtestcard2.c dominion.o rngs.o
*      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
********************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "village"

int randomGen (int lower, int upper) {
    int result;
    result = (rand() % 
        (upper - lower + 1)) + lower; 
        //printf("Result is: %d ", result); 

    return result;
}


int main() {
    int newCards = 0;
    int discarded = 1;
    //int xtraCoins = 0;
    int shuffledCards = 0;


    int handpos = 0,  bonus = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    //int remove1, remove2;
    int seed = 3000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, gardens, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    /*LOOP TEST PORCESS*/
int x;    
for (x=0; x<10;x++)  {

  /*RESET VARIABLES AS NEEDED*/
    int newCards = 0;
    int discarded = 1;
    //int xtraCoins = 0;
    int shuffledCards = 0;
    //int remove1, remove2;
    int seed = 3000;
    int numPlayers = 2;
    int thisPlayer = 0;  

    /*RANDOMIZE CARD INPUT*/
    handpos = randomGen(0,5); 
    choice1 = randomGen(0,2); 
    choice2 = randomGen(0,2); 
    choice3 = randomGen(0,2); 
    bonus = randomGen(0,3);

    /*RANDOMIZE GAME STATE*/
    G.whoseTurn = randomGen(0,1); 
    G.phase = randomGen(1,3); 
    G.coins = randomGen(0,8); // Use as you see fit! 
    G.numBuys = randomGen(0,5); // Starts at 1 each turn  
    int i;
    for (i=0; i<MAX_PLAYERS; i++) {
        G.handCount[i] = randomGen(1, MAX_HAND);
        
    }
    for (i=0; i<MAX_PLAYERS; i++) {
        G.deckCount[i] = randomGen(9, 30);
    } 
    for (i=0; i<MAX_PLAYERS; i++) {
        G.discardCount[i] = randomGen(1, MAX_HAND); 
    }
    G.playedCardCount = randomGen(1,5); 

	printf("----------------- Test Card is %s ----------------\n", TESTCARD);

	// copy the game state to a test case for later comparison
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
    //ref_village(&G, handpos, &bonus);

    //Set expected changes
    //+1 Card +2 Actions
    newCards = 1;

if (G.numPlayers == testG.numPlayers)  {
    printf("PASS: #Players = %d, expected = %d\n", G.numPlayers, testG.numPlayers);
}
else {
    printf("FAIL: #Players = %d, expected = %d\n", G.numPlayers, testG.numPlayers);
}
 
if (G.whoseTurn == testG.whoseTurn)
    {
    printf("PASS: whoseTurn = %d, expected = %d\n", G.whoseTurn, testG.whoseTurn);
    }
else {
    printf("FAIL: whoseTurn = %d, expected = %d\n", G.whoseTurn, testG.whoseTurn);
}

if (G.phase == testG.phase)
    {
    printf("PASS: phase = %d, expected = %d\n", G.phase, testG.phase);
    }
else {
    printf("FAIL: phase = %d, expected = %d\n", G.phase, testG.phase);
}

if (G.numActions == testG.numActions+1)
    {
    printf("PASS: numActions = %d, expected = %d\n", G.numActions, testG.numActions+1);
    }
else {
    printf("FAIL: numActions = %d, expected = %d\n", G.numActions, testG.numActions+1);
}

if (G.coins == testG.coins)
    {
    printf("PASS:coins = %d, expected = %d\n", G.coins, testG.coins);
    }
else {
    printf("FAIL:coins = %d, expected = %d\n", G.coins, testG.coins);
}
 
if (G.phase == testG.phase)
    {
    printf("PASS: phase = %d, expected = %d\n", G.phase, testG.phase);
    }
else {
    printf("FAIL: phase = %d, expected = %d\n", G.phase, testG.phase);
}

/*G.hand[MAX_PLAYERS][MAX_HAND]; */
 
if (G.handCount[thisPlayer] == testG.handCount[thisPlayer] + newCards - discarded)
    {
    printf("PASS: hand count = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer] + newCards - discarded);
    }
else {
    printf("FAIL: hand count = %d, expected = %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer] + newCards - discarded);
    
}

/*G.deck[MAX_PLAYERS][MAX_DECK]; */

if (G.deckCount[thisPlayer] == testG.deckCount[thisPlayer])
    {
    printf("PASS: deck count = %d, expected = %d\n", G.deckCount[thisPlayer], testG.deckCount[thisPlayer] - newCards + shuffledCards);
    }
else {
    printf("FAIL: deck count = %d, expected = %d\n", G.deckCount[thisPlayer], testG.deckCount[thisPlayer] - newCards + shuffledCards);
    
}

/*G.discard[MAX_PLAYERS][MAX_DECK]; */

if (G.discardCount[thisPlayer] == testG.discardCount[thisPlayer]-1)  //Card is discarded
    {
    printf("PASS: discardCount = %d, expected = %d\n", G.discardCount[thisPlayer],testG.discardCount[thisPlayer]-1);
    }
else {
    printf("FAIL: discardCount = %d, expected = %d\n", G.discardCount[thisPlayer],testG.discardCount[thisPlayer]-1);
}

/*G.playedCards[MAX_DECK]; */

if (G.playedCardCount+1 == testG.playedCardCount)
    {
    printf("PASS: playedCardCount = %d, expected = %d\n", G.playedCardCount+1, testG.playedCardCount);
    }
else {
    printf("FAIL: playedCardCount = %d, expected = %d\n", G.playedCardCount+1, testG.playedCardCount);
}

}
    return 0;
}
