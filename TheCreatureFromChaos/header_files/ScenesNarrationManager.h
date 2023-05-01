#pragma once

#include <fstream>

#include "Utils.h"
#include "UserScenesManager.h"
//#include "UserInputManager.h"
//#include "ScenesMenuManager.h"
#include "main.h"

//class ScenesMenuManager;

class ScenesNarrationManager {
public:
	ScenesNarrationManager(UserScenesManager* sceneManager);
	void PrintLinesFromScene();

	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine);

	UserScenesManager* GetSceneManager();

	unsigned short int GetSceneMenuLine(UserScenesManager::E_SceneSequence fromLine);
private:
	unsigned short int GetSceneTextLines(UserScenesManager::E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(UserScenesManager::E_SceneSequence fromLine);

	UserScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;

	unsigned short int m_sceneTextLines[2];
	unsigned short int m_sceneImageLines[2];
	unsigned short int m_sceneMenuLines[2];

};
