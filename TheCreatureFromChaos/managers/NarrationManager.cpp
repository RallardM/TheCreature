
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "NarrationManager.h"
#include "DebugMessageSystem.h"



//NarrationManager::NarrationManager(MainClass* mainClassAcces, ScenesManager* sceneManager) :
NarrationManager::NarrationManager(ScenesManager* sceneManager) :
    m_textFilePath("resouce_files/NarrationText.txt"), 
    m_pictureFilePath("resouce_files/ScenesArt.txt"),
    m_menuFilePath("resouce_files/MenuText.txt"),
    //m_sceneTextLines{ 1, 6 },
    //m_sceneImageLines{ 1, 35 },
    //m_sceneMenuLines{ 1, 6 },
    m_sceneManager(sceneManager)
{

}

//NarrationManager::NarrationManager()
//{
//}

void NarrationManager::PrintLinesFromScene()
{
    E_SceneSequence scene = GetSceneManager()->GetPlayerCurrentScene();
    const unsigned short int ASCII_IMAGE_HEIGHT = 33;
    const unsigned short int STORY_TEXT_HEIGHT = 4;
    const unsigned short int MENU_TEXT_HEIGHT = 5;

    unsigned short int gameImageFirstLine = 0;
    unsigned short int gameImageLastLine = 0;
    unsigned short int gameTextFirstLine = 0;
    unsigned short int gameTextLastLine = 0;

    switch (scene)
    {
		case E_SceneSequence::INTRO_SCENE:
            gameImageFirstLine = GetSceneImageLines(E_SceneSequence::INTRO_SCENE);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(E_SceneSequence::INTRO_SCENE);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for INTRO_SCENE.");

			break;

		case E_SceneSequence::MOVING_SCENE:
            gameImageFirstLine = GetSceneImageLines(E_SceneSequence::MOVING_SCENE);
            gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

            gameTextFirstLine = GetSceneTextLines(E_SceneSequence::MOVING_SCENE);
            gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for MOVING_SCENE.");

			break;

		default:
			break;
	}

	std::string scenePicture = GetTextBetweenLines(GetPictureFilePath(), gameImageFirstLine, gameImageLastLine);
	std::string sceneText = GetTextBetweenLines(GetTextFilePath(), gameTextFirstLine, gameTextLastLine);
	
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Print TXT-IMG for choosen scene.");
	std::cout << scenePicture;
	std::cout << sceneText;
    //GetSceneManager()->SetIsSceneCleared();
	
}

std::string NarrationManager::GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine)
{
    DEBUG_MSG("NarrationMAnager.cpp : GetTextBetweenLines() : Enters GetTextBetweenLines().");
    //std::ifstream filePath("resouce_files/ScenesAsciiArt.txt");
    std::ifstream filePath(filePathStr);
    std::string text;
    std::string line;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R NarrationMAnager.cpp : GetTextBetweenLines() : Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        //unsigned int currentLine = 1;
        unsigned int currentLine = 1;

        // Read each line in the file until we reach the end or the desired line range.
        while (std::getline(filePath, line) && currentLine <= lastLine)
        {
            // Debug condition, print a line :
            if (currentLine == firstLine + 1)
            {
                DEBUG_MSG("#Y NarrationMAnager.cpp : GetTextBetweenLines() : Debug print line : ");
                std::cout << (firstLine + 1) << std::endl;
                DEBUG_MSG("#Y NarrationMAnager.cpp : GetTextBetweenLines() : line : ");
                std::cout << line << std::endl << std::endl;
			}

            // If the current line is within the desired range, add it to the output string.
            if (currentLine >= firstLine)
            {
                text += line + "\n";
            }
            currentLine++;
        }

        // Close the file
        filePath.close();
    }

    // Return the output string.
    return text;
}

std::string& NarrationManager::GetPictureFilePath()
{
    return m_pictureFilePath;
}

std::string& NarrationManager::GetTextFilePath()
{ 
    return m_textFilePath;
}

std::string& NarrationManager::GetMenuFilePath()
{
    return m_menuFilePath;
}

unsigned short int NarrationManager::GetSceneImageLines(E_SceneSequence fromLine)
{
    return SCENES_IMAGE_LINES[static_cast<int>(fromLine)];
}

unsigned short int NarrationManager::GetSceneTextLines(E_SceneSequence fromLine)
{
    return SCENES_TEXT_LINES[static_cast<int>(fromLine)];
}

unsigned short int NarrationManager::GetSceneMenuLine(E_SceneSequence fromLine)
{
    return SCENES_MENU_LINES[static_cast<int>(fromLine)];
}

ScenesManager* NarrationManager::GetSceneManager()
{
	return m_sceneManager;
}
