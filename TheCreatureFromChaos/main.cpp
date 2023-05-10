#include <iostream>
#include <string>
#include <chrono>
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
	consoleHandler->DisableConsoleScrolling();
	consoleHandler->ActivateConsoleCursor();

	UserData* userData = new UserData();
	bool areWeaponsEquiped = userData->GetAreWeaponsEquiped();

	ScenesManager* scenesManager = new ScenesManager(userData);

	NarrationManager* narrationManager = new NarrationManager(scenesManager);
	scenesManager->SetNarrationManager(narrationManager);

	MenuManager* menuManager = new MenuManager(consoleHandler, scenesManager, narrationManager, userData);
	scenesManager->SetMenuManager(menuManager);
	bool isMenuCleared = menuManager->GetIsMenuCleared();

	CombatManager* combatManager = new CombatManager(userData, menuManager);
	bool isFightStarted = combatManager->GetIsFightStarted();
	bool isFightLogCleared = combatManager->GetIsFightLogCleared();
	scenesManager->SetCombatManager(combatManager);
	menuManager->SetCombatManager(combatManager);

	UserInputManager* inputManager = new UserInputManager(consoleHandler, scenesManager, menuManager);
	bool isPlayerInNavigationMode = (inputManager->GetCurrentInputType() == UserInputManager::E_CurrentInputType::NAVIGATION);
	bool isPlayerInCombatMode = (inputManager->GetCurrentInputType() == UserInputManager::E_CurrentInputType::COMBAT);
	E_UserInput userInput = E_UserInput::EMPTY;
	narrationManager->SetUserInputManager(inputManager);

	WeaponManager* weaponManager = new WeaponManager(menuManager);
	bool isWeaponBeltCleared = weaponManager->GetIsWeaponBeltCleared();
	scenesManager->SetWeaponManager(weaponManager);
	inputManager->SetWeaponManager(weaponManager);
	menuManager->SetWeaponManager(weaponManager);
	combatManager->SetWeaponManager(weaponManager);
	
	// Print Intro scene.
	narrationManager->PrintLinesFromScene();

	auto start_time = std::chrono::steady_clock::now();
	auto next_print_time = start_time + std::chrono::seconds(1);


	//DEBUG_MSG("main.cpp : main() : Enters main loop.");
	while (consoleHandler->GetIsGameRunning())
	{
		// Process user input
		if (_kbhit())
		{
			userInput = inputManager->GetInput();
			inputManager->SetAction(userInput);
		}

		isMenuCleared = menuManager->GetIsMenuCleared();
		if (isMenuCleared)
		{
			userInput = E_UserInput::EMPTY;
			menuManager->SelectMenuFromScene(userInput);
		}

		areWeaponsEquiped = userData->GetAreWeaponsEquiped();
		isWeaponBeltCleared = weaponManager->GetIsWeaponBeltCleared();
		isPlayerInNavigationMode = (inputManager->GetCurrentInputType() == UserInputManager::E_CurrentInputType::NAVIGATION);
		isPlayerInCombatMode = (inputManager->GetCurrentInputType() == UserInputManager::E_CurrentInputType::COMBAT);
		if (areWeaponsEquiped && isWeaponBeltCleared && (isPlayerInNavigationMode || isPlayerInCombatMode))
		{
			userInput = E_UserInput::EMPTY;
			weaponManager->SelectWeapon(userInput);
		}

		isFightStarted = combatManager->GetIsFightStarted();
		isFightLogCleared = combatManager->GetIsFightLogCleared();
		if (isFightStarted && isFightLogCleared)
		{
			userInput = E_UserInput::EMPTY;
			combatManager->SetCombatAction(userInput);
		}


		if (combatManager->GetIsCountdownStarted() && !isMenuCleared)
		{
			combatManager->Countdown(10, start_time, next_print_time);
		}
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
	exit(EXIT_SUCCESS);
	return 0;
}
