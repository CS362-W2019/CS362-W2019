/*      Village Card Test        */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){

       struct gameState state;
       int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        printf("------------------  Testing Card: Village Card ----------------\n");

        initializeGame(MAX_PLAYERS, k, 5, &state);
	int coin_bonus=0;	

	//make sure the number of actions change and number of cards in hand doesn't change 
        int i = state.numActions;
        int j = state.handCount[0];

	cardEffect(14, -1, -1, -1, &state, 0, &coin_bonus);
	
	if(i + 2 == state.numActions)
		printf("Village card PASSED actions test\n");
	else
		printf("Village card FAILED actions test\n");

	if(j == state.handCount[0])
                printf("Village card PASSED number cards test\n");
        else
                printf("Village card FAILED number cards test\n");
  	

	return(0);
}
