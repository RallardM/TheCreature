#pragma once

#include <fstream>
#include "ScenesManager.h"
class ScenesManager;
#include "ScenesControllers.h"
using namespace ScenesControllers;

class MenuManager {
public:
	const short int EMPTY_MENU_LINE = -1;
	const std::string EMPTY_MENU_TEXT = "";

	MenuManager(ScenesManager* sceneManager, NarrationManager* textManager);

	void PrintMenuFromScene(E_UserInput userInput);
	void SelectSceneToPrint(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice);

	std::string GetLastLineInConsole();

	E_MenuChoices GetSelectedMenuLine();
	void SetSelectedMenuLine(E_MenuChoices selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, E_MenuChoices atLine);

	void ClearConsolePreviousLine();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	NarrationManager* GetNarrationManager();
	ScenesManager* GetSceneManager();

	//UserInputManager* GetUserInputManager();
	//void SetUserInputManager(UserInputManager* inputManager);

private:

	E_MenuChoices m_selectedMenuLine;

	std::ifstream m_menuFilePath;
	bool m_isMenuCleared;

	ScenesManager* m_sceneManager;
	NarrationManager* m_narrationManager;
	//UserInputManager* m_inputManager;

};
