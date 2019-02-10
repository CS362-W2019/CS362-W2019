#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include "rngs.h"

void testKingdomCards()
{
    int i;

    // 0, 7-26 are kingdom cards
    // 1-3 are victory cards, 4-6 are treasure cards
    // test standard game with valid CARD enums
    int set1[] = {0, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int *deck1 = kingdomCards(0, 7, 8, 9, 10, 11, 12, 13, 14, 15); // all valid cards
    if (deck1 == NULL)
    {
        printf("FAIL --- kingdomCards() returned null for deck 1\n");
    }
    else 
    {
        for (i = 0; i < 10; i++)
        {
            if (set1[i] != deck1[i])
            {
                printf("FAIL --- kingdomCards() failed to add card %d from set 1\n", i);
            }
        }
    }
    int set2[] = {16, 17, 18, 19, 20, 21, 22, 24, 25, 26};
    int *deck2 = kingdomCards(16, 17, 18, 19, 20, 21, 22, 24, 25, 26); // all valid cards
    if (deck2 == NULL)
    {
        printf("FAIL --- kingdomCards() returned null for deck 2\n");
    }
     else 
    {
        for (i = 0; i < 10; i++)
        {
            if (set2[i] != deck2[i])
            {
                printf("FAIL --- kingdomCards() failed to add card %d from set 2\n", i);
            }
        }
    }
    int set3[] = {1, 2, 3, 4, 5, 6, 7, 8, -1, 30};
    int *deck3 = kingdomCards(1, 2, 3, 4, 5, 6, 7, 8, -1, 30); // 1-6, -1, 30 shouldn't be pick-able
    if (deck3 == NULL)
    {
        printf("FAIL --- kingdomCards() returned null for deck 3\n");
    }
     else 
    {
        for (i = 0; i < 10; i++)
        {
            if (set3[i] != deck3[i])
            {
                printf("FAIL --- kingdomCards() failed to add card %d from set 3\n", i);
            }
            if (set3[i] < gold && set3[i] > curse) // shouldn't be pickable
            {
                printf("FAIL --- kingdomCards() added a non-kingdom card: %d\n", set3[i]);
            }
            else if (set3[i] > treasure_map || set3[i] < curse) // non-existent card
            {
                printf("FAIL --- kingdomCards() added a non-existent card: %d\n", set3[i]);
            }
        }
    }
    // free up the malloc'd memory
    free(deck1);
    free(deck2);
    free(deck3);
}

int main()
{
    srand(time(NULL));
    testKingdomCards();
    return 0;
}
