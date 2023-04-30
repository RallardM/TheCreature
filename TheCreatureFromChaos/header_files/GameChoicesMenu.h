#pragma once

#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "main.h"
//#include "GameTextManager.h"
class GameTextManager;


class GameChoicesMenu {
public:
	GameChoicesMenu(MainClass* mainClassAccess, UserScenesManager* sceneManager, GameTextManager* textManager);
	void PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo);
	//UserScenesManager* GetSceneManager();
	//GameTextManager* GetGameTextManager();

	std::string GetLastLineInConsole();

	unsigned short int GetGameMenuLine(UserScenesManager::E_SceneSequence fromLine);

	void SetCurrentPlainMenu(short int currentPlainMenu);
	short int GetCurrentPlainMenu();

	std::string GetCurrentSceneMenuText();
	void SetCurrentSceneMenuText(std::string sceneMenu);

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);

private:
	unsigned short int m_gameMenuLines[2];
	short int m_selectedMenuLine;
	short int m_currentPlainMenu;
	std::string m_currenSceneMenuText;

	MainClass* m_mainClassAccess;
	UserScenesManager* m_sceneManager;
	GameTextManager* m_textManager;
};