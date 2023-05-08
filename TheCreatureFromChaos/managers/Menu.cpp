#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <array>
#include <chrono>

#include "Menu.h"
#include "DebugMessageSystem.h"

Menu::Menu(Scenes* scenes) :
    m_userData(nullptr),
    m_outputManager(nullptr),
    m_scenes(scenes),
   // m_gameplayManager(gameplayManager),
    m_consoleHandler(nullptr),
    m_isMenuCleared(true)
{
    m_selectedMenuLine = E_MenuChoices::NO_MENU_LINE;
}

void Menu::SelectMenuFromScene(E_UserInput userInput)
{
    E_SceneSequence scene = GetScenes()->GetPlayerCurrentScene();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : INTRO_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::TRY_TO_MOVE, E_MenuChoices::TRY_TO_REMEBER);
        break;

    case E_SceneSequence::MOVING_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : MOVING_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::LOOK_AROUND, E_MenuChoices::TRY_TO_REMEBER_TWO);
        break;

    case E_SceneSequence::KOBOLD_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::WHO_ARE_YOU, E_MenuChoices::ATTACK_KOBOLD);
        break;

    case E_SceneSequence::NAME_SCENE:
    case E_SceneSequence::ATTACK_KOBOLD_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : NAME_SCENE, ATTACK_KOBOLD_SCENE");
        PrintEnterNameMenu();
        break;

    case E_SceneSequence::WEAPONS_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : WEAPONS_SCENE TODO");
        PrintSingleMenuChoice(userInput, E_MenuChoices::TAKE_WEAPONS);
        break;

    case E_SceneSequence::DEAD_END_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : KOBOLD_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::GO_BACK);
        break;

    case E_SceneSequence::ENNEMY_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::ATTACK_ENEMY, E_MenuChoices::RUN_AWAY);
        break;

    case E_SceneSequence::ROOM_ONE_FRONT:
    case E_SceneSequence::ROOM_ONE_BACK:
    case E_SceneSequence::ROOM_TWO_FRONT:
    case E_SceneSequence::ROOM_TWO_BACK:
    case E_SceneSequence::ROOM_THREE_FRONT:
    case E_SceneSequence::ROOM_THREE_BACK:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : Prints 4-ways navigation system");
        SelectNavigationElement(userInput, E_MenuChoices::NAVIGATION_PLAIN);
        break;
    case E_SceneSequence::ROOM_ONE_RIGHT:
    case E_SceneSequence::ROOM_ONE_LEFT:
    case E_SceneSequence::ROOM_TWO_RIGHT:
    case E_SceneSequence::ROOM_TWO_LEFT:
    case E_SceneSequence::ROOM_THREE_RIGHT:
    case E_SceneSequence::ROOM_THREE_LEFT:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : Prints 2-ways navigation system");
        SelectNavigationElement(userInput, E_MenuChoices::LR_NAVIGATION_PLAIN);
        break;

    case E_SceneSequence::COMBAT_SCENE:
        DEBUG_MSG("Menu.cpp : SelectMenuFromScene() : COMBAT_SCENE");
        SelectCombatChoice(userInput, E_MenuChoices::COMBAT_PLAIN);
        break;

    default:
        DEBUG_MSG("#R Menu.cpp : SelectMenuFromScene() : Default no menu selected");
        break;
    }
}

void Menu::SelectMenuChoice(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("Menu.cpp : SelectMenuChoice() : UserInput is EMPTY.");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }

    ClearConsolePreviousLine();
    SetIsMenuCleared(true);
    if (userInput == E_UserInput::LEFT && GetSelectedMenuLine() != LeftMenuChoice)
    {
        DEBUG_MSG("Menu.cpp : SelectMenuChoice() : Print LeftMenuChoice");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }
    else if (userInput == E_UserInput::RIGHT && GetSelectedMenuLine() != rightMenuChoice)
    {
        DEBUG_MSG("Menu.cpp : SelectMenuChoice() : Print rightMenuChoice");
        PrintSelectedMenu(rightMenuChoice);
        return;
    }
}

void Menu::SelectNavigationElement(E_UserInput userInput, E_MenuChoices menuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("Menu.cpp : SelectNavigationElement() : UserInput is EMPTY");
        ClearConsolePreviousLine();
        PrintNavigationMenu(menuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT)
    {
        PrepareNavigationMenu(menuChoice, CURRENT_MENU_ELEMENT);
        return;
    }
    else if (userInput == E_UserInput::RIGHT)
    {
        PrepareNavigationMenu(menuChoice, NEXT_TWO_MENU_ELEMENTS);
        return;
    }
    else if (userInput == E_UserInput::UP)
    {
        PrepareNavigationMenu(menuChoice, NEXT_THREE_MENU_ELEMENTS);
        return;
    }
    else if (userInput == E_UserInput::DOWN)
    {
        PrepareNavigationMenu(menuChoice, NEXT_FOUR_MENU_ELEMENTS);
        return;
    }
    return;
}

void Menu::SelectCombatChoice(E_UserInput userInput, E_MenuChoices menuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("Menu.cpp : SelectCombatChoice() : UserInput is EMPTY");
        ClearConsolePreviousLine();
        PrintNavigationMenu(menuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT) // Khai Help
    {
        PrepareNavigationMenu(menuChoice, CURRENT_MENU_ELEMENT);
        return;
    }
    else if (userInput == E_UserInput::RIGHT) // Potion
    {
        PrepareNavigationMenu(menuChoice, NEXT_TWO_MENU_ELEMENTS);
        return;
    }
    else if (userInput == E_UserInput::UP) // ATTACK
    {
        PrepareNavigationMenu(menuChoice, NEXT_THREE_MENU_ELEMENTS);
        return;
    }
    else if (userInput == E_UserInput::DOWN) // Flee
    {
        PrepareNavigationMenu(menuChoice, NEXT_FOUR_MENU_ELEMENTS);
        return;
    }
    return;
}

void Menu::PrepareNavigationMenu(E_MenuChoices menuChoice, unsigned short int numberOfUiElementsToJumpOver)
{
    GetUserData()->GetWeapons()->ClearWeaponLogLine();
    
    ClearConsoleNavigationMenu();
    //SetIsMenuCleared(true);
    int enumToInt = static_cast<int>(menuChoice);
    E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(enumToInt + (NB_LINES_NEXT_NAVIG_UI * numberOfUiElementsToJumpOver));
    PrintNavigationMenu(nextMenuInEnum);

    GetUserData()->GetWeapons()->SelectWeapon(E_UserInput::EMPTY);

    AddDelay();
    return;
}

void Menu::PrintSingleMenuChoice(E_UserInput userInput, E_MenuChoices menuChoice)
{

    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("Menu.cpp : PrintSingleMenuChoice() : UserInput is EMPTY");
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
        AddDelay();
        return;
    }

    return;
}

void Menu::PrintSelectedMenu(E_MenuChoices currentMenuChoice)
{
    std::cout << GetMenuAtLine(GetOutputManager()->GetNarration()->GetMenuFilePath(), currentMenuChoice) << std::endl;
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentMenuChoice);
    return;
}

void Menu::PrintNavigationMenu(E_MenuChoices currentNavigationChoice)
{
    unsigned int enumToInt = static_cast<unsigned int>(currentNavigationChoice);
    std::string& menuFilePath = GetOutputManager()->GetNarration()->GetMenuFilePath();
    std::string navigationMenuText = GetOutputManager()->GetNarration()->GetTextBetweenLines(menuFilePath, enumToInt, NAVIGATION_MENU_HEIGHT);
    std::cout << navigationMenuText;
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentNavigationChoice);
    return;
}

void Menu::PrintEnterNameMenu()
{
    std::cout << "            What name do you want Khai to call you? ";
    std::string playerName;
    GetConsoleHandler()->ActivateConsoleCursor();

    std::cin >> playerName;

    //GetConsoleHandler()->DisableConsoleCursor(); // TODO: readd
    GetUserData()->SetPlayerName(playerName);
    SetIsMenuCleared(false);
    GetScenes()->SetNextScene(E_MenuChoices::ENTER_NAME);
    return;
}

std::string Menu::GetLastLineInConsole()
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

std::string Menu::GetMenuAtLine(std::string& filePathStr, E_MenuChoices atLine)
{
    std::ifstream filePath(filePathStr);
    std::string text;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R Menu.cpp : GetMenuAtLine() : ERROR: Could not open the game text file.");
        std::cout << "Menu.cpp : GetMenuAtLine() : ERROR Could not open the game text file." << std::endl;
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

E_MenuChoices Menu::GetSelectedMenuLine()
{
    DEBUG_MSG("#C Menu.cpp : GetSelectedMenuLine() : ");
    //std::cout << int(m_selectedMenuLine) << std::endl; // Debug line
    return m_selectedMenuLine;
}

void Menu::SetSelectedMenuLine(E_MenuChoices selectedMenuLine)
{
    DEBUG_MSG("#C Menu.cpp : SetSelectedMenuLine() : ");
    //std::cout << int(selectedMenuLine) << std::endl; // Debug line
    m_selectedMenuLine = selectedMenuLine;
}

void Menu::ClearConsolePreviousLine()
{
    DEBUG_MSG("#Y Menu.cpp : ClearConsolePreviousLine() : Clear previous line debug deactivated");
    std::cout << "\033[1A\033[0K";
}

void Menu::ClearConsoleNavigationMenu()
{
    DEBUG_MSG("#Y Menu.cpp : ClearConsolePreviousLine() : Clear navigation menu");
    for (size_t i = 0; i < NAVIGATION_MENU_HEIGHT; i++)
    {
        ClearConsolePreviousLine();
    }
}

bool Menu::GetIsMenuCleared()
{
    return m_isMenuCleared;
}

void Menu::SetIsMenuCleared(bool isMenuCleared)
{
    m_isMenuCleared = isMenuCleared;
}


//
//Narration* Menu::GetNarrationManager()
//{
//    return m_narrationManager;
//}
//
//Scenes* Menu::GetScenesManager()
//{
//    return m_scenesManager;
//}
//
//UserData* Menu::GetUserData()
//{
//    return m_userData;
//}
//
//
//
//Weapons* Menu::GetWeaponManager()
//{
//    return m_weaponManager;
//}
//
//void Menu::SetWeaponManager(Weapons* weaponManager)
//{
//    m_weaponManager = weaponManager;
//}

void Menu::AddDelay()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

//GameplayManager* Menu::GetGameplayManager()
//{
//    return m_gameplayManager;
//}
//
//void Menu::SetGameplayManager(GameplayManager* gameplayManager)
//{
//    m_gameplayManager = gameplayManager;
//}

UserData* Menu::GetUserData()
{
    return m_userData;
}

void Menu::SetUserData(UserData* userData)
{
    m_userData = userData;
}

OutputManager* Menu::GetOutputManager()
{
    return m_outputManager;
}

void Menu::SetOutputManager(OutputManager* outputManager)
{
    m_outputManager = outputManager;
}

ConsoleHandler* Menu::GetConsoleHandler()
{
    return m_consoleHandler;
}

void Menu::SetConsoleHandler(ConsoleHandler* consoleHandler)
{
    m_consoleHandler = consoleHandler;
}

Scenes* Menu::GetScenes()
{
    return m_scenes;
}

//void Menu::SetScenes(Scenes* scenes)
//{
//    m_scenes = scenes;
//}
