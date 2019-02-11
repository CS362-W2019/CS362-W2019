#include <stdio.h>
#include "test_helpers.h"
#include "dominion.h"

int main()
/*
test card village

http://wiki.dominionstrategy.com/index.php/Village

+1 Card
+2 Actions

*/
{
    printf("Testing card: Village\n\n");

    struct gameState state;

    int hand[] = {village, -1};
    int deck[] = {village, village, great_hall, -1};
    int discard[] = {-1};

    initGameState(2, &state);

    addCards(0, hand, deck, discard, &state);

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 3); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed Village.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 2); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.playedCardCount == 1); 
    asserttrue(state.numActions == 2);

    printf("\nVillage tests done.\n\n");
}
