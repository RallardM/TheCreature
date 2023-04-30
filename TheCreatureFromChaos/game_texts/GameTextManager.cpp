
#include <iostream>
#include <fstream>
#include <filesystem>
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

//GameTextManager::GameTextManager()
//{
//}

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

//// Go to a specific lines in a file and return the text between those lines.
//std::string GameTextManager::GetTextBetweenLines(std::ifstream& filePath, unsigned int firstLine, unsigned int lastLine)
//{
//    std::string text;
//    std::string line;
//
//    // If the firstLine and lastLine are the same, return just that line.
//    if (firstLine == lastLine && firstLine > 0) 
//    {
//        // Move to the desired line
//        for (unsigned int i = 1; i < firstLine; ++i) 
//        {
//            std::getline(filePath, line);
//        }
//        // Get the desired line
//        std::getline(filePath, line);
//        // Add the line to the output string
//        text += line;
//    }
//    else if (lastLine > 0 && firstLine <= lastLine) 
//    {
//        // Move to the first desired line
//        for (unsigned int i = 1; i < firstLine; ++i) 
//        {
//            std::getline(filePath, line);
//        }
//        // Read each line in the desired range and add it to the output string
//        unsigned int currentLine = firstLine;
//        while (std::getline(filePath, line) && currentLine <= lastLine) 
//        {
//            text += line;
//            if (currentLine < lastLine) 
//            {
//                text += "\n"; // Only add a newline if it's not the last line
//            }
//            currentLine++;
//        }
//    }
//
//    // Return the output string.
//    return text;
//}

std::string GameTextManager::GetTextBetweenLines(std::ifstream& filePath, unsigned int firstLine, unsigned int lastLine)
{
    std::string text;
    std::string line;
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

    // Return the output string.
    return text;
}

std::string GetFileContents(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();

    return buffer.str();
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