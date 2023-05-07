#pragma once

#include <fstream>

class ScenesManager;

#include "ScenesManager.h"
#include "PublicConstants.h"
#include "ScenesConstants.h"

using namespace PublicConstants;
using namespace ScenesConstants;

class NarrationManager{
public:

	NarrationManager(ScenesManager* sceneManager);
	void PrintLinesFromScene();
	std::string GetPictureTextScene(E_SceneSequence scene, const unsigned short int height);
	std::string& GetPictureFilePath();
	std::string& GetTextFilePath();
	std::string& GetMenuFilePath();
	std::string GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, const unsigned short int height);

	ScenesManager* GetScenesManager();

	const unsigned short int ASCII_IMAGE_HEIGHT     = 34;
	const unsigned short int NAVIGATION_MENU_HEIGHT =  7;
	const unsigned short int STORY_TEXT_HEIGHT      =  5;
	const unsigned short int NARRATION_MENU_HEIGHT  =  1;

private:
	unsigned short int GetSceneTextLines(E_SceneSequence fromLine);
	unsigned short int GetSceneImageLines(E_SceneSequence fromLine);

	ScenesManager* m_sceneManager;

	std::string m_textFilePath;
	std::string m_pictureFilePath;
	std::string m_menuFilePath;
};