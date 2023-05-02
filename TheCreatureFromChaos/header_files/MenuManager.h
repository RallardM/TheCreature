#pragma once

#include <fstream>

#include "ScenesManager.h"
#include "Globals.h"
//#include "UserInputManager.h"
//#include "NarrationManager.h"


class ScenesManager;
//class NarrationManager;
//class UserInputManager;

class MenuManager {
public:

	E_MenuChoices g_introHighlightedMenu[G_TWO_MENU_CHOICES]
	{
		E_MenuChoices::TRY_TO_MOVE,
		E_MenuChoices::DO_NOTHING
	};

	const short int EMPTY_MENU_LINE = -1;
	const std::string EMPTY_MENU_TEXT = "";

	MenuManager(ScenesManager* sceneManager, NarrationManager* textManager);


	void PrintMenuFromScene(E_UserInput userInput);

	std::string GetLastLineInConsole();

	E_MenuChoices GetSelectedMenuLine();
	void SetSelectedMenuLine(E_MenuChoices selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, E_MenuChoices atLine);

	void ClearConsolePreviousLine();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	NarrationManager* GetNarrationManager();

private:

	E_MenuChoices m_selectedMenuLine;

	std::ifstream m_menuFilePath;
	bool m_isMenuCleared;

	ScenesManager* m_sceneManager;
	NarrationManager* m_narrationManager;
};
