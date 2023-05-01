#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <fstream>

#include "ScenesManager.h"
#include "UserInputManager.h"
#include "NarrationManager.h"


//class UserInputManager;
//class ScenesManager;
//class NarrationManager;

const short int EMPTY_MENU_LINE = -1;
const std::string EMPTY_MENU_TEXT = "";
const unsigned short int NUMBER_OF_HIGHLIGHTED_MENU_LINES = 4;
const unsigned short int UNHIGHLIGHTED_MENU_LINE = 1;

class MenuManager : ScenesManager {
public:
	unsigned short int g_introHighlightedMenu[NUMBER_OF_HIGHLIGHTED_MENU_LINES]{ 2, 3, 4, 5 };

	MenuManager(ScenesManager* sceneManager, NarrationManager* textManager);
	//MenuManager(MainClass* mainClassAccess, ScenesManager* sceneManager, NarrationManager* textManager);
	//MenuManager();

	void PrintMenuFromScene(UserInputManager::E_UserInput userInput);

	std::string GetLastLineInConsole();

	//unsigned short int GetGameMenuLine(ScenesManager::E_SceneSequence fromLine);

	//void SetCurrentPlainMenu(short int currentPlainMenu);
	//short int GetCurrentPlainMenu();

	//std::string GetCurrentSceneMenuText();
	//void SetCurrentSceneMenuText(std::string sceneMenu);

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, unsigned short int atLine);

	void ClearConsolePreviousLine();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

private:
	//unsigned short int m_gameMenuLines[2];
	//unsigned short int m_introHighlightedMenu[NUMBER_OF_HIGHLIGHTED_MENU_LINES];
	short int m_selectedMenuLine;
	//short int m_currentPlainMenu;
	//std::string m_currenSceneMenuText;
	std::ifstream m_menuFilePath;
	bool m_isMenuCleared;
	//MainClass* m_mainClassAccess;
	ScenesManager* m_sceneManager;
	NarrationManager* m_narrationManager;
};
#endif // MENUMANAGER_HPP