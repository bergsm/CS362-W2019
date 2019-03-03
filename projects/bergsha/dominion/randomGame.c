#include "randomGame.h"
//#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isIn(int test, int arr[], int arrSize)
{
    for (int i=0; i<arrSize; i++)
    {
        if (test == arr[i])
            return 1;
    }
    return 0;
}


void initializeKingCards(int TESTCARD, int* kingdomCards)
{
    int kingCardsPool[] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, embargo, sea_hag, tribute, minion, cutpurse};
    int numKingCards = 13;

    //int* k = malloc(10 * sizeof(int));
    if (isIn(TESTCARD, kingCardsPool, numKingCards))
    {
        kingdomCards[0] = TESTCARD;

        for (int i=1; i<10; i++)
        {
            int card = (int)floor(Random() * numKingCards);
            while (card == TESTCARD)
            {
                card = (int)floor(Random() * numKingCards);
            }
            kingdomCards[i] = card;
        }
    }
    else
    {
        for (int i=0; i<10; i++)
        {
            kingdomCards[i] = kingCardsPool[(int)floor(Random() * numKingCards)];
        }
    }
}


int randomizeGame(int TESTCARD, struct gameState *state) {

  int i;
  int j;
  int it;
  //set up random number generator
  int randomSeed = (int)floor(Random() * 2000);
  SelectStream(1);
  PutSeed((long)randomSeed);

  //set number of players
  state->numPlayers = floor(Random() * 2) + 2;
  int numPlayers = state->numPlayers;

  // initialize kingdom cards
  int* kingdomCards = malloc(sizeof(int) * 10);
  initializeKingCards(TESTCARD, kingdomCards);



  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (numPlayers == 2)
    {
      // random number between 5-20
      //state->supplyCount[curse] = 10;
      state->supplyCount[curse] = (int)floor(Random() * 15) + 5;
    }
  else if (numPlayers == 3)
    {
      // random number between 10-30
      //state->supplyCount[curse] = 20;
      state->supplyCount[curse] = (int)floor(Random() * 20) + 10;
    }
  else
    {
      // random number between 20-40
      //state->supplyCount[curse] = 30;
      state->supplyCount[curse] = (int)floor(Random() * 20) + 20;
    }

  //set number of Victory cards
  if (numPlayers == 2)
    {
      // random number between 4-12
      state->supplyCount[estate] = (int)floor(Random() * 8) + 4;
;
      state->supplyCount[duchy] = (int)floor(Random() * 8) + 4;
      state->supplyCount[province] = (int)floor(Random() * 8) + 4;

    }
  else
    {
      // random number between 8-16
      state->supplyCount[estate] = (int)floor(Random() * 8) + 8;
      state->supplyCount[duchy] = (int)floor(Random() * 8) + 8;
      state->supplyCount[province] = (int)floor(Random() * 8) + 8;
    }

  //set number of Treasure cards
  // random number between 40-80 for copper before subtraction
  int cBS = (int)floor(Random() * 40) + 40;

  state->supplyCount[copper] = cBS - (7 * numPlayers);
  // copper - 20
  state->supplyCount[silver] = cBS - 20;
  // silver - 10
  state->supplyCount[gold] = cBS - 10;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
      for (j = 0; j < 10; j++)           		//loop chosen cards
	{
	  if (kingdomCards[j] == i)
	    {
	      //check if card is a 'Victory' Kingdom card
	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
		{
		  if (numPlayers == 2){ 
            // random number between 4-8
		    state->supplyCount[i] = (int)floor(Random() * 4) + 4;
		  }
          // random number between 8-16
		  else{ state->supplyCount[i] = (int)floor(Random() * 8) + 8;
 }
		}
	      else
		{
          // random card between 5-15
		  state->supplyCount[i] = (int)floor(Random() * 10) + 5;
		}
	      break;
	    }
	  else    //card is not in the set choosen for the game
	    {
	      state->supplyCount[i] = -1;
	    }
	}

    }

  ////////////////////////
  //supply intilization complete

  //set player decks
  for (i = 0; i < numPlayers; i++)
    {
      state->deckCount[i] = 0;
      for (j = 0; j < 3; j++)
	{
	  state->deck[i][j] = estate;
	  state->deckCount[i]++;
	}
      for (j = 3; j < 10; j++)
	{
	  state->deck[i][j] = copper;
	  state->deckCount[i]++;		
	}
    }

  //shuffle player decks
  for (i = 0; i < numPlayers; i++)
    {
      if ( shuffle(i, state) < 0 )
	{
	  return -1;
	}
    }

  //draw player hands
  for (i = 0; i < numPlayers; i++)
    {  
      //initialize hand size to zero
      state->handCount[i] = 0;
      state->discardCount[i] = 0;
      //draw 5 cards
      // for (j = 0; j < 5; j++)
      //	{
      //	  drawCard(i, state);
      //	}
    }
  
  //set embargo tokens to 0 for all supply piles
  for (i = 0; i <= treasure_map; i++)
    {
      state->embargoTokens[i] = 0;
    }

  //initialize first player's turn
  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->whoseTurn = 0;
  state->handCount[state->whoseTurn] = 0;
  //int it; move to top

  //Moved draw cards to here, only drawing at the start of a turn
  // start with random num of cards between 5-10
  int startCards = floor(Random() * 5) + 5;
  for (it = 0; it < startCards; it++){
    drawCard(state->whoseTurn, state);
  }

  updateCoins(state->whoseTurn, state, 0);

  return 0;
}


