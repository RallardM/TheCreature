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

	// Print Intro scene.
	narrationManager->PrintLinesFromScene();

	UserInputManager* inputManager = new UserInputManager(sceneManager, menuManager);


	unsigned short int counter = 0;
	unsigned short int numLoops = 5;

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
			menuManager->PrintMenuFromScene(userInput);
			//menuManager->SetIsMenuCleared(false);
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

//void MainClass::SetIsSceneCleared(bool isSceneCleared)
//{
//	m_isSceneCleared = isSceneCleared;
//}
//
//bool MainClass::GetIsSceneCleared()
//{
//	return m_isSceneCleared;
//}

//void MainClass::SetIsMenuCleared(bool isMenuCleared)
//{
//	m_isMenuCleared = isMenuCleared;
//}
//
//bool MainClass::GetIsMenuCleared()
//{
//	return m_isMenuCleared;
//}

//UserInputManager* MainClass::GetMainInputManager()
//{
//	return m_inputManager;
//}
//
//ScenesManager* MainClass::GetMainSceneManager()
//{
//	return m_sceneManager;
//}
//
//NarrationManager* MainClass::GetMainNarrationManager()
//{
//	return m_narrationManager;
//}
//
//MenuManager* MainClass::GetMainMenuManager()
//{
//	return m_menuManager;
//}
//
//void MainClass::SetMainInputManager(UserInputManager* inputManager)
//{
//	m_inputManager = inputManager;
//}
//
//void MainClass::SetMainSceneManager(ScenesManager* sceneManager)
//{
//	m_sceneManager = sceneManager;
//}
//
//void MainClass::SetMainNarrationManager(NarrationManager* narrationManager)
//{
//	m_narrationManager = narrationManager;
//}
//
//void MainClass::SetMainMenuManager(MenuManager* menuManager)
//{
//	m_menuManager = menuManager;
//}