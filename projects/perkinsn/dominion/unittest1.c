#include "test_helpers.h"
#include "dominion.h"

#define print(test) printf("Comparing %d and %d, expecting %d\n", test.x,test.y,test.expected);

typedef struct {
    int x;
    int y;
    int expected;
} test_case;

int main()
{
    printf("Testing compare()\n\n");

    test_case tests[] = {
        { 0, 0, 0 }, 
        { 1, 0, 1 },
        { 0, 1, -1 },
        { -1, 0, -1 },
        { 0, -1, 1 }, 
        { INT_MAX, INT_MIN, 1 },
        { INT_MIN, INT_MAX, -1 },
        { -1, 1, -1 },
        { 1, -1, 1 },
        { INT_MAX, 1, 1 },
        { INT_MIN, -1, -1 },
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; ++i) {
        test_case test = tests[i];
        print(test);
        asserttrue(compare( (void*) &test.x, (void*) &test.y ) == test.expected);
        printf("\n");
    }
    printf("Tests for compare() done.\n\n");
}