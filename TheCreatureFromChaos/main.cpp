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
#include "WeaponManager.h"
#include "CombatManager.h"

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

	consoleHandler->ActivateConsoleCursor();

	UserData* userData = new UserData();

	ScenesManager* scenesManager = new ScenesManager(userData);

	NarrationManager* narrationManager = new NarrationManager(scenesManager);
	scenesManager->SetNarrationManager(narrationManager);

	MenuManager* menuManager = new MenuManager(consoleHandler, scenesManager, narrationManager, userData);
	scenesManager->SetMenuManager(menuManager);

	// Print Intro scene.
	narrationManager->PrintLinesFromScene();

	CombatManager* combatManager = new CombatManager(userData);

	UserInputManager* inputManager = new UserInputManager(consoleHandler, scenesManager, menuManager, combatManager);
	E_UserInput userInput = E_UserInput::EMPTY;
	narrationManager->SetUserInputManager(inputManager);

	WeaponManager* weaponManager = new WeaponManager(menuManager);
	scenesManager->SetWeaponManager(weaponManager);
	inputManager->SetWeaponManager(weaponManager);
	menuManager->SetWeaponManager(weaponManager);
	combatManager->SetWeaponManager(weaponManager);

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
			userInput = E_UserInput::EMPTY;
			menuManager->SelectMenuFromScene(userInput);
		}

		if (userData->GetAreWeaponsEquiped() && weaponManager->GetIsMenuCleared())
		{
			userInput = E_UserInput::EMPTY;
			weaponManager->SelectWeapon(userInput);
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
	delete combatManager;
	delete weaponManager;

	return 0;
}
