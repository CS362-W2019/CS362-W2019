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
test card adventurer

http://wiki.dominionstrategy.com/index.php/Adventurer

Reveal cards from your deck until you reveal 2 Treasure cards. 
Put those Treasure cards into your hand and discard the other revealed cards.
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
        int adventurerIndex = -1;

        for (int i = 0; i < state.handCount[player]; ++i)
        {
            if (state.hand[player][i] == adventurer) {
                adventurerIndex = i;
                break;
            }
        }

        if (adventurerIndex == -1) {
            // greatHall not in hand, cannot be played
            continue;
        }

        // adventurer was found
        int playedCardCountBefore = state.playedCardCount;
        int actionsBefore   = state.numActions; 

        int handCopperBefore = countCards(copper, state.hand[player], state.handCount[player]);
        int handSilverBefore = countCards(silver, state.hand[player], state.handCount[player]);
        int handGoldBefore = countCards(gold, state.hand[player], state.handCount[player]);

        int deckCopperBefore = countCards(copper, state.deck[player], state.deckCount[player]);
        int deckSilverBefore = countCards(silver, state.deck[player], state.deckCount[player]);
        int deckGoldBefore = countCards(gold, state.deck[player], state.deckCount[player]);

        int discardCopperBefore = countCards(copper, state.discard[player], state.discardCount[player]);
        int discardSilverBefore = countCards(silver, state.discard[player], state.discardCount[player]);
        int discardGoldBefore = countCards(gold, state.discard[player], state.discardCount[player]);

        // printf("numDrawnCards: %d\n", numDrawnCards);
        // debugGameState(player, &state);
        playCard(adventurerIndex, -1, -1, -1, &state);
        // debugGameState(player, &state);

        int handCopperAfter = countCards(copper, state.hand[player], state.handCount[player]);
        int handSilverAfter = countCards(silver, state.hand[player], state.handCount[player]);
        int handGoldAfter = countCards(gold, state.hand[player], state.handCount[player]);

        int deckCopperAfter = countCards(copper, state.deck[player], state.deckCount[player]);
        int deckSilverAfter = countCards(silver, state.deck[player], state.deckCount[player]);
        int deckGoldAfter = countCards(gold, state.deck[player], state.deckCount[player]);

        int discardCopperAfter = countCards(copper, state.discard[player], state.discardCount[player]);
        int discardSilverAfter = countCards(silver, state.discard[player], state.discardCount[player]);
        int discardGoldAfter = countCards(gold, state.discard[player], state.discardCount[player]); 

        assert_true_with_state(player, state, state.playedCardCount == playedCardCountBefore);
        assert_true_with_state(player, state, state.numActions == actionsBefore - 1);

        assert_true_with_state(player, state, handCopperAfter == handCopperBefore + (deckCopperBefore - deckCopperAfter) + (discardCopperBefore - discardCopperAfter));
        assert_true_with_state(player, state, handSilverAfter == handSilverBefore + (deckSilverBefore - deckSilverAfter) + (discardSilverBefore - discardSilverAfter));
        assert_true_with_state(player, state, handGoldAfter == handGoldBefore + (deckGoldBefore - deckGoldAfter) + (discardGoldBefore - discardGoldAfter));
    }

    printf("\n adventurer done.\n\n");
}
