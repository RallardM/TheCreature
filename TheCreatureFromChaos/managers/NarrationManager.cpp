
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <sstream>
#include <string>
#include <array>

#include "NarrationManager.h"
#include "DebugMessageSystem.h"

NarrationManager::NarrationManager(ScenesManager* sceneManager) :
    m_textFilePath("resouce_files/NarrationText.txt"), 
    m_pictureFilePath("resouce_files/ScenesArt.txt"),
    m_menuFilePath("resouce_files/MenuText.txt"),
    m_sceneManager(sceneManager)
{

}

void NarrationManager::PrintLinesFromScene()
{
    E_SceneSequence scene = GetScenesManager()->GetPlayerCurrentScene();
    std::string scenePicture = "";
    std::string sceneText = "";

    switch (scene)
    {
		case E_SceneSequence::INTRO_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for INTRO_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::INTRO_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::INTRO_SCENE, STORY_TEXT_HEIGHT);
			break;

		case E_SceneSequence::MOVING_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for MOVING_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::MOVING_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::MOVING_SCENE, STORY_TEXT_HEIGHT);
			break;

        case E_SceneSequence::KOBOLD_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for KOBOLD_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::KOBOLD_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::KOBOLD_SCENE, STORY_TEXT_HEIGHT);
            break;

        case E_SceneSequence::NAME_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for NAME_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::NAME_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::NAME_SCENE, STORY_TEXT_HEIGHT);
            break;

        case E_SceneSequence::ATTACK_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for ATTACK_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::ATTACK_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::ATTACK_SCENE, STORY_TEXT_HEIGHT);
            break;

        case E_SceneSequence::WEAPONS_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for WEAPONS_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::WEAPONS_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::WEAPONS_SCENE, STORY_TEXT_HEIGHT);
            break;

        case E_SceneSequence::DEAD_END_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for DEAD_END_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::DEAD_END_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::DEAD_END_SCENE, STORY_TEXT_HEIGHT);
            break;

        case E_SceneSequence::ENNEMY_SCENE:
            DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Prepare TXT-IMG for ENNEMY_SCENE.");
            scenePicture = GetPictureTextScene(E_SceneSequence::ENNEMY_SCENE, ASCII_IMAGE_HEIGHT);
            sceneText = GetPictureTextScene(E_SceneSequence::ENNEMY_SCENE, STORY_TEXT_HEIGHT);
            break;

		default:
			break;
	}
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Print TXT-IMG for choosen scene.");
	std::cout << scenePicture;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Picture printed.");
	std::cout << sceneText;
    DEBUG_MSG("NarrationMAnager.cpp : PrintLinesFromScene() : Text printed.");

    //GetScenesManager()->SetIsSceneCleared();
}

std::string NarrationManager::GetPictureTextScene(E_SceneSequence scene, const unsigned short int height)
{
    
    unsigned short int textFirstLine = 0;
    unsigned short int textLastLine = 0;
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
        DEBUG_MSG("#R NarrationManager.cpp : GetPictureTextScene() : No text height found!");
	}
    
    textLastLine = textFirstLine + height;
    std::string sceneTextOrPicture = GetTextBetweenLines(pathToFile, textFirstLine, textLastLine);

    return sceneTextOrPicture;
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

ScenesManager* NarrationManager::GetScenesManager()
{
	return m_sceneManager;
}
