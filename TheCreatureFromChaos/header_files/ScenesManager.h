#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
//#pragma once
// include string
#include <string>
//#include <UserInputManager.h>

//#include "UserInputManager.h"

class ScenesManager {
public:
	const short int EMPTY_MENU_LINE = -1;
	const std::string EMPTY_MENU_TEXT = "";
	const unsigned short int NUMBER_OF_HIGHLIGHTED_MENU_LINES = 4;
	const unsigned short int UNHIGHLIGHTED_MENU_LINE = 1;
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };
	enum class E_SceneSequence {
		//  NarrationManager.cpp m_sceneMenuLines{ 1, 6 }
		NO_SCENE = -1, 
		INTRO_SCENE = 0, // line 1 
		MOVING_SCENE = 2, // line 6
	};

	//ScenesManager();
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(E_UserInput userInput);
	void PrintMenuFromScene(E_UserInput userInput);
	void PrintLinesFromScene();

	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine);

	ScenesManager* GetSceneManager();

	unsigned short int GetSceneMenuLine(ScenesManager::E_SceneSequence fromLine);
	std::string GetLastLineInConsole();

	unsigned short int GetSelectedMenuLine();
	void SetSelectedMenuLine(unsigned short int selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, unsigned short int atLine);

	void ClearConsolePreviousLine();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

private:
	E_SceneSequence m_userCurrentScene;

	short int m_selectedMenuLine;

	//std::ifstream m_menuFilePath;
	bool m_isMenuCleared;
	bool m_hasInput;
	//ScenesManager* m_sceneManager;
	//NarrationManager* m_narrationManager;

	unsigned short int GetSceneTextLines(ScenesManager::E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(ScenesManager::E_SceneSequence fromLine);

	//ScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;

	unsigned short int m_introHighlightedMenu[4] = { 2, 3, 4, 5 };
	unsigned short int m_sceneTextLines[2];
	unsigned short int m_sceneImageLines[2];
	unsigned short int m_sceneMenuLines[2];
};
#endif // SCENEMANAGER_HPP