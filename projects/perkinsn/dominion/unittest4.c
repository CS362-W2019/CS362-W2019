#include "test_helpers.h"
#include "dominion.h"

#include <string.h>

typedef struct {
    int hand[50];
    int discard[50];
    int deck[50];
    int card;
    int expected;
} test_case;

int main()
{   
    printf("Testing fullDeckCount()\n\n");

    test_case tests[] = {
        {
            {curse, estate, duchy, -1},
            {curse, estate, duchy, -1},
            {-1},
            curse,
            2
        },
        {
            {curse, duchy, -1},
            {curse, estate, duchy, -1},
            {-1},
            estate,
            1
        },
        {
            {curse, duchy, -1},
            {curse, estate, duchy, -1},
            {-1},
            duchy,
            2
        },
        {
            {curse, curse, curse, -1},
            {curse, curse, curse, -1},
            {curse, curse, curse, -1},
            curse,
            9
        }, 
        {
            {estate, estate, estate, -1},
            {estate, estate, estate, -1},
            {estate, estate, estate, -1},
            estate,
            9
        }, 
        {
            {duchy, duchy, duchy, -1},
            {duchy, duchy, duchy, -1},
            {duchy, duchy, duchy, -1},
            duchy,
            9
        },
        {
            {province, province, province, -1},
            {province, province, province, -1},
            {province, province, province, -1},
            province,
            9
        },
        {
            {great_hall, great_hall, great_hall, -1},
            {great_hall, great_hall, great_hall, -1},
            {great_hall, great_hall, great_hall, -1},
            great_hall,
            9
        }, 
        {
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            gardens,
            3
        }, 
        {
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            estate,
            27
        }, 
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; ++i) {
        test_case test = tests[i];

        struct gameState state;
        memset(&state, 0, sizeof(state));

        for (int i = 0; test.hand[i] != -1; ++i) {
            state.hand[0][i] = test.hand[i];
            state.handCount[0]++;
        }

        for (int i = 0; test.discard[i] != -1; ++i) {
            state.discard[0][i] = test.discard[i];
            state.discardCount[0]++;
        }

        for (int i = 0; test.deck[i] != -1; ++i) {
            state.deck[0][i] = test.deck[i];
            state.deckCount[0]++;
        }

        int actual = fullDeckCount(0, test.card, &state);
        printf("Actual: %d, Expected: %d\n", actual, test.expected);
        asserttrue(actual == test.expected);
        printf("\n");
    }
    printf("Tests for fullDeckCount() done.\n\n");
}