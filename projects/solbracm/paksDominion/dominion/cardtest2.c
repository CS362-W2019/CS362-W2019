/*      Adventurer Card Test        */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

int main(){

       struct gameState state;
       int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        printf("------------------  Testing Card: Adventurer Card ----------------\n");

        initializeGame(MAX_PLAYERS, k, 5, &state);
        int coin_bonus=0;

        // Check to see if the at least two coins get added 
        
	int i =  state.coins;	
	
        cardEffect(7, -1, -1, -1, &state, 0, &coin_bonus);
	updateCoins(0, &state, 0);
	int j = state.coins;

	if(i+1 < j)
		printf("Adventurer card PASSED treasure test\n");
	else
		printf("Adventurer card FAILED treasure test\n");


	// ensure that the deck shuffles
	

	state.deckCount[0] = 0;


        cardEffect(7, -1, -1, -1, &state, 0, &coin_bonus);


	
	if(state.deckCount[0] > 0)
                printf("Adventurer card PASSED the shuffle test\n");
        else
                printf("Adventurer card FAILED the shuffle test\n");
	

	return(0);       
}
