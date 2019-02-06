#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include "interface.h"

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
    // Test getCost()

    // Initialization and setup
    char msgString[50];
    int costArray[] = {CURSE_COST, ESTATE_COST, DUCHY_COST, PROVINCE_COST, COPPER_COST, SILVER_COST, GOLD_COST, ADVENTURER_COST, COUNCIL_ROOM_COST,
			FEAST_COST, GARDEN_COST, MINE_COST, REMODEL_COST, SMITHY_COST, VILLAGE_COST, BARON_COST, GREAT_HALL_COST, MINION_COST,
			STEWARD_COST, TRIBUTE_COST, AMBASSADOR_COST, CUTPURSE_COST, EMBARGO_COST, OUTPOST_COST, SALVAGER_COST, SEA_HAG_COST, TREASURE_MAP_COST};

    printf("TESTING getCost():\n----------\n");

    // Compare cost constant to cost retreived by getCost() for each card
    for (int i=curse; i<=treasure_map; i++) {
        sprintf(msgString, "getCost(): Card %i has correct value.", i);
        assertEquals(getCost(i), costArray[i], msgString);
    }

    printf("----------\n");

    return 0;
}
