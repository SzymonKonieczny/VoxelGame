#include <iostream>

#include "Game/Game.h"

int main()
{

	std::cout << "Hello swiat xd\n";
	Game  game;
	game.Init();

	game.Start();



	Renderer::Shutdown();
	return 0;
}