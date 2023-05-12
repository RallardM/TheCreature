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
	DEBUG_MSG("#B main.cpp : main() : Enters main function.");

	// Initialize the console object and set its properties
	// that hadles the console window and its attributes
	ConsoleHandler* consoleHandler = new ConsoleHandler();
	consoleHandler->SetConsolesize();
	consoleHandler->SetCenterConsolePosition();
	consoleHandler->DisableConsoleCursor();
	consoleHandler->DisableConsoleScrolling();
	//consoleHandler->ActivateConsoleCursor();

	// Initialize the user data object that handles the user data
	UserData* userData = new UserData();
	bool areWeaponsEquiped = userData->GetAreWeaponsEquiped();

	// Initialize the scenes manager object that manage the scenes successions
	ScenesManager* scenesManager = new ScenesManager(userData);

	// Initialize the narration manager object that manage and print the narration texts according to the current scene
	NarrationManager* narrationManager = new NarrationManager(scenesManager);
	scenesManager->SetNarrationManager(narrationManager);

	// Initialize the menu manager object that manage and print the action menus according to the current scene
	MenuManager* menuManager = new MenuManager(consoleHandler, scenesManager, narrationManager, userData);
	scenesManager->SetMenuManager(menuManager);
	bool isMenuCleared = menuManager->GetIsMenuCleared();

	CombatManager* combatManager = new CombatManager(userData, menuManager);
	bool isFightStarted = combatManager->GetIsFightStarted();
	bool isFightLogCleared = combatManager->GetIsFightLogCleared();
	bool isCurrentFightStartedLog = combatManager->GetIsCurrentFightStartedLog();
	bool isCountdownStarted = combatManager->GetIsCountdownStarted();
	bool isCountdownLogCleared = combatManager->GetIsCountdownLogCleared();
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

		isCurrentFightStartedLog = combatManager->GetIsCurrentFightStartedLog();
		isFightLogCleared = combatManager->GetIsFightLogCleared();
		if (isCurrentFightStartedLog && isFightLogCleared)
		{
			userInput = E_UserInput::EMPTY;
			combatManager->SetCombatAction(userInput);
		}

		isCountdownLogCleared = combatManager->GetIsCountdownLogCleared();
		isCountdownStarted = combatManager->GetIsCountdownStarted();
		if (isCountdownStarted && isCountdownLogCleared)
		{
			combatManager->PrintRemaningSeconds();
			combatManager->Countdown(9, start_time, next_print_time);
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
