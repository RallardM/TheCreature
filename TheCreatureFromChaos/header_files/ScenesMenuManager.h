#pragma once

#include <fstream>

#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "main.h"

class ScenesNarrationManager;

const short int EMPTY_MENU_LINE = -1;
const std::string EMPTY_MENU_TEXT = "";

class ScenesMenuManager {
public:
	ScenesMenuManager(MainClass* mainClassAccess, UserScenesManager* sceneManager, ScenesNarrationManager* textManager);
	void PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo);

	std::string GetLastLineInConsole();

	unsigned short int GetGameMenuLine(UserScenesManager::E_SceneSequence fromLine);

	void SetCurrentPlainMenu(short int currentPlainMenu);
	short int GetCurrentPlainMenu();

	std::string GetCurrentSceneMenuText();
	void SetCurrentSceneMenuText(std::string sceneMenu);

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, unsigned int atLine);
	//std::ifstream& GetMenuFilePath();

private:
	unsigned short int m_gameMenuLines[2];
	short int m_selectedMenuLine;
	short int m_currentPlainMenu;
	std::string m_currenSceneMenuText;
	std::ifstream m_menuFilePath;

	MainClass* m_mainClassAccess;
	UserScenesManager* m_sceneManager;
	ScenesNarrationManager* m_textManager;
};