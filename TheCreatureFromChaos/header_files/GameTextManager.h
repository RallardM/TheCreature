#pragma once

#include <fstream>

#include "Utils.h"
#include "UserScenesManager.h"
#include "UserInputManager.h"
#include "GameChoicesMenu.h"
#include "main.h"

class GameTextManager {
public:
	//GameTextManager(MainClass* mainClassAcces, UserScenesManager* sceneManager);
	GameTextManager(UserScenesManager* sceneManager);
	//GameTextManager();
	void PrintLinesFromScene();

	std::ifstream& GetPictureFilePath();
	std::ifstream& GetTextFilePath();
	std::ifstream& GetMenuFilePath();

	unsigned short int GetSceneTextLines(UserScenesManager::E_SceneSequence fromLine);
	std::string GetTextBetweenLines(std::ifstream& file, unsigned int firstLine, unsigned int lastLine);

	UserScenesManager* GetSceneManager();

private:
	UserScenesManager* m_sceneManager;
	//MainClass* m_mainClassAcces;
	std::ifstream m_textFilePath;
	std::ifstream m_pictureFilePath;
	std::ifstream m_menuFilePath;

	unsigned short int m_sceneTextLines[2];
	unsigned short int m_sceneImageLines[2];
	unsigned short int m_sceneMenuLines[2];

	unsigned short int GetSceneImageLines(UserScenesManager::E_SceneSequence fromLine);
	std::string GetMenuAtLine(std::ifstream& filePath, unsigned int lastLine);
};
