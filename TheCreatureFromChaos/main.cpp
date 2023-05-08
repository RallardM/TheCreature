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
	Menu* menu = new Menu(scenes);
	Weapons* weapon = new Weapons();
	UserData* userData = new UserData(weapon);
	Combat* combat = new Combat();
	Narration* narration = new Narration();

	UserInput* inputManager = new UserInput();
	ConsoleHandler* consoleHandler = new ConsoleHandler(inputManager);
	consoleHandler->SetConsolesize();
	consoleHandler->SetCenterConsolePosition();
	//consoleHandler->DisableConsoleCursor();
	consoleHandler->DisableConsoleScrolling();
	consoleHandler->ActivateConsoleCursor();
	narration->SetConsoleHandler(consoleHandler);
	E_UserInput userInput = E_UserInput::EMPTY;


	OutputManager* outputManager = new OutputManager();
	GameplayManager* gameplayManager = new GameplayManager(scenes);
	
	narration->SetGameplayManager(gameplayManager);
	inputManager->SetGameplayManager(gameplayManager);
	inputManager->SetOutputManager(outputManager);
	gameplayManager->SetCombat(combat);
	combat->SetUserData(userData);

	outputManager->SetNarration(narration);

	
	//menu->SetGameplayManager(gameplayManager);
	//menu->SetScenes(scenes);
	menu->SetOutputManager(outputManager);
	menu->SetConsoleHandler(consoleHandler);

	gameplayManager->SetScenes(scenes);
	//scenes->SetGameplayManager(gameplayManager);
	scenes->SetOutputManager(outputManager);
	scenes->SetUserData(userData);
	scenes->SetCombat(combat);

	// Print Intro scene.
	narration->PrintLinesFromScene();

	//bool gameRunning = true;

	//DEBUG_MSG("main.cpp : main() : Enters main loop.");
	while (true)
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
