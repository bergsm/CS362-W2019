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
	//int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, gardens};

	int handpos, choice1, choice2, choice3, bonus;
	handpos = choice1 = choice2 = choice3 = bonus = 0;

	//int seed = 1234;

	printf("Testing Card: %s\n", TESTCARD);

    // main testing loop
    for (int n=0; n<2000; n++)
    {
        // initialize a game state and player cards
        if (randomizeGame(adventurer, &testG) != 0)
        {
            printf("Randomize unsuccessful\n");
            continue;
        }

        //initializeGame(2, k, seed, &testG);

        printf("Test #%d\n", n);
        int p = whoseTurn(&testG);

        int oldHandCount = numHandCards(&testG);
        int oldDeckCount = testG.deckCount[p];
        int oldDiscardCount = testG.discardCount[p];

        // assert the card did not fail to play
        printf("TEST 0: testing cardEffect returns correctly\n");
        asserttrue(cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus) == 0)

        // store new deck and hand counts
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
