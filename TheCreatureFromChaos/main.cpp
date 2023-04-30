#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "Utils.h"
#include "ScenesNarrationManager.h"
#include "UserInputManager.h"
#include "ScenesMenuManager.h"
#include "UserScenesManager.h"
#include "DebugMessageSystem.h"
#include "main.h"

int main()
{
	//DEBUG_MSG("¢Bmain.cpp : main() : Enters main function.");

	// Create a Utils object, set the console size and position.
	//DEBUG_MSG("main.cpp : main() : Create a Utils object, set the console size and position.");
	Utils* utils = nullptr;
	utils->SetConsolesize();
	utils->SetCenterConsolePosition();
	//utils->DisableConsoleCursor();
	utils->ActivateConsoleCursor();

	// Initialize the UserInputManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the UserInputManager object.");
	UserInputManager inputManager{};
	//DEBUG_MSG("main.cpp : main() : Get user input.");
	UserInputManager::E_UserInput userInput = inputManager.GetInput();

	// Initialize the MainClass object.
	//DEBUG_MSG("main.cpp : main() : Initialize the MainClass object.");
	MainClass* mainClassAccess  = new MainClass();

	// Initialize the UserScenesManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the UserScenesManager object.");
	UserScenesManager* sceneManager = new UserScenesManager();

	// Initialize the ScenesNarrationManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the ScenesNarrationManager object.");
	//ScenesNarrationManager* textManager = new ScenesNarrationManager(mainClassAcces, sceneManager);
	ScenesNarrationManager* textManager = new ScenesNarrationManager(sceneManager);

	// Initialize the ScenesMenuManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the ScenesMenuManager object.");
	ScenesMenuManager* menuManager = new ScenesMenuManager(mainClassAccess, sceneManager, textManager);

	unsigned short int counter = 0;
	unsigned short int numLoops = 5;

	mainClassAccess->SetIsMenuCleared(true);
	bool oneLoopOFTwo = true;
	bool isSceneCleared = true;
	//bool isMenuCleared = true;
	bool gameRunning = true;
	//DEBUG_MSG("main.cpp : main() : Enters main loop.");
	while (gameRunning)
	{
		// Process user input
		if (inputManager.HasInput()) 
		{
			//std::cout << inputManager.GetInput();
			//InputData inputData = inputManager.GetInput();
			//ProcessInput(inputData);

			// Clear the console.
			//system("cls");
			userInput = inputManager.GetInput();
			utils->ClearConsole();
			//mainClassAcces->SetIsSceneCleared(true);
			isSceneCleared = true;
		}

		//if (mainClassAcces->GetIsSceneCleared())
		if (isSceneCleared)
		{
			// Print the scene text.
			textManager->PrintLinesFromScene();
			//mainClassAcces->SetIsSceneCleared(false);
			isSceneCleared = false;
		}

		if (oneLoopOFTwo)
		{
			for (int i = 0; i < numLoops; i++) 
			{
				if (mainClassAccess->GetIsMenuCleared())
				{
					menuManager->PrintMenuFromScene(userInput, true);
					mainClassAccess->SetIsMenuCleared(false);
				}
			}

			if (!mainClassAccess->GetIsMenuCleared()) 
			{
				std::cout << "\033[1A\033[0K";
				menuManager->SetCurrentSceneMenuText(EMPTY_MENU_TEXT);
				mainClassAccess->SetIsMenuCleared(true);

				menuManager->PrintMenuFromScene(userInput, false);
				mainClassAccess->SetIsMenuCleared(false);
			}
			oneLoopOFTwo = false;
		}
		else 
		{
			for (int i = 0; i < numLoops; i++) 
			{
				if (mainClassAccess->GetIsMenuCleared())
				{
					menuManager->PrintMenuFromScene(userInput, false);
					mainClassAccess->SetIsMenuCleared(false);
				}
			}

			if (!mainClassAccess->GetIsMenuCleared()) 
			{
				std::cout << "\033[1A\033[0K";
				menuManager->SetCurrentSceneMenuText(EMPTY_MENU_TEXT);
				mainClassAccess->SetIsMenuCleared(true);

				menuManager->PrintMenuFromScene(userInput, true);
				mainClassAccess->SetIsMenuCleared(false);
			}
			oneLoopOFTwo = true;
		}

		//if (oneLoopOFTwo)
		//{
		//	if (mainClassAcces->GetIsMenuCleared())
		//	{
		//		// Print selected scene menu.
		//		menuManager->PrintMenuFromScene(userInput, oneLoopOFTwo);
		//		mainClassAcces->SetIsMenuCleared(false);
		//	}
		//	else
		//	{
		//		// Clear the previous line.
		//		std::cout << "\033[1A\033[0K";
		//		mainClassAcces->SetIsMenuCleared(true);
		//	}

		//	oneLoopOFTwo = false;
		//}
		//else
		//{
		//	if (mainClassAcces->GetIsMenuCleared())
		//	{
		//		// Print plain scene menu.
		//		menuManager->PrintMenuFromScene(userInput, oneLoopOFTwo);
		//		mainClassAcces->SetIsMenuCleared(false);
		//	}
		//	else
		//	{
		//		// Clear the previous line.
		//		std::cout << "\033[1A\033[0K";
		//		mainClassAcces->SetIsMenuCleared(true);
		//	}

		//	oneLoopOFTwo = true;
		//}

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Clean up dynamically allocated memory.
	delete menuManager;
	delete textManager;
	delete sceneManager;

	return 0;
}

//void MainClass::SetIsSceneCleared(bool isSceneCleared)
//{
//	m_isSceneCleared = isSceneCleared;
//}
//
//bool MainClass::GetIsSceneCleared()
//{
//	return m_isSceneCleared;
//}

void MainClass::SetIsMenuCleared(bool isMenuCleared)
{
	m_isMenuCleared = isMenuCleared;
}

bool MainClass::GetIsMenuCleared()
{
	return m_isMenuCleared;
}