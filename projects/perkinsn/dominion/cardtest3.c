#include <stdio.h>
#include "test_helpers.h"
#include "dominion.h"

int main()
/*
test card great hall

http://wiki.dominionstrategy.com/index.php/Great_Hall

+1 Card
+1 Action

*/
{
    printf("Testing card: Great Hall\n\n");

    struct gameState state;

    int hand[] = {great_hall, -1};
    int deck[] = {village, village, village, village, -1};
    int discard[] = {-1};

    initGameState(2, &state);

    addCards(0, hand, deck, discard, &state);

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed Great Hall.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 3); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.playedCardCount == 1); 
    asserttrue(state.numActions == 1);

    printf("\ngreat hall tests done.\n\n");
}
