#include "test_helpers.h"
#include "dominion.h"

#include <string.h>

#define print(test) printf("Comparing %d and %d, expecting %d\n", test.x,test.y,test.expected);

typedef struct {
    int hand[50];
    int discard[50];
    int deck[50];
    int expected;
} test_case;

int main()
{   
    printf("Testing scoreFor()\n\n");

    test_case tests[] = {
        {
            {curse, estate, duchy, -1},
            {curse, estate, duchy, -1},
            {-1},
            6
        },
        {
            {curse, curse, curse, -1},
            {curse, curse, curse, -1},
            {curse, curse, curse, -1},
            -9
        }, 
        {
            {estate, estate, estate, -1},
            {estate, estate, estate, -1},
            {estate, estate, estate, -1},
            9
        }, 
        {
            {duchy, duchy, duchy, -1},
            {duchy, duchy, duchy, -1},
            {duchy, duchy, duchy, -1},
            27
        },
        {
            {province, province, province, -1},
            {province, province, province, -1},
            {province, province, province, -1},
            54
        },
        {
            {great_hall, great_hall, great_hall, -1},
            {great_hall, great_hall, great_hall, -1},
            {great_hall, great_hall, great_hall, -1},
            9
        }, 
        {
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            {gardens, estate, estate, estate, estate, estate, estate, estate, estate, estate, -1},
            36
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

        printf("Actual: %d, Expected: %d\n", scoreFor(0, &state), test.expected);
        asserttrue(scoreFor(0, &state) == test.expected);
        printf("\n");
    }
    printf("Tests for scoreFor() done.\n\n");
}