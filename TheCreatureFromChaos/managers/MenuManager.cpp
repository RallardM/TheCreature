#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>

#include "MenuManager.h"
#include "DebugMessageSystem.h"

MenuManager::MenuManager(ConsoleHandler* consoleHandler, ScenesManager* scenesManager, NarrationManager* narrationManager, UserData* userData) :
    m_consoleHandler(consoleHandler),
    m_narrationManager(narrationManager),
    m_scenesManager(scenesManager),
    m_userData(userData),
    m_isMenuCleared(true)
{
    m_selectedMenuLine = E_MenuChoices::NO_MENU_LINE;
}

void MenuManager::PrintMenuFromScene(E_UserInput userInput)
{
    E_SceneSequence scene = GetScenesManager()->GetPlayerCurrentScene();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : INTRO_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::TRY_TO_MOVE, E_MenuChoices::TRY_TO_REMEBER);
        break;

    case E_SceneSequence::MOVING_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : MOVING_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::LOOK_AROUND, E_MenuChoices::TRY_TO_REMEBER_TWO);
        break;

    case E_SceneSequence::KOBOLD_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::WHO_ARE_YOU, E_MenuChoices::ATTACK_KOBOLD);
        break;

    case E_SceneSequence::NAME_SCENE:
    case E_SceneSequence::ATTACK_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : NAME_SCENE, ATTACK_SCENE");
        PrintEnterNameMenu();
        break;

    case E_SceneSequence::WEAPONS_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : WEAPONS_SCENE TODO");
        //SelectMenuChoice(userInput, E_MenuChoices::GO_BACK, E_MenuChoices::GO_BACK);
        break;

    case E_SceneSequence::DEAD_END_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::GO_BACK, E_MenuChoices::GO_BACK);
        break;

    case E_SceneSequence::ENNEMY_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::ATTACK_ENEMY, E_MenuChoices::RUN_AWAY);
        break;
    
    case E_SceneSequence::ROOM_ONE_FRONT:
    case E_SceneSequence::ROOM_ONE_BACK:
    case E_SceneSequence::ROOM_TWO_FRONT:
    case E_SceneSequence::ROOM_TWO_BACK:
    case E_SceneSequence::ROOM_THREE_FRONT:
    case E_SceneSequence::ROOM_THREE_BACK:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : TODO Front back rooms navigation system");
        break;

    case E_SceneSequence::ROOM_ONE_RIGHT:
    case E_SceneSequence::ROOM_ONE_LEFT:
    case E_SceneSequence::ROOM_TWO_RIGHT:
    case E_SceneSequence::ROOM_TWO_LEFT:
    case E_SceneSequence::ROOM_THREE_RIGHT:
    case E_SceneSequence::ROOM_THREE_LEFT:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : TODO Left right rooms navigation system");
        break;

    default:
        DEBUG_MSG("#R MenuManager.cpp : PrintMenuFromScene() : Default no menu selected");
        break;
    }
}

void MenuManager::SelectMenuChoice(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : UserInput is EMPTY Print TRY_TO_MOVE menu");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }

    ClearConsolePreviousLine();
    if (userInput == E_UserInput::LEFT && GetSelectedMenuLine() != LeftMenuChoice)
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print LeftMenuChoice");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }
    else if (userInput == E_UserInput::RIGHT && GetSelectedMenuLine() != rightMenuChoice)
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print DO_NOTHING menu");
        PrintSelectedMenu(rightMenuChoice);
        return;
    }
}

void MenuManager::PrintSelectedMenu(E_MenuChoices currentMenuChoice)
{
    
    std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), currentMenuChoice) << std::endl;
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentMenuChoice);
    return;
}

void MenuManager::PrintEnterNameMenu()
{
    std::cout << "            What name do you want Khai to call you? ";
    std::string playerName;
    GetConsoleHandler()->ActivateConsoleCursor();
    //GetConsoleHandler()->SetIsUserPrompted(true);
    std::cin >> playerName;
    //GetConsoleHandler()->SetIsUserPrompted(false);
    GetConsoleHandler()->DisableConsoleCursor();
    GetUserData()->SetPlayerName(playerName);
    SetIsMenuCleared(false);
    GetScenesManager()->SetNextScene(E_MenuChoices::ENTER_NAME);
    return;
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
        DEBUG_MSG("#R MenuManager.cpp : GetMenuAtLine() : ERROR: Could not open the game text file.");
        std::cout << "MenuManager.cpp : GetMenuAtLine() : ERROR Could not open the game text file." << std::endl;
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

E_MenuChoices MenuManager::GetSelectedMenuLine()
{
    DEBUG_MSG("#C MenuManager.cpp : GetSelectedMenuLine() : ");
    //std::cout << int(m_selectedMenuLine) << std::endl; // Debug line
    return m_selectedMenuLine;
}

void MenuManager::SetSelectedMenuLine(E_MenuChoices selectedMenuLine)
{
    DEBUG_MSG("#C MenuManager.cpp : SetSelectedMenuLine() : ");
    //std::cout << int(selectedMenuLine) << std::endl; // Debug line
    m_selectedMenuLine = selectedMenuLine;
}

void MenuManager::ClearConsolePreviousLine()
{
    DEBUG_MSG("#Y MenuManager.cpp : ClearConsolePreviousLine() : Clear previous line debug deactivated");
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

ConsoleHandler* MenuManager::GetConsoleHandler()
{
    return m_consoleHandler;
}

NarrationManager* MenuManager::GetNarrationManager()
{
    return m_narrationManager;
}

ScenesManager* MenuManager::GetScenesManager()
{
	return m_scenesManager;
}

UserData* MenuManager::GetUserData()
{
    return m_userData;
}