#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int assertEquals(int a, int b, char* msg)
{   
    if (a==b) {
        printf("PASS: %s\n", msg);
        return 1;
    }
    else {
        printf("FAIL: %s\n", msg);
        return 0;
    }
}

int main()
{
    // Test supplyCount()

    // Initialization and setup
    struct gameState G = {0};

    printf("TESTING supplyCount():\n----------\n");

    // Check that supplyCount() returns correct values
    assertEquals(supplyCount(adventurer, &G), 0, "supplyCount(): Check adventurer pile contains 0 cards.");

    G.supplyCount[adventurer] = 10;
    assertEquals(supplyCount(adventurer, &G), 10, "supplyCount(): Check adventurer pile contains 10 cards.");

    G.supplyCount[adventurer]--;
    assertEquals(supplyCount(adventurer, &G), 9, "supplyCount(): Remove one adventurer card.");

    G.supplyCount[adventurer]++;
    G.supplyCount[adventurer]++;
    assertEquals(supplyCount(adventurer, &G), 11, "supplyCount(): Add two adventurer cards.");

    printf("----------\n");

    return 0;
}
