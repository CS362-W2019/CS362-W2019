#include "cards.h"
#include "dominion_helpers.h"

#include <stdio.h>

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

int playFeast(struct gameState* state, int choice)
{
    int currentPlayer = state->whoseTurn;
    int temphand[MAX_HAND];

    //gain card with cost up to 5
    //Backup hand
    for (int i = 0; i <= state->handCount[currentPlayer]; i++){
        temphand[i] = state->hand[currentPlayer][i];//Backup card
        state->hand[currentPlayer][i] = -1;//Set to nothing
    }
    //Backup hand

    //Update Coins for Buy
    updateCoins(currentPlayer, state, 5);
    int x = 1; //Condition to loop on

    while(x == 1) {//Buy one card
        if (supplyCount(choice, state) <= 0){
            if (DEBUG) {
                printf("None of that card left, sorry!\n");
                printf("Cards Left: %d\n", supplyCount(choice, state));
            }
        }
        else if (state->coins < getCost(choice)){
            printf("That card is too expensive!\n");

            if (DEBUG){
                printf("Coins: %d < %d\n", state->coins, getCost(choice));
            }
        }
	    else{

            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }

            gainCard(choice, state, 0, currentPlayer);//Gain the card
            x = 0;//No more buying cards

            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }

	    }
    }     

    //Reset Hand
    for (int i = 0; i <= state->handCount[currentPlayer]; i++){
        state->hand[currentPlayer][i] = temphand[i];
        temphand[i] = -1;
    }
    //Reset Hand
            
    return 0;
}

int playMine(struct gameState* state, int handPos, int choice1, int choice2) {
    int currentPlayer = state->whoseTurn;

    int j = state->hand[currentPlayer][choice1];  //store card we will trash

    if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	{
	  return -1;
	}
		
    if (choice2 > treasure_map || choice2 < curse)
	{
	  return -1;
	}

    if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
	{
	  return -1;
	}

    gainCard(choice2, state, 2, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //discard trashed card
    for (int i = 0; i < state->handCount[currentPlayer]; i++)
	{
	    if (state->hand[currentPlayer][i] == j)
	    {
	      discardCard(i, currentPlayer, state, 0);			
	      break;
	    }
	}
			
    return 0;
}

int playRemodel(struct gameState* state, int handPos, int choice1, int choice2)
{
    int currentPlayer = state->whoseTurn;

    int j = state->hand[currentPlayer][choice1];  //store card we will trash

    if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
    {
        return -1;
    }

    gainCard(choice2, state, 0, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //discard trashed card
    for (int i = 0; i < state->handCount[currentPlayer]; i++)
	{
	  if (state->hand[currentPlayer][i] == j)
        {
            discardCard(i, currentPlayer, state, 0);			
            break;
        }
	}

    return 0;
}

int playGreatHall(struct gameState* state, int handPos)
{
    int currentPlayer = state->whoseTurn;

    //+1 Card
    drawCard(currentPlayer, state);
        
    //+1 Actions
    state->numActions++;
        
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}

int playGardens(struct gameState* state)
{
    return -1;
}

int playVillage(struct gameState* state, int handPos)
{
    int currentPlayer = state->whoseTurn;
    //+1 Card
    drawCard(currentPlayer, state);
        
    //+2 Actions
    state->numActions = state->numActions + 2;
        
    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}