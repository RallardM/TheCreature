#pragma once

#include <fstream>

#include "Utils.h"
#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "ScenesMenuManager.h"
#include "main.h"

class ScenesNarrationManager {
public:
	ScenesNarrationManager(UserScenesManager* sceneManager);
	void PrintLinesFromScene();

	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();

	unsigned short int GetSceneTextLines(UserScenesManager::E_SceneSequence fromLine);
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine);

	UserScenesManager* GetSceneManager();

private:
	UserScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;

	unsigned short int m_sceneTextLines[2];
	unsigned short int m_sceneImageLines[2];
	unsigned short int m_sceneMenuLines[2];

	unsigned short int GetSceneImageLines(UserScenesManager::E_SceneSequence fromLine);

};
