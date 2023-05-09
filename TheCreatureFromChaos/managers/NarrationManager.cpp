
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "NarrationManager.h"
#include "DebugMessageSystem.h"
#include "UserInputManager.h"

NarrationManager::NarrationManager(ScenesManager* sceneManager) :
    m_textFilePath("resouce_files/NarrationText.txt"),
    m_pictureFilePath001("resouce_files/001_ScenesArt.txt"),
    m_pictureFilePath002("resouce_files/002_ScenesArt.txt"),
    m_menuFilePath("resouce_files/MenuText.txt"),
    m_sceneManager(sceneManager),
    m_userInputManager(nullptr)
{

}

void NarrationManager::PrintLinesFromScene()
{
    E_SceneSequence scene = GetScenesManager()->GetPlayerCurrentScene();
    std::string scenePicture = "";
    std::string jumpLine = "";
    std::string sceneText = "";

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
    case E_SceneSequence::MOVING_SCENE:
    case E_SceneSequence::KOBOLD_SCENE:
    case E_SceneSequence::NAME_SCENE:
    case E_SceneSequence::ATTACK_KOBOLD_SCENE:
    case E_SceneSequence::WEAPONS_SCENE:
    case E_SceneSequence::DEAD_END_SCENE:
    case E_SceneSequence::ENNEMY_SCENE:
    case E_SceneSequence::VICTORY_SCENE:
        DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG.");
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        jumpLine = "\n";
        sceneText = GetPictureTextScene(scene, STORY_TEXT_HEIGHT);
        GetUserInputManager()->SetCurrentInputType(UserInputManager::E_CurrentInputType::DIALOGUES);
        break;

    case E_SceneSequence::ROOM_ONE_FRONT:
    case E_SceneSequence::ROOM_ONE_RIGHT:
    case E_SceneSequence::ROOM_ONE_LEFT:
    case E_SceneSequence::ROOM_ONE_BACK:
    case E_SceneSequence::ROOM_TWO_FRONT:
    case E_SceneSequence::ROOM_TWO_RIGHT:
    case E_SceneSequence::ROOM_TWO_LEFT:
    case E_SceneSequence::ROOM_TWO_BACK:
    case E_SceneSequence::ROOM_THREE_FRONT:
    case E_SceneSequence::ROOM_THREE_RIGHT:
    case E_SceneSequence::ROOM_THREE_LEFT:
    case E_SceneSequence::ROOM_THREE_BACK:
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        GetUserInputManager()->SetCurrentInputType(UserInputManager::E_CurrentInputType::NAVIGATION);
        break;

    case E_SceneSequence::COMBAT_SCENE:
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        GetUserInputManager()->SetCurrentInputType(UserInputManager::E_CurrentInputType::COMBAT);
        break;

    case E_SceneSequence::YOU_DIED_SCENE:
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        GetUserInputManager()->SetCurrentInputType(UserInputManager::E_CurrentInputType::DIALOGUES);
    default:
        // TODO : Add an error message
        break;
    }
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Print TXT-IMG for choosen scene.");
    std::cout << scenePicture;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Picture printed.");
    std::cout << jumpLine << sceneText;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Text printed.");
}

std::string NarrationManager::GetPictureTextScene(E_SceneSequence scene, const unsigned short int height)
{
    unsigned short int textFirstLine = 0;
    std::string pathToFile = "";

    if (height == ASCII_IMAGE_HEIGHT)
    {
        textFirstLine = GetSceneImageLines(scene);
        if (scene <= E_SceneSequence::ROOM_ONE_BACK)
        {
			pathToFile = GetPictureFilePath001();
		}
        else
        {
			pathToFile = GetPictureFilePath002();
		}
    }
    else if (height == STORY_TEXT_HEIGHT)
    {
        textFirstLine = GetSceneTextLines(scene);
        pathToFile = GetTextFilePath();
    }
    else
    {
        DEBUG_MSG("#R NarrationManager.cpp : GetPictureTextScene() : No text height found!");
    }

    //textLastLine = textFirstLine + height;
    std::string sceneTextOrPicture = GetTextBetweenLines(pathToFile, textFirstLine, height);

    return sceneTextOrPicture;
}

std::string NarrationManager::GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, const unsigned short int height)
{
    DEBUG_MSG("NarrationMAnager.cpp : GetTextBetweenLines() : Enters GetTextBetweenLines().");
    //std::ifstream filePath("resouce_files/ScenesAsciiArt.txt");
    std::ifstream filePath(filePathStr);
    std::string text = "";
    std::string line = "";
    unsigned int lastLine = (firstLine - 1) + height;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R NarrationMAnager.cpp : GetTextBetweenLines() : Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        unsigned int currentLine = 1;

        // Read each line in the file until we reach the end or the desired line range.
        while (std::getline(filePath, line) && currentLine <= lastLine)
        {
            //         // Debug condition, print a line :
            //         if (currentLine == firstLine + 1)
            //         {
            //             DEBUG_MSG("#Y NarrationMAnager.cpp : GetTextBetweenLines() : Debug print line : ");
            //             std::cout << (firstLine + 1) << std::endl;
            //             DEBUG_MSG("#Y NarrationMAnager.cpp : GetTextBetweenLines() : line : ");
            //             std::cout << line << std::endl << std::endl;
                     //}

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

std::string& NarrationManager::GetPictureFilePath001()
{
    return m_pictureFilePath001;
}

std::string& NarrationManager::GetPictureFilePath002()
{
    return m_pictureFilePath002;
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

ScenesManager* NarrationManager::GetScenesManager()
{
    return m_sceneManager;
}

UserInputManager* NarrationManager::GetUserInputManager()
{
	return m_userInputManager;
}

void NarrationManager::SetUserInputManager(UserInputManager* userInputManager)
{
    m_userInputManager = userInputManager;
}