#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>

#include "MenuManager.h"
#include "DebugMessageSystem.h"

MenuManager::MenuManager(ScenesManager* sceneManager, NarrationManager* narrationManager) :
    m_narrationManager(narrationManager),
    m_sceneManager(sceneManager),
    m_isMenuCleared(true)//,
   // m_inputManager(nullptr)
{
    m_selectedMenuLine = E_MenuChoices::NO_MENU_LINE;
}


void MenuManager::PrintMenuFromScene(E_UserInput userInput)
{
    //E_UserInput userInput = GetUserInputManager()->GetInput();
    E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        if (userInput != E_UserInput::EMPTY)
        {
            ClearConsolePreviousLine();
            if (userInput == E_UserInput::LEFT)
            {
                DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print TRY_TO_MOVE menu");
                std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::TRY_TO_MOVE) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(E_MenuChoices::TRY_TO_MOVE);
                break;
            }
            else if (userInput == E_UserInput::RIGHT)
            {
                DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print DO_NOTHING menu");
                std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::DO_NOTHING) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(E_MenuChoices::DO_NOTHING);
                break;
            }
        }
        else
        {
            DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : UserInput is EMPTY Print TRY_TO_MOVE menu");
            std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::TRY_TO_MOVE) << std::endl;
            SetIsMenuCleared(false);
            SetSelectedMenuLine(E_MenuChoices::TRY_TO_MOVE);
            break;
        }
        break;

    case E_SceneSequence::MOVING_SCENE:
        DEBUG_MSG("#R MOVING_SCENE");
        break;

    default:
        DEBUG_MSG("#R MenuManager.cpp : PrintMenuFromScene() : Default no menu selected");
        break;
    }
}

std::string MenuManager::GetLastLineInConsole()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);

    COORD position;
    position.X = 0;
    position.Y = screenBufferInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(consoleHandle, position);

    std::string lastLine;
    if (screenBufferInfo.dwCursorPosition.X == 0) 
    {
        return "";
    }

    getline(std::cin, lastLine);

    return lastLine;
}

std::string MenuManager::GetMenuAtLine(std::string& filePathStr, E_MenuChoices atLine)
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
            if (currentLine == static_cast<unsigned short int>(atLine))
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

NarrationManager* MenuManager::GetNarrationManager()
{
	return m_narrationManager;
}

E_MenuChoices MenuManager::GetSelectedMenuLine()
{
    DEBUG_MSG("#C MenuManager.cpp : GetSelectedMenuLine() : ");
    std::cout << int(m_selectedMenuLine) << std::endl;
    return m_selectedMenuLine;
}

void MenuManager::SetSelectedMenuLine(E_MenuChoices selectedMenuLine)
{
    DEBUG_MSG("#C MenuManager.cpp : SetSelectedMenuLine() : ");
    std::cout << int(selectedMenuLine) << std::endl;
    m_selectedMenuLine = selectedMenuLine;
}

void MenuManager::ClearConsolePreviousLine()
{
    DEBUG_MSG("#Y MenuManager.cpp : ClearConsolePreviousLine() : Clear previous line debug deactivated");
    //std::cout << "\033[1A\033[0K";
    SetIsMenuCleared(true);
}

bool MenuManager::GetIsMenuCleared()
{
    return m_isMenuCleared;
}

void MenuManager::SetIsMenuCleared(bool isMenuCleared)
{
    m_isMenuCleared = isMenuCleared;
}

//UserInputManager* MenuManager::GetUserInputManager()
//{
//	return m_inputManager;
//}
//
//void MenuManager::SetUserInputManager(UserInputManager* inputManager)
//{
//    m_inputManager = inputManager;
//}