#include "test_helpers.h"
#include "interface.h"

#include <string.h>
#include <stdlib.h>

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

void fillDeck(int player, struct gameState* state, int max)
{
    state->deckCount[player] = max;

    for (int i = 0; i < MAX_DECK; ++i)
        state->deck[player][i] = -1;

    for (int i = 0; i < max; ++i)
    {
        state->deck[player][i] = rand() % (LAST_CARD + 1);
    }
}

void fillHand(int player, struct gameState* state, int max)
{
    state->handCount[player] = max;

    for (int i = 0; i < MAX_HAND; ++i)
        state->hand[player][i] = -1;

    for (int i = 0; i < max; ++i)
        state->hand[player][i] = rand() % (LAST_CARD + 1);
}

void fillDiscard(int player, struct gameState* state, int max)
{
    state->discardCount[player] = max;

    for (int i = 0; i < MAX_DECK; ++i)
        state->discard[player][i] = -1;

    for (int i = 0; i < max; ++i)
        state->discard[player][i] = rand() % (LAST_CARD);
}

void debugGameState(int player, struct gameState* state)
{
    printf("numPlayers: %d\n", state->numPlayers);
    printf("whoseTurn: %d\n", state->whoseTurn);
    printf("numActions: %d\n", state->numActions);
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

int countCards(int card, int* pile, int size)
{
  int count = 0;
  for (int i = 0; i < size &&  i != -1; ++i)
  {
    if (pile[i] == card)
    {
      ++count;
    }   
  }

  return count;
}
