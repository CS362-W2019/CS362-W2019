#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){

        struct gameState state;
        int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        printf("------------------  Testing Function: fullDeckCount ----------------\n");

        // checking to see if the function will run without initializing the game
        if(!fullDeckCount(0, 0, &state))
        	printf("fullDeckCount PASSED initialize test \n");
        else
                printf("fullDeckCount FAILED initialize test \n");


	// initialize a passing state of the game
	initializeGame(MAX_PLAYERS, k, 5, &state); 
       
	if(fullDeckCount(0, 4, &state))
                printf("fullDeckCount PASSED initialize test \n");
        else
                printf("fullDeckCount FAILED initialize test \n");
   
	// pass bad player input 
	if(!fullDeckCount(-1, 4, &state))
                printf("fullDeckCount PASSED player input test \n");
        else
                printf("fullDeckCount FAILED player input test \n");

        if(!fullDeckCount(4, 4, &state))
                printf("fullDeckCount PASSED player input test \n");
        else
                printf("fullDeckCount FAILED player input test \n");


	// pass bad card input
        if(!fullDeckCount(0, -1, &state))
                printf("fullDeckCount PASSED card input test \n");
        else
                printf("fullDeckCount FAILED card input test \n");

        if(!fullDeckCount(0, 50, &state))
                printf("fullDeckCount PASSED card input test \n");
        else
                printf("fullDeckCount FAILED card input test \n");
}
