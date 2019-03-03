#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "randomGame.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define asserttrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

#define TESTCARD "adventurer"

// adventurer card test
void randomtestadventurer()
{
	//struct gameState* testG = newGame();
	struct gameState testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, gardens};

	int handpos, choice1, choice2, choice3, bonus;
	handpos = choice1 = choice2 = choice3 = bonus = 0;

	int seed = 1234;


	printf("Testing Card: %s\n", TESTCARD);

    //TODO change back to a large number
    // main testing loop
    for (int n=0; n<5; n++)
    {
        // initialize a game state and player cards
        if (randomizeGame(adventurer, &testG) != 0)
        {
            printf("Randomize unsuccessful\n");
            continue;
        }

        //initializeGame(2, k, seed, &testG);

        printf("Test #%d\n", n);
        // set values of testG to random (but logical) values
        //for (int i=0; i<sizeof(struct gameState); i++)
        //{
        //    ((char*)&testG)[i] = floor(Random() * 256);
        //}
        //testG.numPlayers = floor(Random() * MAX_PLAYERS);
        //testG.whoseTurn = floor(Random() * testG.numPlayers);
        //int p = whoseTurn(testG);
        // TODO randomize turn
        int p = whoseTurn(&testG);
        //printf("p= %d\n", p);
        //testG->deckCount[p] = floor(Random() * MAX_DECK);
        //testG->discardCount[p] = floor(Random() * MAX_DECK);
        //testG->handCount[p] = floor(Random() * MAX_HAND);

        //testG.deckCount[p] = floor(Random() * MAX_DECK);

        //for (int i=0; i<3; i++)
        //{
        //    for (int card=copper; card<=gold; card++)
        //    {
        //        testG.deck[p][(int)floor(Random()*testG.deckCount[p])] = card;
        //        printf("Card is: %d\n", card);
        //    }
        //}



        //testG.supplyCount[silver] = 3;
        //testG.supplyCount[gold] = 3;

        //Ensure there are enough treasure cards to test adventurer
        //int treasureCt = testG->supplyCount[copper] + testG->supplyCount[silver] + testG->supplyCount[gold];
        //int treasureCt = testG.supplyCount[copper] + testG.supplyCount[silver] + testG.supplyCount[gold];
        //printf("Number of treasure: %d\n", treasureCt);
        //printf("Number of copper: %d\n", testG.supplyCount[copper]);
        //printf("Number of silver: %d\n", testG.supplyCount[silver]);
        //printf("Number of gold: %d\n", testG.supplyCount[gold]);
        //if (treasureCt < 6)
        //{
        //    printf("Not enough treasure to test adventurer in this gameState\n");
        //    continue;
        //}

        // store old deck and hand counts
        //int oldHandCount = numHandCards(testG);
        //int oldDeckCount = testG->deckCount[p];
        //int oldDiscardCount = testG->discardCount[p];

        int oldHandCount = numHandCards(&testG);
        int oldDeckCount = testG.deckCount[p];
        int oldDiscardCount = testG.discardCount[p];

        printf("oHC = %d\n", oldHandCount);
        printf("oDC = %d\n", oldDeckCount);
        printf("oDcC = %d\n", oldDiscardCount);

        // assert the card did not fail to play
        printf("TEST 0: testing cardEffect returns correctly\n");
        asserttrue(cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus) == 0)

        // store new deck and hand counts
        //int newHandCount = numHandCards(testG);
        //int newDeckCount = testG->deckCount[p];
        //int newDiscardCount = testG->discardCount[p];
        int newHandCount = numHandCards(&testG);
        int newDeckCount = testG.deckCount[p];
        int newDiscardCount = testG.discardCount[p];

        // test 1 number of cards in the deck has changed
        printf("TEST 1: testing number of cards in player's hand has changed\n");
        asserttrue(oldHandCount != newHandCount);

        // test 2 number of cards in the player's hand has changed
        printf("TEST 2: testing number of cards in deck has changed\n");
        asserttrue(oldDeckCount != newDeckCount);

        // test 3 number of cards in the discard pile has changed
        printf("TEST 3: testing number of cards in discard pile has changed\n");
        asserttrue(oldDiscardCount != newDiscardCount);

        // test 4 number of cards in the player's hand has increased by 2
        printf("TEST 4: testing number of cards in player's hand has increased by 2\n");
        asserttrue(newHandCount == oldHandCount+2);
    }
}

int main(int argc, char *argv[])
{
    randomtestadventurer();
    return 0;
}
