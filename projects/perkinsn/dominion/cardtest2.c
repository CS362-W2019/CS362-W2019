#include <stdio.h>
#include "test_helpers.h"
#include "dominion.h"

int main()
/*
test card adventurer

Reveal cards from your deck until you reveal 2 Treasure cards. 
Put those Treasure cards into your hand and discard the other revealed cards.
*/
{
    printf("Testing card: adventurer\n\n");
    printf("Test with normal usage.\n");
    struct gameState state;

    int hand[] = {adventurer, -1};
    int deck[] = {village, village, silver, gold, village, village, -1};
    int discard[] = {-1};

    initGameState(2, &state);

    addCards(0, hand, deck, discard, &state);

    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 6); 
    asserttrue(state.discardCount[0] == 0);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed adventurer.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 2);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 2);
    asserttrue(state.numActions == 0);
    
    printf("\nTest with shuffle.\n");

    int hand1[] = {adventurer, -1};
    int deck1[] = {village, village, copper, village, village, -1};
    int discard1[] = {gold, -1};

    initGameState(2, &state);

    addCards(0, hand1, deck1, discard1, &state);

    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 5); 
    asserttrue(state.discardCount[0] == 1);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed adventurer.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 2);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 2);
    asserttrue(state.numActions == 0);

    printf("\nTest without enough treasure.\n");

    int hand2[] = {adventurer, -1};
    int deck2[] = {village, village, village, village, -1};
    int discard2[] = {gold, -1};

    initGameState(2, &state);

    addCards(0, hand2, deck2, discard2, &state);

    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 1);
    asserttrue(state.numActions == 1);

    playCard(0, -1, -1, -1, &state);
    printf("\nPlayed adventurer.\n\n");

    debugGameState(0, &state);
    asserttrue(state.handCount[0] == 1);
    asserttrue(state.deckCount[0] == 4); 
    asserttrue(state.discardCount[0] == 2);
    asserttrue(state.numActions == 0);

    printf("\nadventurer tests done.\n\n");
}
