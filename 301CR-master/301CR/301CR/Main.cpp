#include "GameEngine.h"

int main()
{


	GameEngine gameEngine;

	gameEngine.Start();
	 

	while (gameEngine.isRunning == true)
	{
		gameEngine.Update();
	}

	return 0;
}
