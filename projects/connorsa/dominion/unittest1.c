#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

void testGetCost()
{
    int i, j, cost;
    int prices[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    int fringe[] = {-1, -2, -3, INT_MIN, INT_MAX};

    int len = sizeof(prices) / sizeof(prices[0]);

    //  quick check of number of prices vs. CARD enums,
    //  this is duplicate effort, but could help if other tests crash without reporting
    if (len != treasure_map + 1)
    {
        printf("FAIL --- number of cards %d and costs %d does not match\n", treasure_map, len);
    }

    // check that valid range of CARD enums returns correct cost
    for (i = curse, j = 0; i <= treasure_map; i++, j++)
    {
        cost = getCost(i);     // get cost for CARD i
        if (cost != prices[j]) // cost does not match
        {
            printf("FAIL --- card %d cost = %d, expected %d\n", i, cost, prices[j]);
        }
        else if (cost == -1) // if valid card has price == error value
        {
            printf("FAIL --- card %d cost = %d, which is the return value for getCost() error\n", i, cost);
        }
        //printf("Card %d cost %d expected %d\n", i, cost, prices[j]);
    }

    // check 15 above the range of valid cards in case cards were added
    for (i = treasure_map + 1; i <= treasure_map + 15; i++)
    {
        cost = getCost(i);
        if (cost != -1)
        {
            printf("FAIL --- getCost() returned %d for non-existent card %d\n", cost, i);
        }
    }

    // check a few fringe cases
    for (i = 0; i < sizeof(fringe) / sizeof(fringe[0]); i++)
    {
        cost = getCost(fringe[i]);
        if (cost != -1)
        {
            printf("FAIL --- getCost() returned %d for non-existent card %d\n", cost, i);
        }
    }
}

int main()
{
    srand(time(NULL));
    testGetCost();
    return 0;
}