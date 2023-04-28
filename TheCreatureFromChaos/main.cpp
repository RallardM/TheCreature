#include <iostream>
#include <string>

#include "Utils.h"
#include "GameText.h"
#include "InputManager.h"

int main()
{
	// Create a Utils object and set the console size.
	Utils* utils = nullptr;
	utils->SetConsolesize();
	utils->SetCenterConsolePosition();

	InputManager inputManager;

	bool gameRunning = true;
	while (gameRunning)
	{
		// Process user input
		if (inputManager.HasInput()) 
		{
			std::cout << inputManager.GetInput();
			//InputData inputData = inputManager.GetInput();
			//ProcessInput(inputData);
		}

		// Create a GameText object and call the Introduction of the game.
		//GameText gameText;
		//gameText.Introduction(utils);
		
	}

	return 0;
}

