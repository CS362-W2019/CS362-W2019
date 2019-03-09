#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){

	struct gameState state;
	int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("------------------  Testing Function: numHandCards ----------------\n");

	// checking to see if the function will run without initializing the game
	if(!numHandCards(&state))
		printf("numHandCards PASSED initialize test \n");
	else
		printf("numHandCards FAILED initialize test \n");
	

	//send a game that is initialized but the whoseTurn is outside of bounds
	initializeGame(MAX_PLAYERS, k, 5, &state);

	state.whoseTurn = -1;

	if(!numHandCards(&state))
                printf("numHandCards PASSED outside bounds test \n");
        else
                printf("numHandCards FAILED outside bounds test \n");

	//check for bugs under normal play conditions
	state.whoseTurn = 0;
	int count = 0;
	while(count < 4)
	{
		printf("Number of Cards in hand %d, Player Number %d  ", numHandCards(&state), whoseTurn(&state));

		if(numHandCards(&state)==5)
			printf("numHandCards PASSED normal play test \n");
		else
			printf("numHandCards FAILED normal play test \n");
	
		endTurn(&state);
		count++;
	}
	
}
 
