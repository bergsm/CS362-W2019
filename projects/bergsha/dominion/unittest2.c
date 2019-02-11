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
void unittest2()
{
	// initialize game
	struct gameState* testG = newGame();
	assert(initializeGame(2, kingdomCards, 1234, testG) == 0);

	// test without setting game over conditon
	asserttrue(isGameOver(testG) == 0);

	// set game over condition 1
	int hold = testG->supplyCount[province];
	testG->supplyCount[province] = 0;
	asserttrue(isGameOver(testG) == 1);

	// reset game
	testG->supplyCount[province] = hold;
	assert(isGameOver(testG) == 0);

	for (int i=0; i<23; i++)
	{
		// set game over condition
		int hold[] = {0, 0, 0};
		hold[0] = testG->supplyCount[i];
		testG->supplyCount[i] = 0;
		hold[1] = testG->supplyCount[i+1];
		testG->supplyCount[i+1] = 0;
		hold[2] = testG->supplyCount[i+2];
		testG->supplyCount[i+2] = 0;

		// test game over condition
		asserttrue(isGameOver(testG) == 1);

		// reset game state
		testG->supplyCount[i] = hold[0];
		testG->supplyCount[i+1] = hold[1];
		testG->supplyCount[i+2] = hold[2];
		assert(isGameOver(testG) == 0);
	}

}

int main(int argc, char *argv[])
{
    unittest2();
    return 0;
}
