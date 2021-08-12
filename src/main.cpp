#include "Game.hpp"

int main()
{
	clearLog();
	srand(time(NULL));

	Game game;
	game.run();

	return 0;
}
