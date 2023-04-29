#include "GameTextManager.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <array>

GameTextManager::GameTextManager() :
    m_textFilePath("resouce_files/GameText.txt"), 
    m_pictureFilePath("resouce_files/GameAsciiArt.txt")
{

}

void GameTextManager::PrintLinesFromScene(E_SceneSequence scene)
{
    const unsigned short int ASCII_IMAGE_HEIGHT = 33;
    const unsigned short int STORY_TEXT_HEIGHT = 4;

    unsigned short int gameImageFirstLine = 0;
    unsigned short int gameImageLastLine = 0;
    unsigned short int gameTextFirstLine = 0;
    unsigned short int gameTextLastLine = 0;

    switch (scene)
    {
		case E_SceneSequence::INTRO:
            gameImageFirstLine = GetGameImageLines(0);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetGameTextLines(0);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;
			break;
		case E_SceneSequence::MOVING:
            gameImageFirstLine = GetGameImageLines(1);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetGameTextLines(1);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;
			break;
		default:
			break;
	}
	std::string asciiIntroPictureArt = GetTextBetweenLines(GetPictureFilePath(), gameImageFirstLine, gameImageLastLine);
	
	std::string introductionText = GetTextBetweenLines(GetTextFilePath(), gameTextFirstLine, gameTextLastLine);

	std::cout << asciiIntroPictureArt;
	std::cout << introductionText << "\n";
}

// Go to a specific lines in a file and return the text between those lines.
std::string GameTextManager::GetTextBetweenLines(std::ifstream& file, unsigned int x, unsigned int y)
{
    std::string text;
    std::string line;
    unsigned int currentLine = 1;

    // Read each line in the file until we reach the end or the desired line range.
    while (std::getline(file, line) && currentLine <= y)
    {
        // If the current line is within the desired range, add it to the output string.
        if (currentLine >= x)
        {
            text += line + "\n";
        }
        currentLine++;
    }

    // Return the output string.
    return text;
}

std::ifstream& GameTextManager::GetTextFilePath() 
{ 
    return m_textFilePath;
}

std::ifstream& GameTextManager::GetPictureFilePath()
{
    return m_pictureFilePath;
}

unsigned short int GameTextManager::GetGameTextLines(unsigned short int fromLine)
{
    return m_gameTextLines[fromLine];
}

unsigned short int GameTextManager::GetGameImageLines(unsigned short int fromLine)
{
    return m_gameImageLines[fromLine];
}
