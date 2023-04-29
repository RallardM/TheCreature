#pragma once

#include <fstream>

#include "Utils.h"
#include "UserScenesManager.h"

class GameTextManager {
public:
	GameTextManager();
	void PrintLinesFromScene(E_SceneSequence scene);
	std::ifstream& GetTextFilePath();
	std::ifstream& GetPictureFilePath();


private:
	std::string GetTextBetweenLines(std::ifstream& file, unsigned int x, unsigned int y);
	std::ifstream m_textFilePath;
	std::ifstream m_pictureFilePath;
	unsigned short int m_gameTextLines[2] = { 1, 6 };
	unsigned short int m_gameImageLines[2] = { 1, 35 };
	unsigned short int GetGameTextLines(unsigned short int fromLine);
	unsigned short int GetGameImageLines(unsigned short int fromLine);

	
};
