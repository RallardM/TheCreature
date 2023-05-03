#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>

#include "Utils.h"
#include "UserInputManager.h"
#include "NarrationManager.h"
#include "MenuManager.h"
#include "DebugMessageSystem.h"
#include "ScenesManager.h"

int main()
{
	//DEBUG_MSG("#B main.cpp : main() : Enters main function.");

	// Create a Utils object, set the console size and position.
	//DEBUG_MSG("main.cpp : main() : Create a Utils object, set the console size and position.");
	Utils* utils = nullptr;
	utils->SetConsolesize();
	utils->SetCenterConsolePosition();
	utils->DisableConsoleCursor();
	//utils->ActivateConsoleCursor();

	ScenesManager* sceneManager = new ScenesManager();

	NarrationManager* narrationManager = new NarrationManager(sceneManager);
	sceneManager->SetNarrationManager(narrationManager);

	MenuManager* menuManager = new MenuManager(sceneManager, narrationManager);
	sceneManager->SetMenuManager(menuManager);

	// Print Intro scene.
	narrationManager->PrintLinesFromScene();

	UserInputManager* inputManager = new UserInputManager(sceneManager, menuManager);
	//menuManager->SetUserInputManager(inputManager);

	//unsigned short int counter = 0;
	//unsigned short int numLoops = 5;

	//mainClassAccess->SetIsMenuCleared(true);
	//bool oneLoopOFTwo = true;
	E_UserInput userInput = E_UserInput::EMPTY;
	
	//bool isMenuCleared = true;
	bool gameRunning = true;
	//DEBUG_MSG("main.cpp : main() : Enters main loop.");
	while (gameRunning)
	{
		// Process user input
		if (_kbhit())
		{
			inputManager->SetAction(userInput);
		}

		//if (sceneManager->GetIsSceneCleared())
		//{
		//	// Print the scene text.
		//	narrationManager->PrintLinesFromScene();
		//}

		if (menuManager->GetIsMenuCleared())
		{
			DEBUG_MSG("main.cpp : main() : GetIsMenuCleared() PrintMenuFromScene()");
			menuManager->PrintMenuFromScene(userInput);
			menuManager->SetIsMenuCleared(false);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Clean up dynamically allocated memory.
	delete menuManager;
	delete inputManager;
	delete narrationManager;
	delete sceneManager;

	return 0;
}
