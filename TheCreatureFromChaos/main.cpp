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
#include "MainClass.h"

int main()
{
	DEBUG_MSG("#B main.cpp : main() : Enters main function.");

	// Initialize the main class that handles all the other classes
	MainClass* mainClass = new MainClass();

	// Initialize the console object and set its properties
	mainClass->InitializeConsoleHandler();
	mainClass->InitializeClasses();

	// Initialize the user input variable for the main loop
	E_UserInput userInput = E_UserInput::EMPTY;

	// Initialize conditional variables for the main loop
	bool isMenuCleared = mainClass->GetMenuManager()->GetIsMenuCleared();
	bool isFightStarted = mainClass->GetCombatManager()->GetIsFightStarted();
	bool isFightLogCleared = mainClass->GetCombatManager()->GetIsFightLogCleared();
	bool isCurrentFightStartedLog = mainClass->GetCombatManager()->GetIsCurrentFightStartedLog();
	bool isCountdownStarted = mainClass->GetCombatManager()->GetIsCountdownStarted();
	bool isCountdownLogCleared = mainClass->GetCombatManager()->GetIsCountdownLogCleared();
	bool isPlayerInNavigationMode = (mainClass->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::NAVIGATION);
	bool isPlayerInCombatMode = (mainClass->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::COMBAT);
	bool isWeaponBeltCleared = mainClass->GetWeaponManager()->GetIsWeaponBeltCleared();
	bool areWeaponsEquiped = mainClass->GetUserData()->GetAreWeaponsEquiped();

	// Print Intro scene.
	mainClass->GetNarrationManager()->PrintLinesFromScene();

	// Initialize the timer variables for the main loop
	auto start_time = std::chrono::steady_clock::now();
	auto next_print_time = start_time + std::chrono::seconds(1);


	//DEBUG_MSG("main.cpp : main() : Enters main loop.");
	while (mainClass->GetConsoleHandler()->GetIsGameRunning())
	{
		// Process user input
		if (_kbhit())
		{
			// Transforms the user input into a gameplay value
			userInput = mainClass->GetUserInputManager()->GetInput();

			// Assign an action to that value
			mainClass->GetUserInputManager()->SetAction(userInput);
		}

		// Update the boolean conditions
		isMenuCleared = mainClass->GetMenuManager()->GetIsMenuCleared();

		// Verify if the menu has been cleared by previous interactions
		if (isMenuCleared)
		{
			// Reprint what has been cleared
			userInput = E_UserInput::EMPTY;
			mainClass->GetMenuManager()->SelectMenuFromScene(userInput);
		}

		// Update the boolean conditions
		areWeaponsEquiped = mainClass->GetUserData()->GetAreWeaponsEquiped();
		isWeaponBeltCleared = mainClass->GetWeaponManager()->GetIsWeaponBeltCleared();
		isPlayerInNavigationMode = (mainClass->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::NAVIGATION);
		isPlayerInCombatMode = (mainClass->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::COMBAT);
		
		// Verify if the weapon belt log has been cleared by previous interactions
		if (areWeaponsEquiped && isWeaponBeltCleared && (isPlayerInNavigationMode || isPlayerInCombatMode))
		{
			// Reprint what has been cleared
			userInput = E_UserInput::EMPTY;
			mainClass->GetWeaponManager()->SelectWeapon(userInput);
		}

		// Update the boolean conditions
		isCurrentFightStartedLog = mainClass->GetCombatManager()->GetIsCurrentFightStartedLog();
		isFightLogCleared = mainClass->GetCombatManager()->GetIsFightLogCleared();

		// Verify if the fight log has been cleared by previous interactions
		if (isCurrentFightStartedLog && isFightLogCleared)
		{
			// Reprint what has been cleared
			userInput = E_UserInput::EMPTY;
			mainClass->GetCombatManager()->SetCombatAction(userInput);
		}

		// Update the boolean conditions
		isCountdownLogCleared = mainClass->GetCombatManager()->GetIsCountdownLogCleared();
		isCountdownStarted = mainClass->GetCombatManager()->GetIsCountdownStarted();

		// Verify if the countdown log has been cleared by previous interactions
		if (isCountdownStarted && isCountdownLogCleared)
		{
			// Reprint what has been cleared
			mainClass->GetCombatManager()->PrintRemaningSeconds();
			mainClass->GetCombatManager()->Countdown(9, start_time, next_print_time);
		}
	}

	exit(EXIT_SUCCESS);
	return 0;
}

void MainClass::InitializeConsoleHandler()
{
	// hadles the console window and its attributes
	ConsoleHandler* consoleHandler = new ConsoleHandler();
	SetConsoleHandler(consoleHandler);

	consoleHandler->SetConsolesize();
	consoleHandler->SetCenterConsolePosition();
	consoleHandler->DisableConsoleCursor();
	consoleHandler->DisableConsoleScrolling();
	//consoleHandler->ActivateConsoleCursor();
}

void MainClass::InitializeClasses()
{
	// Initialize the user data object that handles the user data
	UserData* userData = new UserData();
	SetUserData(userData);

	// Initialize the scenes manager object that manage the scenes successions
	ScenesManager* scenesManager = new ScenesManager(userData);
	SetScenesManager(scenesManager);

	// Initialize the narration manager object that manage and print the narration texts according to the current scene
	NarrationManager* narrationManager = new NarrationManager(scenesManager);
	SetNarrationManager(narrationManager);

	scenesManager->SetNarrationManager(narrationManager);

	// Initialize the menu manager object that manage and print the action menus according to the current scene
	MenuManager* menuManager = new MenuManager(GetConsoleHandler(), scenesManager, narrationManager, userData);
	SetMenuManager(menuManager);

	scenesManager->SetMenuManager(menuManager);

	// Initialize the combat manager object that manage the combat actions and menu
	CombatManager* combatManager = new CombatManager(userData, menuManager);
	SetCombatManager(combatManager);

	scenesManager->SetCombatManager(combatManager);
	menuManager->SetCombatManager(combatManager);

	// Initialize the user input manager object that manage the user inputs
	UserInputManager* inputManager = new UserInputManager(GetConsoleHandler(), scenesManager, menuManager);
	SetUserInputManager(inputManager);

	narrationManager->SetUserInputManager(inputManager);

	// Initialize the weapon manager object that manage the weapons and the weapon belt log
	WeaponManager* weaponManager = new WeaponManager(menuManager);
	SetWeaponManager(weaponManager);

	scenesManager->SetWeaponManager(weaponManager);
	inputManager->SetWeaponManager(weaponManager);
	menuManager->SetWeaponManager(weaponManager);
	combatManager->SetWeaponManager(weaponManager);
}

MainClass::MainClass() :
	m_userData(nullptr),
	m_narrationManager(nullptr),
	m_menuManager(nullptr),
	m_combatManager(nullptr),
	m_userInputManager(nullptr),
	m_weaponManager(nullptr),
	m_scenesManager(nullptr),
	m_consoleHandler(nullptr)
{
}

MainClass::~MainClass() {
	delete m_userData;
	delete m_narrationManager; 
	delete m_menuManager;
	delete m_combatManager; 
	delete m_userInputManager; 
	delete m_weaponManager; 
	delete m_scenesManager;
	delete m_consoleHandler;
}

NarrationManager* MainClass::GetNarrationManager()
{
	return m_narrationManager;
}

void MainClass::SetNarrationManager(NarrationManager* narrationManager)
{
	m_narrationManager = narrationManager;
}

MenuManager* MainClass::GetMenuManager()
{
	return m_menuManager;
}

void MainClass::SetMenuManager(MenuManager* menuManager)
{
	m_menuManager = menuManager;
}

CombatManager* MainClass::GetCombatManager()
{
	return m_combatManager;
}

void MainClass::SetCombatManager(CombatManager* combatManager)
{
	m_combatManager = combatManager;
}

UserInputManager* MainClass::GetUserInputManager()
{
	return m_userInputManager;
}

void MainClass::SetUserInputManager(UserInputManager* userInputManager)
{
	m_userInputManager = userInputManager;
}

WeaponManager* MainClass::GetWeaponManager()
{
	return m_weaponManager;
}

void MainClass::SetWeaponManager(WeaponManager* weaponManager)
{
	m_weaponManager = weaponManager;
}

UserData* MainClass::GetUserData()
{
	return m_userData;
}

void MainClass::SetUserData(UserData* userData)
{
	m_userData = userData;
}

ScenesManager* MainClass::GetScenesManager()
{
	return m_scenesManager;
}

void MainClass::SetScenesManager(ScenesManager* scenesManager)
{
	m_scenesManager = scenesManager;
}

ConsoleHandler* MainClass::GetConsoleHandler()
{
	return m_consoleHandler;
}

void MainClass::SetConsoleHandler(ConsoleHandler* consoleHandler)
{
	m_consoleHandler = consoleHandler;
}