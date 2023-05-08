#pragma once

#include <fstream>

#include "Scenes.h"
class Scenes;
#include "PublicConstants.h"
#include "UserData.h"
#include "ConsoleHandler.h"
//#include "GameplayManager.h"
//class GameplayManager;

using namespace PublicConstants;

class Menu {
public:
	const short int EMPTY_MENU_LINE = -1;
	const std::string EMPTY_MENU_TEXT = "";

	Menu(Scenes* scenes);
	void SelectMenuFromScene(E_UserInput userInput);
	void SelectMenuChoice(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice);

	void SelectNavigationElement(E_UserInput userInput, E_MenuChoices menuChoice);
	void PrepareNavigationMenu(E_MenuChoices menuChoice, unsigned short int numberOfUiElementsToJumpOver);

	void SelectCombatChoice(E_UserInput userInput, E_MenuChoices menuChoice);

	void PrintSingleMenuChoice(E_UserInput userInput, E_MenuChoices menuChoice);
	void PrintSelectedMenu(E_MenuChoices currentMenuChoice);
	void PrintNavigationMenu(E_MenuChoices currentMenuChoice);
	void PrintEnterNameMenu();


	std::string GetLastLineInConsole();

	E_MenuChoices GetSelectedMenuLine();
	void SetSelectedMenuLine(E_MenuChoices selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, E_MenuChoices atLine);

	void ClearConsolePreviousLine();
	void ClearConsoleNavigationMenu();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	//Narration* GetNarrationManager();
	//Scenes* GetScenesManager();
	//UserData* GetUserData();

	void AddDelay();

	//Weapons* GetWeaponManager();
	//void SetWeaponManager(Weapons* weaponManager);

	//GameplayManager* GetGameplayManager();
	//void SetGameplayManager(GameplayManager* gameplayManager);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	OutputManager* GetOutputManager();
	void SetOutputManager(OutputManager* outputManager);

	ConsoleHandler* GetConsoleHandler();
	void SetConsoleHandler(ConsoleHandler* consoleHandler);

	Scenes* GetScenes();
	//void SetScenes(Scenes* scenes);

private:

	E_MenuChoices m_selectedMenuLine;

	//std::ifstream m_menuFilePath;
	bool m_isMenuCleared;

	//GameplayManager* m_gameplayManager;
	Scenes* m_scenes;
	UserData* m_userData;
	OutputManager* m_outputManager;

	ConsoleHandler* m_consoleHandler;
	//Scenes* m_scenesManager;
	//Narration* m_narrationManager;
	//UserData* m_userData;
	//Weapons* m_weaponManager;
};