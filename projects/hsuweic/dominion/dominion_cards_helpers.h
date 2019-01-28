#ifndef _DOMINION_CARDS_HELPERS_H
#define _DOMINION_CARDS_HELPERS_H

#include "dominion.h"

int playAdventurer(struct gameState*, int*, int,  int, int);
int playCouncilRoom(struct gameState*, int, int);
int playFeast(struct gameState*, int*, int, int);
int playGardens();
int playMine(struct gameState*, int, int, int, int);
int playSmithy(struct gameState*, int, int);
int playRemodel(struct gameState*, int, int, int, int);
int playVillage(struct gameState*, int, int);

#endif
