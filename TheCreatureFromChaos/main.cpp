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
	//MainClass* mainClassAccess = new MainClass();
	//mainClassAccess->SetMainClassAccess(mainClassAccess);



	// Initialize the ScenesManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the ScenesManager object.");
	ScenesManager* sceneManager = new ScenesManager();
	//mainClassAccess->SetMainSceneManager(sceneManager);

	// Initialize the NarrationManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the NarrationManager object.");
	//NarrationManager* narrationManager = new NarrationManager(mainClassAcces, sceneManager);
	NarrationManager* narrationManager = new NarrationManager(sceneManager);
	//mainClassAccess->SetMainNarrationManager(narrationManager);

	// Initialize the MenuManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the MenuManager object.");
	MenuManager* menuManager = new MenuManager(sceneManager, narrationManager);
	//MenuManager* menuManager = new MenuManager(mainClassAccess, sceneManager, narrationManager);
	//mainClassAccess->SetMainMenuManager(menuManager);

	// Initialize the UserInputManager object.
	//DEBUG_MSG("main.cpp : main() : Initialize the UserInputManager object.");
	UserInputManager* inputManager = new UserInputManager(menuManager);
	//mainClassAccess->SetMainInputManager(inputManager);

	unsigned short int counter = 0;
	unsigned short int numLoops = 5;

	//mainClassAccess->SetIsMenuCleared(true);
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