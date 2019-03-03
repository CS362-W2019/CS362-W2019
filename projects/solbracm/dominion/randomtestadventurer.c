/* Random tests adventurer card */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"



int main(){
        printf("----------------------- Random Testing: Adventurer Card --------------\n");

        srand(time(NULL));

        int randomTestNumber = 0;
        int draw2Cards = 0;
        int firstCard = 0;
        int secondCard = 0;

        int k[10]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        while (randomTestNumber < 2000)
        {
                int players = (rand() % MAX_PLAYERS-1)+2;
                struct gameState state;

                initializeGame(players, k, rand(), &state);

                int player = rand() % players;

                int bonus = -1;
                int choice1 = -1;
                int choice2 = -1;
                int choice3 = -1;
                int handPos = rand() % MAX_HAND;

                struct gameState orig;
                memcpy(&orig, &state, sizeof(struct gameState));

                cardEffect(7, choice1, choice2, choice3, &state, handPos, &bonus);

                if(state.handCount[player] != orig.handCount[player] + 2)
                {
            		printf("Player %d, handPos %d, Test Failed Draw 2 Cards.\n", player, handPos);
			draw2Cards++;
        	}

        	int firstCardD = state.hand[player][state.handCount[player] - 1];
        	if(firstCardD != copper && firstCardD != silver && firstCardD != gold)
		{
            		printf("Player %d, handPos %d, Test Failed Card 1 is not money.\n", player, handPos);
			firstCard++;        	
		}	

        	int secondCardD = state.hand[player][state.handCount[player] - 2];
        	if(secondCardD != copper && secondCardD != silver && secondCardD != gold)
		{
            		printf("Player %d, handPos %d, Test Failed Card 2 is not money.\n", player, handPos);
			secondCard++;        	
		}
    	
		randomTestNumber++;
	}	

	printf("Number of failed Draw 2 Cards Test: %d\nNumber of failed Card 1 not money: %d\nNumber of failed Card2 not money: %d\n", draw2Cards, firstCard, secondCard); 		

	return(0);
}

