#include "test_helpers.h"
#include "dominion.h"

#include <string.h>

int getCost(int cardNumber);

typedef struct {
    char* name;
    int card;
    int expected;
} test_case;

int main()
{   
    printf("Testing getCost()\n\n");

    // verified costs on http://wiki.dominionstrategy.com/index.php/List_of_cards
    // verified all cards listed in dominion.h are accounted for
    test_case tests[] = {
        {"curse", curse, 0},
        {"estate", estate, 2},
        {"duchy", duchy, 5},
        {"province", province, 8},
        {"copper", copper, 0},
        {"silver", silver, 3},
        {"gold", gold, 6},
        {"adventurer", adventurer, 6},
        {"council_room", council_room, 5},
        {"feast", feast, 4},
        {"gardens", gardens, 4},
        {"mine", mine, 5},
        {"remodel", remodel, 4},
        {"smithy", smithy, 4},
        {"village", village, 3},
        {"baron", baron, 4},
        {"great_hall", great_hall, 3},
        {"minion", minion, 5},
        {"steward", steward, 3},
        {"tribute", tribute, 5},
        {"ambassador", ambassador, 3},
        {"cutpurse", cutpurse, 4},
        {"embargo", embargo, 2},
        {"outpost", outpost, 5},
        {"salvager", salvager, 4},
        {"seahag", sea_hag, 4},
        {"treasure_map", treasure_map, 4},
        {"invalid_card", INT_MAX, -1},
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; ++i) {
        test_case test = tests[i];

        int actual = getCost(test.card);

        printf("Name: %s, Actual: %d, Expected: %d\n", test.name, actual, test.expected);
        asserttrue(actual == test.expected);
        printf("\n");
    }
    printf("Tests for getCost() done.\n\n");
}
