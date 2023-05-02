#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <fstream>

#include "ScenesManager.h"
#include "UserInputManager.h"
#include "NarrationManager.h"
#include "MenuManager.h"

const short int EMPTY_MENU_LINE = -1;
const std::string EMPTY_MENU_TEXT = "";
const unsigned short int NUMBER_OF_HIGHLIGHTED_MENU_LINES = 4;
const unsigned short int UNHIGHLIGHTED_MENU_LINE = 1;

class MenuManager {
public:
	unsigned short int g_introHighlightedMenu[NUMBER_OF_HIGHLIGHTED_MENU_LINES]{ 2, 3, 4, 5 };

	MenuManager(ScenesManager* sceneManager, NarrationManager* textManager);


	void PrintMenuFromScene(UserInputManager::E_UserInput userInput);

	std::string GetLastLineInConsole();

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, unsigned short int atLine);

	void ClearConsolePreviousLine();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

private:

	short int m_selectedMenuLine;

	std::ifstream m_menuFilePath;
	bool m_isMenuCleared;

	ScenesManager* m_sceneManager;
	NarrationManager* m_narrationManager;
};
#endif // MENUMANAGER_H