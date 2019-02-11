#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define asserttrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

// isGameOver unit test
void unittest4()
{
	// initialize game
	struct gameState* testG = newGame();
	assert(initializeGame(2, kingdomCards, 1234, testG) == 0);

	updateCoins(0, testG, 0);
	int oldCoins = testG->coins;


	// test bonus without changing player hand
	printf("Bonus\n");
	updateCoins(0, testG, 2);
	asserttrue(testG->coins == oldCoins + 2);

	// add copper to player hand and test
	printf("Copper\n");
	testG->hand[0][0] = copper;
	updateCoins(0, testG, 0);
	asserttrue(testG->coins == oldCoins + 1);

	// add silver to player hand and test
	printf("Silver\n");
	testG->hand[0][0] = silver;
	updateCoins(0, testG, 0);
	asserttrue(testG->coins == oldCoins + 2);

	// add gold to player hand and test
	printf("Gold\n");
	testG->hand[0][0] = gold;
	updateCoins(0, testG, 0);
	asserttrue(testG->coins == oldCoins + 3);

}

int main(int argc, char *argv[])
{
    unittest4();
    return 0;
}
