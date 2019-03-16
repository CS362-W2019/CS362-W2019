#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){

        struct gameState state;
        int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        printf("------------------  Testing Function: isGameOver ----------------\n");

        // checking to see if the function will run without initializing the game
        if(isGameOver(&state))
        	printf("isGameOver PASSED initialize test \n");
         else
                printf("isGameOver FAILED initialize test \n");
        
        
        // initialize game and set province to 0
        initializeGame(MAX_PLAYERS, k, 5, &state);
        
	state.supplyCount[province] = 0;

	if(isGameOver(&state))
                printf("isGameOver PASSED province test \n");
        else
                printf("isGameOver FAILED province test \n");

	// set province to -1 to check outside bounds

	state.supplyCount[province] = -1;

        if(!isGameOver(&state))
                printf("isGameOver PASSED province test \n");
        else
                printf("isGameOver FAILED province test \n");

	// set province to 1 to check inside bounds

	state.supplyCount[province] = 1;
	
	if(!isGameOver(&state))
                printf("isGameOver PASSED province test \n");
        else
                printf("isGameOver FAILED province test \n");

	state.supplyCount[mine] = 0;

        if(!isGameOver(&state))
                printf("isGameOver PASSED supply piles test \n");
        else
                printf("isGameOver FAILED supply piles test \n");

        state.supplyCount[copper] = 0;

        if(!isGameOver(&state))
                printf("isGameOver PASSED supply piles test \n");
        else
                printf("isGameOver FAILED supply piles test \n");

        state.supplyCount[smithy] = 0;

        if(isGameOver(&state))
                printf("isGameOver PASSED supply piles test \n");
        else
                printf("isGameOver FAILED supply piles test \n");

        state.supplyCount[curse] = 0;

        if(isGameOver(&state))
                printf("isGameOver PASSED supply piles test \n");
        else
                printf("isGameOver FAILED supply piles test \n");

}
