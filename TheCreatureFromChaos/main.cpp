#include <iostream>
#include <string>

#include "Utils.h"
#include "GameTextManager.h"
#include "UserInputManager.h"
#include "GameChoicesMenu.h"
#include "UserScenesManager.h"

int main()
{
	// Create a Utils object and set the console size.
	Utils* utils = nullptr;
	utils->SetConsolesize();
	utils->SetCenterConsolePosition();

	UserInputManager inputManager{};
	E_UserInput userInput = inputManager.GetInput();

	// Initialize the UserScenesManager object.
	UserScenesManager sceneManager;

	bool gameRunning = true;
	while (gameRunning)
	{
		// Process user input
		if (inputManager.HasInput()) 
		{
			//std::cout << inputManager.GetInput();
			//InputData inputData = inputManager.GetInput();
			//ProcessInput(inputData);
			userInput = inputManager.GetInput();
		}

		// Create a GameText object and call the Introduction of the game.
		GameTextManager gameText;
		gameText.PrintLinesFromScene(sceneManager.GetPlayerCurrentScene());

		GameChoicesMenu manageMenu;
		manageMenu.Render(userInput);

		// Clear the console.
		system("cls");
	}

	return 0;
}

