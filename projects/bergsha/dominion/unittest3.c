#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define assertTrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

// supplyCount unit test
void unittest3()
{
	// initialize game
	struct gameState* testG = newGame();
	assert(initializeGame(2, kingdomCards, 1234, testG) == 0);

	// test supplyCount function for every card in game
	for (int i=curse; i<=treasure_map; i++)
	{
		assertTrue(testG->supplyCount[i] == supplyCount(i, testG))
	}
}

int main(int argc, char *argv[])
{
    unittest3();
    return 0;
}
