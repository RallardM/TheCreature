#pragma once

#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "main.h"
//#include "GameTextManager.h"
class GameTextManager;


class GameChoicesMenu {
public:
	GameChoicesMenu(MainClass* mainClassAcces, UserScenesManager* sceneManager, GameTextManager* textManager);
	void PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo);
	//UserScenesManager* GetSceneManager();
	//GameTextManager* GetGameTextManager();

	std::string GetLastLineInConsole();

	unsigned short int GetGameMenuLine(unsigned short int fromLine);

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);

	void SetCurrentPlainMenu(short int currentPlainMenu);
	short int GetCurrentPlainMenu();

	std::string GetCurrentSceneMenu();
	void SetCurrentSceneMenu(std::string sceneMenu);

private:
	unsigned short int m_gameMenuLines[2];
	unsigned short int m_selectedMenuLine;
	short int m_currentPlainMenu;
	std::string m_currenSceneMenuText;

	MainClass* m_mainClassAcces;
	UserScenesManager* m_sceneManager;
	GameTextManager* m_textManager;
};