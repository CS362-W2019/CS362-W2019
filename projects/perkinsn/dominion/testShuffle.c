#include "dominion.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main () {
  printf("Starting testShuffle\n");

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  struct gameState G;
  struct gameState G2;

  // Initialize G.
  initializeGame(2, k, -1, &G);

  memcpy (&G2, &G, sizeof(struct gameState));

  int ret = shuffle(0,&G);

  if (G.deckCount[0] > 0) {
    assert (ret != -1);
    
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), compare);
    qsort ((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);    
  } else
    assert (ret == -1);

  assert(memcmp(&G, &G2, sizeof(struct gameState)) == 0);

  printf("PASS\n");

  return 0;
}
