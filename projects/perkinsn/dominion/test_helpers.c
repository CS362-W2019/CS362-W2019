#include "test_helpers.h"
#include "interface.h"

#include <string.h>

void initGameState(int players, struct gameState* state)
{
    memset(state, 0, sizeof(struct gameState));
    state->numPlayers = players;
    state->numActions = 1;
    state->numBuys    = 1;
    state->whoseTurn  = 0;
    state->phase      = 0;
}

void addCards(int player, int* hand, int* deck, int* discard, struct gameState* state)

{
    for (int i = 0; hand[i] != -1; ++i) {
        state->hand[player][i] = hand[i];
        state->handCount[player]++;
    }

    for (int i = 0; discard[i] != -1; ++i) {
        state->discard[player][i] = discard[i];
        state->discardCount[player]++;
    }

    for (int i = 0; deck[i] != -1; ++i) {
        state->deck[player][i] = deck[i];
        state->deckCount[player]++;
    }
}

void debugGameState(int player, struct gameState* state)
{
    printf("numPlayers: %d\n", state->numPlayers);
    printf("whoseTurn: %d\n", state->whoseTurn);
    char phase[20];
    phaseNumToName(state->phase, phase);
    printf("phase: %s\n", phase);
    printf("playedCardCount: %d\n", state->playedCardCount);

    printf("playedCards: ");
    for (int i = 0; i < state->playedCardCount; ++i) {
        char name[20];
        cardNumToName(state->playedCards[i], name);
        printf("%s ", name); 
    }
    printf("\n\n");
    
    if (player > -1) {
        printf("handCount: %d\n", state->handCount[player]);
        printf("Hand: ");
        for (int i = 0; i < state->handCount[player]; ++i) {
            char name[20];
            cardNumToName(state->hand[player][i], name);
            printf("%s ", name); 
        }
        printf("\n");

        printf("deckCount: %d\n", state->deckCount[player]);
        printf("Deck: ");
        for (int i = 0; i < state->deckCount[player]; ++i) {
            char name[20];
            cardNumToName(state->deck[player][i], name);
            printf("%s ", name); 
        }
        printf("\n");

        printf("discardCount: %d\n", state->discardCount[player]);
        printf("Discard: ");
        for (int i = 0; i < state->discardCount[player]; ++i) {
            char name[20];
            cardNumToName(state->deck[player][i], name);
            printf("%s ", name); 
        }
        printf("\n");
    }

    printf("\n");
}
