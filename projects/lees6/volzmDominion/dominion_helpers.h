#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
int smithyFunc(int handPos, int player, struct gameState *state);
int adventurerFunc(int handPos, int player, struct gameState *state, int drawntreasure, int *temphand, int z);
int councilroomFunc(int handPos, int player, struct gameState *state);
int villageFunc(int handPos, int player, struct gameState *state);
int greathallFunc(int handPos, int player, struct gameState *state);

#endif
