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

// Refactored: this implementation was moved from cardEffect() into its own function.
int adventurerEffect(struct gameState *state, int currentPlayer);

// Refactored: implementation moved from cardEffect() into its own function.
int smithyEffect(int handPos, int currentPlayer, struct gameState *state);

// Refactored: this implementation was moved from cardEffect() into its own function.
int mineEffect(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state);

// Refactored: this implementation was moved from cardEffect() into its own function.
int outpostEffect(int currentPlayer, int handPos, struct gameState *state);

// Refactored: This implementation was moved into its own function.		
int treasure_mapEffect(int currentPlayer, int handPos, struct gameState *state);


#endif
