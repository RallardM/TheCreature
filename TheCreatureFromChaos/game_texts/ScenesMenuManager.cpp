#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>

#include "ScenesMenuManager.h"
//#include "UserInputManager.h"
//#include "ScenesNarrationManager.h"
#include "DebugMessageSystem.h"

ScenesMenuManager::ScenesMenuManager(MainClass* mainClassAcces, UserScenesManager* sceneManager, ScenesNarrationManager* narrationManager) :
    m_gameMenuLines{ 1, 6 },
    m_introHighlightedMenu{ 2, 3 },
    m_mainClassAccess(mainClassAcces),
    m_narrationManager(narrationManager),
    m_sceneManager(sceneManager),
    m_currentPlainMenu(EMPTY_MENU_LINE),
    m_currenSceneMenuText(EMPTY_MENU_TEXT)
{
    m_selectedMenuLine = static_cast<int>(UserScenesManager::E_SceneSequence::NO_SCENE);
}

ScenesMenuManager::ScenesMenuManager()
{
}

void ScenesMenuManager::PrintMenuFromScene(UserInputManager:: E_UserInput userInput)
{
    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
    //short int gameMenuLine = 0;
    //short int selectedMenuLine = GetSelectedMenuLine();
    //short int startingMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
    //short int currentPlainMenu = GetCurrentPlainMenu();
    //std::string currentSceneMenuText = GetCurrentSceneMenuText();
    //std::ifstream& menuFilePath = GetMenuFilePath();

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
        if (userInput != UserInputManager::E_UserInput::EMPTY)
        {
            ClearConsolePreviousLine();
            if (userInput == UserInputManager::E_UserInput::LEFT)
            {
                std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), m_introHighlightedMenu[0]) << std::endl;
            }
            else if (userInput == UserInputManager::E_UserInput::RIGHT)
            {
                std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), m_introHighlightedMenu[1]) << std::endl;
            }
        }
        else
        {
            std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), m_introHighlightedMenu[0]) << std::endl;
        }
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:
        //std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), 7) << std::endl;

        break;

    default:
        break;
    }
    //std::string newCurrentSceneMenuText = GetMenuAtLine(m_narrationManager->GetMenuFilePath(), gameMenuLine);
    //std::cout << newCurrentSceneMenuText << std::endl;
    //std::cout << GetCurrentSceneMenuText();
}

std::string ScenesMenuManager::GetLastLineInConsole()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);

    COORD position;
    position.X = 0;
    position.Y = screenBufferInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(consoleHandle, position);

    std::string lastLine;
   // DEBUG_MSG("#R Last line:");
    //std::cout << "\n" << lastLine << std::endl;
    //DEBUG_MSG("#R :Last line");

    // Check if the last line is empty
    if (screenBufferInfo.dwCursorPosition.X == 0) 
    {
        return "";
    }

    getline(std::cin, lastLine);

    return lastLine;
}

std::string ScenesMenuManager::GetMenuAtLine(std::string& filePathStr, unsigned short int atLine)
{
    std::ifstream filePath(filePathStr);
    std::string text;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R ERROR: Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::string line;
        unsigned short int currentLine = 0;

        // Read the file line by line
        while (getline(filePath, line))
        {
            // Increment the current line number
            currentLine++;

            // If the current line number matches the specified line number, 
            // store the line in the output string and break out of the loop
            if (currentLine == atLine)
            {
                text = line;
                break;
            }
        }

        // Close the file
        filePath.close();
    }

    // Return the output string.
    return text;
}

std::string ScenesMenuManager::GetCurrentSceneMenuText()
{
	return m_currenSceneMenuText;
}

void ScenesMenuManager::SetCurrentSceneMenuText(std::string sceneMenu)
{
    m_currenSceneMenuText = sceneMenu;
}

unsigned short int ScenesMenuManager::GetGameMenuLine(UserScenesManager::E_SceneSequence atLine)
{
	return m_gameMenuLines[static_cast<int>(atLine)];
}

//UserScenesManager* ScenesMenuManager::GetSceneManager()
//{
//    return m_narrationManager;
//}
//
//ScenesNarrationManager* ScenesMenuManager::GetGameTextManager()
//{
//	return m_narrationManager;
//}

unsigned short int ScenesMenuManager::GetSelectedMenuLine()
{
    return m_selectedMenuLine;
}

void ScenesMenuManager::SetSelectedMenuLine(unsigned short int selectedMenuLine)
{
    m_selectedMenuLine = selectedMenuLine;
}

void ScenesMenuManager::SetCurrentPlainMenu(short int currentPlainMenu)
{
    m_currentPlainMenu = currentPlainMenu;
}

short int ScenesMenuManager::GetCurrentPlainMenu()
{
    return m_currentPlainMenu;
}

void ScenesMenuManager::ClearConsolePreviousLine()
{
    std::cout << "\033[1A\033[0K";
}