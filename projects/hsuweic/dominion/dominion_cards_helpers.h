#ifndef _DOMINION_CARDS_HELPERS_H
#define _DOMINION_CARDS_HELPERS_H

#include "dominion.h"

int playAdventurer(struct gameState*, int*, int,  int, int);
int playCouncilRoom(struct gameState*, int, int);
int playFeast(struct gameState*, int*, int, int);
int playGARDENS();
int playMine(struct gameState*, int, int, int, int);
int playSmithy(struct gameState*, int, int);
int playREMODEL(struct gameState*, int, int, int, int);
int playVILLAGE(struct gameState*, int, int);
int playBaron(struct gameState*, int, int);
int playGreatHall(struct gameState*, int, int);
int playMinion(struct gameState*, int, int, int, int, int);
int playSteward(struct gameState*, int, int, int, int, int);


#endif
