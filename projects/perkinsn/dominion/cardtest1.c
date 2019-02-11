#include <stdio.h>
#include "test_helpers.h"
#include "dominion.h"

int main()
/*
test card smithy

http://wiki.dominionstrategy.com/index.php/Smithy

You draw 3 cards.

*/
{
    printf("Testing card: smithy\n\n");

    struct gameState state;

    int hand[] = {smithy, -1};
    int deck[] = {village, village, village, village, -1};
    int discard[] = {-1};

    initGameState(2, &state);

    addCards(0, hand, deck, discard, &state);

    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed smithy.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 3);
    asserttrue(state.deckCount[0] == 1); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.playedCardCount == 1); 
    asserttrue(state.numActions == 0);

    printf("\nsmithy tests done.\n\n");
}
