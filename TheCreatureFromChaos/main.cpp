#include <iostream>
#include <string>
//#include <chrono>
#include <thread>
#include <conio.h>

#include "ConsoleHandler.h"
#include "UserInput.h"
#include "Narration.h"
#include "Menu.h"
#include "DebugMessageSystem.h"
#include "Scenes.h"
#include "UserData.h"
#include "Weapons.h"
#include "Combat.h"
#include "GameplayManager.h"
#include "OutputManager.h"

int main()
{
	//DEBUG_MSG("#B main.cpp : main() : Enters main function.");
	
	Scenes* scenes = new Scenes();
	Narration* narration = new Narration();
	Menu* menu = new Menu();
	Combat* combat = new Combat();
	Weapons* weapon = new Weapons();

	UserInput* inputManager = new UserInput();
	E_UserInput userInput = E_UserInput::EMPTY;

	//DEBUG_MSG("main.cpp : main() : Create a Utils object, set the console size and position.");
	ConsoleHandler* consoleHandler = new ConsoleHandler(inputManager);
	consoleHandler->SetConsolesize();
	consoleHandler->SetCenterConsolePosition();
	//consoleHandler->DisableConsoleCursor();
	consoleHandler->DisableConsoleScrolling();
	consoleHandler->ActivateConsoleCursor();

	menu->SetConsoleHandler(consoleHandler);

	UserData* userData = new UserData(weapon);
	scenes->SetUserData(userData);
	combat->SetUserData(userData);

	GameplayManager* gameplayManager = new GameplayManager(scenes, combat);
	scenes->SetGameplayManager(gameplayManager);
	menu->SetGameplayManager(gameplayManager);

	OutputManager* outputManager = new OutputManager(narration, menu);
	scenes->SetOutputManager(outputManager);
	
	// Print Intro scene.
	narration->PrintLinesFromScene();

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

		if (menu->GetIsMenuCleared())
		{
			userInput = E_UserInput::EMPTY;
			menu->SelectMenuFromScene(userInput);
		}

		if (userData->GetAreWeaponsEquiped() && weapon->GetIsMenuCleared())
		{
			userInput = E_UserInput::EMPTY;
			weapon->SelectWeapon(userInput);
		}

		if (combat->GetIsFightStarted() && combat->GetIsFightLogCleared())
		{
			userInput = E_UserInput::EMPTY;
			combat->SetCombatAction(userInput);
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Clean up dynamically allocated memory.
	delete consoleHandler;
	delete menu;
	delete userData;
	delete inputManager;
	delete narration;
	delete scenes;
	delete combat;
	delete weapon;
	delete gameplayManager;
	delete outputManager;

	return 0;
}
