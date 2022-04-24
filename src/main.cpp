// random
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// headers
#include "game.h"

int main()
{
    srand (time(NULL));
    Game game{800, 800};
    game.renderLoop();
	return 0;
}