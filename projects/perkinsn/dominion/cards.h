#ifndef _CARDS_H
#define _CARDS_H

#include "dominion.h"

int playSmithy(struct gameState* state, int handPos);
int playCouncilRoom(struct gameState* state, int handPos);
int playAdventurer(struct gameState* state);
int playFeast(struct gameState* state, int choice);
int playMine(struct gameState* state, int handPos, int choice1, int choice2);
int playRemodel(struct gameState* state, int handPos, int choice1, int choice2);

#endif