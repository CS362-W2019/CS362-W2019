#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main () {

  int r;

  int k[10] = {ADVENTURER, COUNCIL_ROOM, FEAST, GARDENS, MINE,
	       REMODEL, SMITHY, VILLAGE, BARON, GREAT_HALL};

  struct gameState G;
  
  r = initializeGame(4, k, 1, &G);

  printf ("initializeGame(4, k, 1, &G) = %d\n", r);
  assert(r == 0);

  r = supplyCount(ADVENTURER, &G);
  printf ("supplyCount(ADVENTURER, &G) = %d\n", r);
  assert(r == 10);
  
  return 0;
}
