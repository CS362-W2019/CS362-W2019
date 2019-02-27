#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/param.h>

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
    srand(time(NULL));

    printf("Testing card: great hall\n\n");

    struct gameState state;

    for (int i = 0; i < 1000; ++i)
    {
        memset(&state, 0, sizeof(struct gameState));
        state.numPlayers = 1 + rand() % MAX_PLAYERS;
        state.numActions = 1 + rand();
        state.numBuys    = 1 + rand(); 
        state.whoseTurn  = rand() % MAX_PLAYERS;
        state.phase      = 0;

        for (int player = 0; player < state.numPlayers; ++player)
        {
            int numDeck = 1 + rand() % MAX_DECK;
            int numHand = 1 + rand() % MAX_HAND - 3;
            int numDiscard = 1 + rand() % MAX_DECK - 1;

            fillDeck(player, &state, numDeck);
            fillHand(player, &state, numHand);
            fillDiscard(player, &state, numDiscard);
        }

        int player = state.whoseTurn;
        int greatHallIndex = -1;

        for (int i = 0; i < state.handCount[player]; ++i)
        {
            if (state.hand[player][i] == great_hall) {
                greatHallIndex = i;
                break;
            }
        }

        if (greatHallIndex == -1) {
            // greatHall not in hand, cannot be played
            continue;
        }

        // smithy was found!
        int numDrawnCards   = MIN(1, state.deckCount[player]);
        int handCountBefore = state.handCount[player];
        int deckCountBefore = state.deckCount[player];
        int discardCountBefore = state.discardCount[player];
        int playedCardCountBefore = state.playedCardCount;
        int actionsBefore   = state.numActions; 

        // printf("numDrawnCards: %d\n", numDrawnCards);
        // debugGameState(player, &state);
        playCard(greatHallIndex, -1, -1, -1, &state);
        // debugGameState(player, &state);

        assert_true_with_state(player, state, state.deckCount[player] == deckCountBefore - numDrawnCards);
        assert_true_with_state(player, state, state.handCount[player] == handCountBefore + numDrawnCards - 1);
        assert_true_with_state(player, state, state.discardCount[player] == discardCountBefore);
        assert_true_with_state(player, state, state.playedCardCount == playedCardCountBefore + 1);
        assert_true_with_state(player, state, state.numActions == actionsBefore);
    }

    printf("\n great hall done.\n\n");
}
