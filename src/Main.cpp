#include "./Game.h"

int main(int argc, char* args[])
{
	Game game;

	while(game.Running() == true)
	{
		game.Input();
		game.Update();
		game.Render();
	}

	game.Destroy();

	return 0;
}