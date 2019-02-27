#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>

// used for INT_MIN and INT_MAX
// from https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>

#include "dominion.h"

// macro for quickly testing a bool value
// from https://piazza.com/class/jpu18p346423vs?cid=159
#define asserttrue(bool) if(bool) { printf("TEST SUCCESSFULLY COMPLETED.\n"); } else { printf("TEST FAILED: '" #bool  "' on line %d.\n", __LINE__); };
#define assert_true_with_state(player, state, bool) if(bool) { printf("."); } else { printf("TEST FAILED: '" #bool  "' on line %d.\n", __LINE__); debugGameState(player, &state); };

void initGameState(int players, struct gameState* state);
void addCards(int player, int* hand, int* deck, int* discard, struct gameState* state);
void debugGameState(int player, struct gameState* state);
void fillDeck(int player, struct gameState* state, int max);
void fillHand(int player, struct gameState* state, int max);
void fillDiscard(int player, struct gameState* state, int max);

#endif