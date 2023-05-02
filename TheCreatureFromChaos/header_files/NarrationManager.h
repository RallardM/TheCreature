#pragma once

#include <fstream>

#include "Utils.h"

class ScenesManager;
#include "ScenesManager.h"
#include "Globals.h"
//lass ScenesManager;


//#include "MenuManager.h" 
//#include "ScenesManager.h"

class NarrationManager{
public:
	NarrationManager(ScenesManager* sceneManager);
	void PrintLinesFromScene();

	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine);

	ScenesManager* GetSceneManager();

	unsigned short int GetSceneMenuLine(E_SceneSequence fromLine);
private:
	unsigned short int GetSceneTextLines(E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(E_SceneSequence fromLine);

	ScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;

	unsigned short int m_sceneTextLines[2];
	unsigned short int m_sceneImageLines[2];
	unsigned short int m_sceneMenuLines[2];

};
