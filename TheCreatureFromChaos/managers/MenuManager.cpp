#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>

#include "MenuManager.h"
//#include "UserInputManager.h"
//#include "NarrationManager.h"
#include "DebugMessageSystem.h"
//#include "main.h"

//MenuManager::MenuManager(MainClass* mainClassAcces, ScenesManager* sceneManager, NarrationManager* narrationManager) :
MenuManager::MenuManager(ScenesManager* sceneManager, NarrationManager* narrationManager) :
   // m_gameMenuLines{ 1, 6 },
    //m_introHighlightedMenu{ 2, 3, 4, 5 },
    //m_mainClassAccess(mainClassAcces),
    m_narrationManager(narrationManager),
    m_sceneManager(sceneManager),
    m_isMenuCleared(false)
   // m_currentPlainMenu(EMPTY_MENU_LINE),
    //m_currenSceneMenuText(EMPTY_MENU_TEXT)
{
    m_selectedMenuLine = static_cast<int>(ScenesManager::E_SceneSequence::NO_SCENE);
}

//MenuManager::MenuManager()
//{
//    MainClass* mainClass{};
//    m_narrationManager = mainClass->GetMainNarrationManager();
//    m_sceneManager = mainClass->GetMainSceneManager();
//    m_selectedMenuLine = GetSelectedMenuLine();
//}

void MenuManager::PrintMenuFromScene(UserInputManager:: E_UserInput userInput)
{
    ScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
    //short int gameMenuLine = 0;
    //short int selectedMenuLine = GetSelectedMenuLine();
    //short int startingMenuLine = GetGameMenuLine(ScenesManager::E_SceneSequence::INTRO_SCENE);
    //short int currentPlainMenu = GetCurrentPlainMenu();
    //std::string currentSceneMenuText = GetCurrentSceneMenuText();
    //std::ifstream& menuFilePath = GetMenuFilePath();

    switch (scene)
    {
    case ScenesManager::E_SceneSequence::INTRO_SCENE:
        if (userInput != UserInputManager::E_UserInput::EMPTY)
        {
            ClearConsolePreviousLine();
            if (userInput == UserInputManager::E_UserInput::LEFT)
            {
                std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), g_introHighlightedMenu[0]) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(g_introHighlightedMenu[0]);
            }
            else if (userInput == UserInputManager::E_UserInput::RIGHT)
            {
                std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), g_introHighlightedMenu[1]) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(g_introHighlightedMenu[1]);
            }
        }
        else
        {
            std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), g_introHighlightedMenu[0]) << std::endl;
        }
        break;

    case ScenesManager::E_SceneSequence::MOVING_SCENE:
        //std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), 7) << std::endl;

        break;

    default:
        break;
    }
    //std::string newCurrentSceneMenuText = GetMenuAtLine(m_narrationManager->GetMenuFilePath(), gameMenuLine);
    //std::cout << newCurrentSceneMenuText << std::endl;
    //std::cout << GetCurrentSceneMenuText();
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

std::string MenuManager::GetMenuAtLine(std::string& filePathStr, unsigned short int atLine)
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

//std::string MenuManager::GetCurrentSceneMenuText()
//{
//	return m_currenSceneMenuText;
//}

//void MenuManager::SetCurrentSceneMenuText(std::string sceneMenu)
//{
//    m_currenSceneMenuText = sceneMenu;
//}

//unsigned short int MenuManager::GetGameMenuLine(ScenesManager::E_SceneSequence atLine)
//{
//	return m_gameMenuLines[static_cast<int>(atLine)];
//}

//ScenesManager* MenuManager::GetSceneManager()
//{
//    return m_narrationManager;
//}
//
//NarrationManager* MenuManager::GetGameTextManager()
//{
//	return m_narrationManager;
//}

unsigned short int MenuManager::GetSelectedMenuLine()
{
    return m_selectedMenuLine;
}

void MenuManager::SetSelectedMenuLine(unsigned short int selectedMenuLine)
{
    m_selectedMenuLine = selectedMenuLine;
}

//void MenuManager::SetCurrentPlainMenu(short int currentPlainMenu)
//{
//    m_currentPlainMenu = currentPlainMenu;
//}

//short int MenuManager::GetCurrentPlainMenu()
//{
//    return m_currentPlainMenu;
//}

void MenuManager::ClearConsolePreviousLine()
{
    std::cout << "\033[1A\033[0K";
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