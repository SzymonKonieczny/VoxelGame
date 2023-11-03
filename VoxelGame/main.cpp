#include <iostream>

#include "Game/Game.h"

int main()
{
	Game  game;
	game.Init();

	game.Start();


	Renderer::Shutdown();
	return 0;
}