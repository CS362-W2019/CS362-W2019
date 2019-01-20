#include "cards.h"
#include "dominion_helpers.h"

int playAdventurer(struct gameState* state) {
    int drawntreasure = 0;
    int currentPlayer = state->whoseTurn;
    int cardDrawn;
    int temphand[MAX_HAND];
    int numCardsDrawn = 0;

    while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            drawntreasure++;
        }
        else
        {
            temphand[numCardsDrawn]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            numCardsDrawn++;
        }
    }

    while(numCardsDrawn-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[numCardsDrawn-1]; // discard all cards in play that have been drawn
        numCardsDrawn=numCardsDrawn-1;
    }

    return 0;
}

int playSmithy(struct gameState* state, int handPos)
{
    int currentPlayer = state->whoseTurn;

    //+3 Cards
    for (int i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
    //discard card from hands
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

int playCouncilRoom(struct gameState* state, int handPos)
{
    int currentPlayer = state->whoseTurn;

    //+4 Cards
    for (int i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
    //+1 Buy
    state->numBuys++;
        
    //Each other player draws a card
    for (int i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}
			
    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);
        
    return 0;
}