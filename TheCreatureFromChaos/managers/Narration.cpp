
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "Narration.h"
#include "DebugMessageSystem.h"
//#include "UserInputManager.h"

Narration::Narration() :
    m_gameplayManager(nullptr),
    m_consoleHandler(nullptr),
    m_textFilePath("resouce_files/NarrationText.txt"),
    m_pictureFilePath("resouce_files/ScenesArt.txt"),
    m_menuFilePath("resouce_files/MenuText.txt")//,
   // m_sceneManager(sceneManager),
   // m_userInputManager(nullptr)
{

}

void Narration::PrintLinesFromScene()
{
    E_SceneSequence scene = GetGameplayManager()->GetScenes()->GetPlayerCurrentScene();
    std::string scenePicture = "";
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
        DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG.");
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        sceneText = GetPictureTextScene(scene, STORY_TEXT_HEIGHT);
        GetConsoleHandler()->GetUserInput()->SetCurrentInputType(UserInput::E_CurrentInputType::DIALOGUES);
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
        GetConsoleHandler()->GetUserInput()->SetCurrentInputType(UserInput::E_CurrentInputType::NAVIGATION);
        break;
    case E_SceneSequence::COMBAT_SCENE:
        scenePicture = GetPictureTextScene(scene, ASCII_IMAGE_HEIGHT);
        GetConsoleHandler()->GetUserInput()->SetCurrentInputType(UserInput::E_CurrentInputType::COMBAT);
        break;

    default:
        break;
    }
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Print TXT-IMG for choosen scene.");
    std::cout << scenePicture;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Picture printed.");
    std::cout << sceneText;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Text printed.");
}

std::string Narration::GetPictureTextScene(E_SceneSequence scene, const unsigned short int height)
{
    unsigned short int textFirstLine = 0;
    std::string pathToFile = "";

    if (height == ASCII_IMAGE_HEIGHT)
    {
        textFirstLine = GetSceneImageLines(scene);
        pathToFile = GetPictureFilePath();
    }
    else if (height == STORY_TEXT_HEIGHT)
    {
        textFirstLine = GetSceneTextLines(scene);
        pathToFile = GetTextFilePath();
    }
    else
    {
        DEBUG_MSG("#R Narration.cpp : GetPictureTextScene() : No text height found!");
    }

    //textLastLine = textFirstLine + height;
    std::string sceneTextOrPicture = GetTextBetweenLines(pathToFile, textFirstLine, height);

    return sceneTextOrPicture;
}

std::string Narration::GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, const unsigned short int height)
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

std::string& Narration::GetPictureFilePath()
{
    return m_pictureFilePath;
}

std::string& Narration::GetTextFilePath()
{
    return m_textFilePath;
}

std::string& Narration::GetMenuFilePath()
{
    return m_menuFilePath;
}

unsigned short int Narration::GetSceneImageLines(E_SceneSequence fromLine)
{
    return SCENES_IMAGE_LINES[static_cast<int>(fromLine)];
}

unsigned short int Narration::GetSceneTextLines(E_SceneSequence fromLine)
{
    return SCENES_TEXT_LINES[static_cast<int>(fromLine)];
}

//Scenes* Narration::GetScenesManager()
//{
//    return m_sceneManager;
//}
//
//UserInput* Narration::GetUserInputManager()
//{
//	return m_userInputManager;
//}
//
//void Narration::SetUserInputManager(UserInput* userInputManager)
//{
//    m_userInputManager = userInputManager;
//}


GameplayManager* Narration::GetGameplayManager()
{
    return m_gameplayManager;
}

void Narration::SetGameplayManager(GameplayManager* gameplayManager)
{
    m_gameplayManager = gameplayManager;
}

ConsoleHandler* Narration::GetConsoleHandler()
{
    return m_consoleHandler;
}

void Narration::SetConsoleHandler(ConsoleHandler* consoleHandler)
{
    m_consoleHandler = consoleHandler;
}
