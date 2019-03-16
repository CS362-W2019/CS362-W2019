#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>


int main(){
	struct gameState state;
	int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(MAX_PLAYERS, k, 5, &state);

	printf("------------------  Testing Function: whoseTurn ----------------\n");
	state.whoseTurn = -1;
	
	while(state.whoseTurn < 6)
	{
		// Testing outside the bounds of the game
		if (state.whoseTurn <= 0 || state.whoseTurn >= 4)
		{	
			if(!whoseTurn(&state))
			{
				if(state.whoseTurn == 0)
					printf("whoseTurn failed %d \n", state.whoseTurn);
				else
					printf("whoseTurn passed %d \n", state.whoseTurn);
			}
			else
				printf("whoseTurn failed %d \n", state.whoseTurn);
		}

		// Testing inside the bounds of the game
		if (state.whoseTurn > 0 && state.whoseTurn < 4)
		{		 
			if(whoseTurn(&state))
				printf("whoseTurn passed %d \n", state.whoseTurn);
			else
				printf("whoseTurn failed %d \n", state.whoseTurn);
		}
		
		state.whoseTurn++;
	}
}



