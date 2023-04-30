
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "GameTextManager.h"
#include "DebugMessageSystem.h"

//GameTextManager::GameTextManager(MainClass* mainClassAcces, UserScenesManager* sceneManager) :
GameTextManager::GameTextManager(UserScenesManager* sceneManager) :
    m_textFilePath("resouce_files/GameText.txt"), 
    m_pictureFilePath("resouce_files/GameAsciiArt.txt"),
    m_sceneTextLines{ 1, 6 },
    m_sceneImageLines{ 1, 35 },
    m_sceneMenuLines{ 1, 6 },
    m_sceneManager(sceneManager)
{

}

//GameTextManager::GameTextManager()
//{
//}

void GameTextManager::PrintLinesFromScene()
{
    UserScenesManager::E_SceneSequence scene = GetSceneManager()->GetPlayerCurrentScene();
    const unsigned short int ASCII_IMAGE_HEIGHT = 33;
    const unsigned short int STORY_TEXT_HEIGHT = 4;
    const unsigned short int MENU_TEXT_HEIGHT = 5;

    unsigned short int gameImageFirstLine = 0;
    unsigned short int gameImageLastLine = 0;
    unsigned short int gameTextFirstLine = 0;
    unsigned short int gameTextLastLine = 0;

    switch (scene)
    {
		case UserScenesManager::E_SceneSequence::INTRO_SCENE:
            gameImageFirstLine = GetSceneImageLines(UserScenesManager::E_SceneSequence::INTRO_SCENE);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(UserScenesManager::E_SceneSequence::INTRO_SCENE);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

			break;

		case UserScenesManager::E_SceneSequence::MOVING_SCENE:
            gameImageFirstLine = GetSceneImageLines(UserScenesManager::E_SceneSequence::MOVING_SCENE);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(UserScenesManager::E_SceneSequence::MOVING_SCENE);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

			break;

		default:
			break;
	}

	std::string scenePicture = GetTextBetweenLines(GetPictureFilePath(), gameImageFirstLine, gameImageLastLine);
	std::string sceneText = GetTextBetweenLines(GetTextFilePath(), gameTextFirstLine, gameTextLastLine);
	

	std::cout << scenePicture;
	std::cout << sceneText;
	
}

std::string GameTextManager::GetTextBetweenLines(std::ifstream& filePath, unsigned int firstLine, unsigned int lastLine)
{
    //std::ifstream& fileInputStream = filePath;
    std::string text;
    std::string line;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("¢RERROR: Could not open the game text file.");
        exit(EXIT_FAILURE);
    }

    //unsigned int currentLine = 1;
    unsigned int currentLine = firstLine;
    
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

    // Close the file
    filePath.close();

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


unsigned short int GameTextManager::GetSceneImageLines(UserScenesManager::E_SceneSequence fromLine)
{
    return m_sceneImageLines[static_cast<int>(fromLine)];
}

unsigned short int GameTextManager::GetSceneTextLines(UserScenesManager::E_SceneSequence fromLine)
{
    return m_sceneTextLines[static_cast<int>(fromLine)];
}

UserScenesManager* GameTextManager::GetSceneManager()
{
	return m_sceneManager;
}