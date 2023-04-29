
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "GameTextManager.h"


//GameTextManager::GameTextManager(MainClass* mainClassAcces, UserScenesManager* sceneManager) :
GameTextManager::GameTextManager(UserScenesManager* sceneManager) :
    m_textFilePath("resouce_files/GameText.txt"), 
    m_pictureFilePath("resouce_files/GameAsciiArt.txt"),
    m_menuFilePath("resouce_files/GameChoicesMenu.txt"),
    m_sceneTextLines{ 1, 6 },
    m_sceneImageLines{ 1, 35 },
    m_sceneMenuLines{ 1, 6 },
    m_sceneManager(sceneManager)
{

}

GameTextManager::GameTextManager()
{
}

void GameTextManager::PrintLinesFromScene()
{
    //GameChoicesMenu manageMenu;

    const unsigned short int ASCII_IMAGE_HEIGHT = 33;
    const unsigned short int STORY_TEXT_HEIGHT = 4;
    const unsigned short int MENU_TEXT_HEIGHT = 5;

    unsigned short int gameImageFirstLine = 0;
    unsigned short int gameImageLastLine = 0;
    unsigned short int gameTextFirstLine = 0;
    unsigned short int gameTextLastLine = 0;

    switch (GetSceneManager()->GetPlayerCurrentScene())
    {
		case UserScenesManager::E_SceneSequence::INTRO:
            gameImageFirstLine = GetSceneImageLines(0);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(0);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

			break;

		case UserScenesManager::E_SceneSequence::MOVING:
            gameImageFirstLine = GetSceneImageLines(1);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(1);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

			break;

		default:
			break;
	}

	std::string scenePicture = GetTextBetweenLines(GetPictureFilePath(), gameImageFirstLine, gameImageLastLine);
	std::string sceneText = GetTextBetweenLines(GetTextFilePath(), gameTextFirstLine, gameTextLastLine);
	

	std::cout << scenePicture;
	std::cout << sceneText << "\n";
	
}

// Go to a specific lines in a file and return the text between those lines.
std::string GameTextManager::GetTextBetweenLines(std::ifstream& filePath, unsigned int firstLine, unsigned int lastLine)
{
    std::string text;
    std::string line;
    unsigned int currentLine = 1;
    
    // Read each line in the file until we reach the end or the desired line range.
    while (std::getline(filePath, line) && currentLine <= lastLine)
    {
        // If the current line is within the desired range, add it to the output string.
        if (currentLine >= firstLine)
        {
            text += line + "\n";
        }
        currentLine++;
    }

    // Return the output string.
    return text;
}

std::ifstream& GameTextManager::GetPictureFilePath()
{
    return m_pictureFilePath;
}

std::ifstream& GameTextManager::GetTextFilePath()
{ 
    return m_textFilePath;
}

std::ifstream& GameTextManager::GetMenuFilePath()
{
    return m_menuFilePath;
}

unsigned short int GameTextManager::GetSceneImageLines(unsigned short int fromLine)
{
    return m_sceneImageLines[fromLine];
}

unsigned short int GameTextManager::GetSceneTextLines(unsigned short int fromLine)
{
    return m_sceneTextLines[fromLine];
}

UserScenesManager* GameTextManager::GetSceneManager()
{
	return m_sceneManager;
}