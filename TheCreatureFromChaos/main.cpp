#include <iostream>
#include <string>
//#include <chrono>
#include <thread>
#include <conio.h>

#include "ConsoleHandler.h"
#include "UserInputManager.h"
#include "NarrationManager.h"
#include "MenuManager.h"
#include "DebugMessageSystem.h"
#include "ScenesManager.h"
#include "UserData.h"

int main()
{
	//DEBUG_MSG("#B main.cpp : main() : Enters main function.");

	// Create a Utils object, set the console size and position.
	//DEBUG_MSG("main.cpp : main() : Create a Utils object, set the console size and position.");
	ConsoleHandler* consoleHandler = new ConsoleHandler();
	consoleHandler->SetConsolesize();
	consoleHandler->SetCenterConsolePosition();
	//consoleHandler->DisableConsoleCursor();
	//consoleHandler->DisableConsoleScrolling();
	//consoleHandler->SetIsUserPrompted(false);
	//consoleHandler->ActivateConsoleCursor();

	ScenesManager* scenesManager = new ScenesManager();

	NarrationManager* narrationManager = new NarrationManager(scenesManager);
	scenesManager->SetNarrationManager(narrationManager);

	UserData* userData = new UserData();

	MenuManager* menuManager = new MenuManager(consoleHandler, scenesManager, narrationManager, userData);
	scenesManager->SetMenuManager(menuManager);

	// Print Intro scene.
	narrationManager->PrintLinesFromScene();

	UserInputManager* inputManager = new UserInputManager(consoleHandler, scenesManager, menuManager);
	//menuManager->SetUserInputManager(inputManager);

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
			userInput = inputManager->GetInput();
			inputManager->SetAction(userInput);
		}

		if (menuManager->GetIsMenuCleared())
		{
			DEBUG_MSG("main.cpp : main() : GetIsMenuCleared() PrintMenuFromScene()");
			userInput = E_UserInput::EMPTY;
			menuManager->PrintMenuFromScene(userInput);
			//menuManager->SetIsMenuCleared(false);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Clean up dynamically allocated memory.
	delete consoleHandler;
	delete menuManager;
	delete userData;
	delete inputManager;
	delete narrationManager;
	delete scenesManager;

	return 0;
}
