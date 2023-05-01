#pragma once

#include <fstream>

#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "ScenesNarrationManager.h"
//#include "main.h"

//class UserInputManager;
//class UserScenesManager;
//class ScenesNarrationManager;

const short int EMPTY_MENU_LINE = -1;
const std::string EMPTY_MENU_TEXT = "";
const unsigned short int NUMBER_OF_HIGHLIGHTED_MENU_LINES = 4;
const unsigned short int UNHIGHLIGHTED_MENU_LINE = 1;

class ScenesMenuManager {
public:
	ScenesMenuManager(UserScenesManager* sceneManager, ScenesNarrationManager* textManager);
	//ScenesMenuManager(MainClass* mainClassAccess, UserScenesManager* sceneManager, ScenesNarrationManager* textManager);
	ScenesMenuManager();

	void PrintMenuFromScene(UserInputManager::E_UserInput userInput);

	std::string GetLastLineInConsole();

	//unsigned short int GetGameMenuLine(UserScenesManager::E_SceneSequence fromLine);

	//void SetCurrentPlainMenu(short int currentPlainMenu);
	//short int GetCurrentPlainMenu();

	//std::string GetCurrentSceneMenuText();
	//void SetCurrentSceneMenuText(std::string sceneMenu);

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, unsigned short int atLine);

	void ClearConsolePreviousLine();

private:
	//unsigned short int m_gameMenuLines[2];
	unsigned short int m_introHighlightedMenu[NUMBER_OF_HIGHLIGHTED_MENU_LINES];
	short int m_selectedMenuLine;
	//short int m_currentPlainMenu;
	//std::string m_currenSceneMenuText;
	std::ifstream m_menuFilePath;

	//MainClass* m_mainClassAccess;
	UserScenesManager* m_sceneManager;
	ScenesNarrationManager* m_narrationManager;
};