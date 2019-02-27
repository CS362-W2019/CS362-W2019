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
test card smithy

http://wiki.dominionstrategy.com/index.php/Smithy

You draw 3 cards.

playSmithy(&state, handPos)

Important calls:
state->whoseTurn;
drawCard(currentPlayer, state);
discardCard(handPost, currentPlayer, state, 0);
*/
{
    srand(time(NULL));

    printf("Testing card: smithy\n\n");

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
        int smithyIndex = -1;

        for (int i = 0; i < state.handCount[player]; ++i)
        {
            if (state.hand[player][i] == smithy) {
                smithyIndex = i;
                break;
            }
        }

        if (smithyIndex == -1) {
            // smithy not in hand, cannot be played
            continue;
        }

        // smithy was found!
        int numDrawnCards   = MIN(3, state.deckCount[player]);
        int handCountBefore = state.handCount[player];
        int deckCountBefore = state.deckCount[player];
        int discardCountBefore = state.discardCount[player];
        int playedCardCountBefore = state.playedCardCount;
        int actionsBefore   = state.numActions; 

        // printf("numDrawnCards: %d\n", numDrawnCards);
        // debugGameState(player, &state);
        playCard(smithyIndex, -1, -1, -1, &state);
        // debugGameState(player, &state);

        assert_true_with_state(player, state, state.deckCount[player] == deckCountBefore - numDrawnCards);
        assert_true_with_state(player, state, state.handCount[player] == handCountBefore + numDrawnCards - 1);
        assert_true_with_state(player, state, state.discardCount[player] == discardCountBefore);
        assert_true_with_state(player, state, state.playedCardCount == playedCardCountBefore + 1);
        assert_true_with_state(player, state, state.numActions == actionsBefore - 1);
    }

    printf("\nsmithy tests done.\n\n");
}
