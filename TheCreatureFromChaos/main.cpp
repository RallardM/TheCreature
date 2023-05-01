#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>

#include "Utils.h"


#include "UserInputManager.h"
#include "ScenesNarrationManager.h"
#include "ScenesMenuManager.h"
#include "DebugMessageSystem.h"
#include "main.h"


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

	// Initialize the MainClass object.
	//DEBUG_MSG("main.cpp : main() : Initialize the MainClass object.");
	MainClass* mainClassAccess = new MainClass();
	//mainClassAccess->SetMainClassAccess(mainClassAccess);

	// Initialize the UserInputManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the UserInputManager object.");
	UserInputManager* inputManager{};
	mainClassAccess->SetMainInputManager(inputManager);

	// Initialize the UserScenesManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the UserScenesManager object.");
	UserScenesManager* sceneManager = new UserScenesManager();
	mainClassAccess->SetMainSceneManager(sceneManager);

	// Initialize the ScenesNarrationManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the ScenesNarrationManager object.");
	//ScenesNarrationManager* narrationManager = new ScenesNarrationManager(mainClassAcces, sceneManager);
	ScenesNarrationManager* narrationManager = new ScenesNarrationManager(sceneManager);
	mainClassAccess->SetMainNarrationManager(narrationManager);

	// Initialize the ScenesMenuManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the ScenesMenuManager object.");
	ScenesMenuManager* menuManager = new ScenesMenuManager(sceneManager, narrationManager);
	//ScenesMenuManager* menuManager = new ScenesMenuManager(mainClassAccess, sceneManager, narrationManager);
	mainClassAccess->SetMainMenuManager(menuManager);

	unsigned short int counter = 0;
	unsigned short int numLoops = 5;

	mainClassAccess->SetIsMenuCleared(true);
	//bool oneLoopOFTwo = true;
	UserInputManager::E_UserInput userInput = UserInputManager::E_UserInput::EMPTY;
	bool isSceneCleared = true;
	
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

		//if (mainClassAcces->GetIsSceneCleared())
		if (isSceneCleared)
		{
			// Print the scene text.
			narrationManager->PrintLinesFromScene();
			//mainClassAcces->SetIsSceneCleared(false);
			isSceneCleared = false;
		}

		if (mainClassAccess->GetIsMenuCleared())
		{
			menuManager->PrintMenuFromScene(userInput);
			mainClassAccess->SetIsMenuCleared(false);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Clean up dynamically allocated memory.
	delete menuManager;
	delete narrationManager;
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

UserInputManager* MainClass::GetMainInputManager()
{
	return m_inputManager;
}

UserScenesManager* MainClass::GetMainSceneManager()
{
	return m_sceneManager;
}

ScenesNarrationManager* MainClass::GetMainNarrationManager()
{
	return m_narrationManager;
}

ScenesMenuManager* MainClass::GetMainMenuManager()
{
	return m_menuManager;
}

void MainClass::SetMainInputManager(UserInputManager* inputManager)
{
	m_inputManager = inputManager;
}

void MainClass::SetMainSceneManager(UserScenesManager* sceneManager)
{
	m_sceneManager = sceneManager;
}

void MainClass::SetMainNarrationManager(ScenesNarrationManager* narrationManager)
{
	m_narrationManager = narrationManager;
}

void MainClass::SetMainMenuManager(ScenesMenuManager* menuManager)
{
	m_menuManager = menuManager;
}