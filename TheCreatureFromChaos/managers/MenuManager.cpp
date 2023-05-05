#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>
#include <chrono>

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
        PrintSingleMenuChoice(userInput, E_MenuChoices::TAKE_WEAPONS);
        break;

    case E_SceneSequence::DEAD_END_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::GO_BACK);
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
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Prints 4-ways navigation system");
        SelectFourWaysNavigation(userInput, E_MenuChoices::NAVIGATION_PLAIN);
        break;

    case E_SceneSequence::ROOM_ONE_RIGHT:
    case E_SceneSequence::ROOM_ONE_LEFT:
    case E_SceneSequence::ROOM_TWO_RIGHT:
    case E_SceneSequence::ROOM_TWO_LEFT:
    case E_SceneSequence::ROOM_THREE_RIGHT:
    case E_SceneSequence::ROOM_THREE_LEFT:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Prints 2-ways navigation system");
        SelectTwoWaysNavigation(userInput, E_MenuChoices::LR_NAVIGATION_PLAIN);
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
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : UserInput is EMPTY.");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }

    ClearConsolePreviousLine();
    SetIsMenuCleared(true);
    if (userInput == E_UserInput::LEFT && GetSelectedMenuLine() != LeftMenuChoice)
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print LeftMenuChoice");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }
    else if (userInput == E_UserInput::RIGHT && GetSelectedMenuLine() != rightMenuChoice)
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print rightMenuChoice");
        PrintSelectedMenu(rightMenuChoice);
        return;
    }
}

void MenuManager::SelectFourWaysNavigation(E_UserInput userInput, E_MenuChoices menuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : PrintSingleMenuChoice() : UserInput is EMPTY");
        PrintSelectedMenu(menuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT)
    {
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + NEXT_NAVIGATION_ELEMENT);
        PrintSelectedMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }
    else if (userInput == E_UserInput::RIGHT)
    {
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + (NEXT_NAVIGATION_ELEMENT * JUMP_TWO_MENU_ELEMENTS));
        PrintSelectedMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }
    else if (userInput == E_UserInput::UP)
    {
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + (NEXT_NAVIGATION_ELEMENT * JUMP_THREE_MENU_ELEMENTS));
        PrintSelectedMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }
    else if (userInput == E_UserInput::DOWN)
    {
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + (NEXT_NAVIGATION_ELEMENT * JUMP_FOUR_MENU_ELEMENTS));
        PrintSelectedMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }
    return;
}

void MenuManager::SelectTwoWaysNavigation(E_UserInput userInput, E_MenuChoices menuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : PrintSingleMenuChoice() : UserInput is EMPTY");
        ClearConsolePreviousLine();
        PrintNavigationMenu(menuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT)
    {
        //ClearConsolePreviousLine();
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + NEXT_NAVIGATION_ELEMENT);
        PrintNavigationMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }
    else if (userInput == E_UserInput::RIGHT)
    {
        //ClearConsolePreviousLine();
        ClearConsoleNavigationMenu();
        SetIsMenuCleared(true);
        int myInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(myInt + (NEXT_NAVIGATION_ELEMENT * JUMP_TWO_MENU_ELEMENTS));
        PrintNavigationMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }

    return;
}


void MenuManager::PrintSingleMenuChoice(E_UserInput userInput, E_MenuChoices menuChoice)
{

    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : PrintSingleMenuChoice() : UserInput is EMPTY");
        PrintSelectedMenu(menuChoice);
        return;
    }
    
    if (userInput == E_UserInput::ENTER)
    {
        ClearConsolePreviousLine();
        SetIsMenuCleared(true);
        int enumToInt = static_cast<int>(menuChoice);
        E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(enumToInt + NEXT_MENU_ELEMENT);
        PrintSelectedMenu(nextMenuInEnum);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return;
    }

    return;
}

void MenuManager::PrintSelectedMenu(E_MenuChoices currentMenuChoice)
{
    
    std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), currentMenuChoice) << std::endl;
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentMenuChoice);
    return;
}

void MenuManager::PrintNavigationMenu(E_MenuChoices currentNavigationChoice)
{
    unsigned int enumToInt = static_cast<unsigned int>(currentNavigationChoice);
    std::string& menuFilePath = GetNarrationManager()->GetMenuFilePath();
    std::string navigationMenuText = GetNarrationManager()->GetTextBetweenLines(menuFilePath, enumToInt, NAVIGATION_MENU_HEIGHT);
    std::cout << navigationMenuText;
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentNavigationChoice);
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
}

void MenuManager::ClearConsoleNavigationMenu()
{
    DEBUG_MSG("#Y MenuManager.cpp : ClearConsolePreviousLine() : Clear navigation menu");
    for (size_t i = 0; i < NAVIGATION_MENU_HEIGHT; i++)
    {
        ClearConsolePreviousLine();
    }
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