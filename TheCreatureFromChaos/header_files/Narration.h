#pragma once

#include <fstream>

//class Scenes;

#include "PublicConstants.h"
#include "GameplayManager.h"
#include "ConsoleHandler.h"
class ConsoleHandler;

using namespace PublicConstants;

class Narration{
public:

	Narration();;
	void PrintLinesFromScene();
	std::string GetPictureTextScene(E_SceneSequence scene, const unsigned short int height);
	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, const unsigned short int height);

	//Scenes* GetScenesManager();

	//UserInput* GetUserInputManager();
	//void SetUserInputManager(UserInput* userInputManager);

	const unsigned short int ASCII_IMAGE_HEIGHT     = 34;
	const unsigned short int NAVIGATION_MENU_HEIGHT =  7;
	const unsigned short int STORY_TEXT_HEIGHT      =  5;
	const unsigned short int NARRATION_MENU_HEIGHT  =  1;

	GameplayManager* GetGameplayManager();
	void SetGameplayManager(GameplayManager* gameplayManager);

	ConsoleHandler* GetConsoleHandler();
	void SetConsoleHandler(ConsoleHandler* consoleHandler);

private:
	GameplayManager* m_gameplayManager;
	ConsoleHandler* m_consoleHandler;

	unsigned short int GetSceneTextLines(E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(E_SceneSequence fromLine);

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;
};