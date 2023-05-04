#pragma once

#include <fstream>

//#include "ConsoleHandler.h"

class ScenesManager;
#include "ScenesManager.h"

#include "ScenesControllers.h"
using namespace ScenesControllers;

class NarrationManager{
public:

	NarrationManager(ScenesManager* sceneManager);
	void PrintLinesFromScene();
	std::string GetPictureTextScene(E_SceneSequence scene, const unsigned short int height);
	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine);

	ScenesManager* GetScenesManager();

	const unsigned short int ASCII_IMAGE_HEIGHT = 33;
	const unsigned short int STORY_TEXT_HEIGHT = 5;

private:
	unsigned short int GetSceneTextLines(E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(E_SceneSequence fromLine);

	ScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;


};
