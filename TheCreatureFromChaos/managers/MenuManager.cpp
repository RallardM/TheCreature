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
    m_combatManager(nullptr),
    m_weaponManager(nullptr),
    m_isMenuCleared(true)
{
    m_selectedMenuLine = E_MenuChoices::NO_MENU_LINE;
}

void MenuManager::SelectMenuFromScene(E_UserInput userInput)
{
    E_SceneSequence scene = GetScenesManager()->GetPlayerCurrentScene();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : INTRO_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::TRY_TO_MOVE, E_MenuChoices::TRY_TO_REMEBER);
        break;

    case E_SceneSequence::MOVING_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : MOVING_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::LOOK_AROUND, E_MenuChoices::TRY_TO_REMEBER_TWO);
        break;

    case E_SceneSequence::KOBOLD_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::WHO_ARE_YOU, E_MenuChoices::ATTACK_KOBOLD);
        break;

    case E_SceneSequence::ENNEMY_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : KOBOLD_SCENE");
        SelectMenuChoice(userInput, E_MenuChoices::ATTACK_ENEMY, E_MenuChoices::RUN_AWAY);
        break;

    case E_SceneSequence::NAME_SCENE:
    case E_SceneSequence::ATTACK_KOBOLD_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : NAME_SCENE, ATTACK_KOBOLD_SCENE");
        PrintEnterNameMenu();
        break;

    case E_SceneSequence::WEAPONS_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : WEAPONS_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::TAKE_WEAPONS);
        break;

    case E_SceneSequence::DEAD_END_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : DEAD_END_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::GO_BACK);
        break;

    case E_SceneSequence::VICTORY_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : VICTORY_SCENE");
        GetUserData()->SetIsPlayerSeenVictory(true);
        GetScenesManager()->GetCombatManager()->SetIsFightStarted(false);
        PrintSingleMenuChoice(userInput, E_MenuChoices::WON_LEAVE);
		break;

    case E_SceneSequence::YOU_DIED_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : YOU_DIED_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::QUIT_GAME);
        break;

    case E_SceneSequence::FLEEING_BACKWARD_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : FLEEING_BACKWARD_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::RUN);
        //GetScenesManager()->GetCombatManager()->SetIsCountdownStarted(true);
        break;

    case E_SceneSequence::FLEEING_FORWARD_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : FLEEING_FORWARD_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::WON_LEAVE);
        break;

    case E_SceneSequence::FLEING_FAILED_DIED_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : FLEEING_FORWARD_SCENE");
        PrintSingleMenuChoice(userInput, E_MenuChoices::QUIT_GAME);
        break;

    case E_SceneSequence::ROOM_ONE_FRONT:
    case E_SceneSequence::ROOM_ONE_BACK:
    case E_SceneSequence::ROOM_TWO_FRONT:
    case E_SceneSequence::ROOM_TWO_BACK:
    case E_SceneSequence::ROOM_THREE_BACK:
    case E_SceneSequence::ROOM_THREE_FRONT:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : Prints 4-ways navigation system");
        SelectNavigationElement(userInput, E_MenuChoices::NAVIGATION_PLAIN);
        break;

    case E_SceneSequence::ROOM_ONE_RIGHT:
    case E_SceneSequence::ROOM_ONE_LEFT:
    case E_SceneSequence::ROOM_TWO_RIGHT:
    case E_SceneSequence::ROOM_TWO_LEFT:
    case E_SceneSequence::ROOM_THREE_RIGHT:
    case E_SceneSequence::ROOM_THREE_LEFT:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : Prints 2-ways navigation system");
        SelectNavigationElement(userInput, E_MenuChoices::LR_NAVIGATION_PLAIN);
        break;

    case E_SceneSequence::COMBAT_SCENE:
        DEBUG_MSG("MenuManager.cpp : SelectMenuFromScene() : COMBAT_SCENE");
        //SelectCombatElement(userInput);
        SelectCombatChoice(userInput);
        break;

    default:
        DEBUG_MSG("#R MenuManager.cpp : SelectMenuFromScene() : Default no menu selected");
        break;
    }
}

void MenuManager::SelectMenuChoice(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : SelectMenuChoice() : UserInput is EMPTY.");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT && GetSelectedMenuLine() != LeftMenuChoice)
    {
        ClearConsolePreviousLine();
        SetIsMenuCleared(true);
        DEBUG_MSG("MenuManager.cpp : SelectMenuChoice() : Print LeftMenuChoice");
        PrintSelectedMenu(LeftMenuChoice);
        return;
    }
    else if (userInput == E_UserInput::RIGHT && GetSelectedMenuLine() != rightMenuChoice)
    {
        ClearConsolePreviousLine();
        SetIsMenuCleared(true);
        DEBUG_MSG("MenuManager.cpp : SelectMenuChoice() : Print rightMenuChoice");
        PrintSelectedMenu(rightMenuChoice);
        return;
    }
}

void MenuManager::SelectNavigationElement(E_UserInput userInput, E_MenuChoices menuChoice)
{
    if (menuChoice == E_MenuChoices::LR_NAVIGATION_PLAIN && (userInput == E_UserInput::UP || userInput == E_UserInput::DOWN))
    {
        return;
    }
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : SelectNavigationElement() : UserInput is EMPTY");
        //ClearConsolePreviousLine();
        PrintNavigationMenu(menuChoice);
        return;
    }

    if (userInput == E_UserInput::LEFT)
    {
        PrepareNavigationMenu(menuChoice, CURRENT_MENU_ELEMENT);
        GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_LEFT);
        return;
    }
    else if (userInput == E_UserInput::RIGHT)
    {
        PrepareNavigationMenu(menuChoice, NEXT_TWO_MENU_ELEMENTS);
        GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_RIGHT);
        return;
    }
    else if (userInput == E_UserInput::UP)
    {
        PrepareNavigationMenu(menuChoice, NEXT_THREE_MENU_ELEMENTS);
        GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_FOWARD);
        return;
    }
    else if (userInput == E_UserInput::DOWN)
    {
        PrepareNavigationMenu(menuChoice, NEXT_FOUR_MENU_ELEMENTS);
        GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_BACK);
        return;
    }
    return;
}

void MenuManager::PrepareNavigationMenu(E_MenuChoices menuChoice, unsigned short int numberOfUiElementsToJumpOver)
{
    //GetWeaponManager()->ClearWeaponLogLine();
    ClearConsolePreviousLine();
    GetWeaponManager()->SetIsWeaponBeltCleared(true);
    ClearConsoleNavigationMenu();
    //SetIsMenuCleared(true);
    int enumToInt = static_cast<int>(menuChoice);
    E_MenuChoices nextMenuInEnum = static_cast<E_MenuChoices>(enumToInt + (NB_LINES_NEXT_NAVIG_UI * numberOfUiElementsToJumpOver));
    PrintNavigationMenu(nextMenuInEnum);

    GetWeaponManager()->SelectWeapon(E_UserInput::EMPTY);

    AddDelay();
    return;
}

//void MenuManager::SelectCombatElement(E_UserInput userInput)
//{
//    if (GetCombatManager()->GetIsPlayerTurn())
//    {
//        SelectCombatChoice(userInput, E_MenuChoices::COMBAT_PLAIN);
//    }
//    else
//    {
//        SelectCombatChoice(userInput, E_MenuChoices::NEXT_TURN);
//    }
//}

void MenuManager::SelectCombatChoice(E_UserInput userInput)
{
    if (userInput == E_UserInput::EMPTY)
    {
        DEBUG_MSG("MenuManager.cpp : SelectCombatChoice() : UserInput is EMPTY");
        if (!GetCombatManager()->GetIsPlayerTurn())
        {
            DEBUG_MSG("MenuManager.cpp : SelectCombatChoice() : Not player turn");
            PrintNavigationMenu(E_MenuChoices::COMBAT_PLAIN);
            return;
        }
        else
        {
            PrintNavigationMenu(E_MenuChoices::NEXT_TURN);
        }
       
        return;
    }
    else if (userInput == E_UserInput::LEFT) // ATTACK
    {
        PrepareCombatMenu(userInput, E_MenuChoices::COMBAT_ATTACK);
        //GetCombatManager()->SetCombatAction(userInput);
        return;
    }
    else if (userInput == E_UserInput::RIGHT) // Potion
    {
        PrepareCombatMenu(userInput, E_MenuChoices::COMBAT_POTION);
        //GetCombatManager()->SetCombatAction(userInput);
        return;
    }
    else if (userInput == E_UserInput::UP)  // Khai Help
    {
        PrepareCombatMenu(userInput, E_MenuChoices::COMBAT_HELP);
        //GetCombatManager()->SetCombatAction(userInput);
        return;
    }
    else if (userInput == E_UserInput::DOWN) // Flee
    {
        PrepareCombatMenu(userInput, E_MenuChoices::COMBAT_FLEE);
        //GetCombatManager()->SetCombatAction(userInput);
        return;
    }
    return;
}

void MenuManager::PrepareCombatMenu(E_UserInput userInput, E_MenuChoices menuChoice)
{
    bool isFightStarted = GetCombatManager()->GetIsFightStarted();
    bool isPlayerTurn = GetCombatManager()->GetIsPlayerTurn();
    if (isFightStarted && !isPlayerTurn)
    {
		DEBUG_MSG("MenuManager.cpp : PrepareCombatMenu() : Not player turn");
		return;
	}
    //GetWeaponManager()->ClearWeaponLogLine();
    ClearConsolePreviousLine();
    GetWeaponManager()->SetIsWeaponBeltCleared(true);
    ClearConsoleNavigationMenu();
    //SetIsMenuCleared(true);
    
    PrintNavigationMenu(menuChoice);

    GetWeaponManager()->SelectWeapon(E_UserInput::EMPTY);

    AddDelay();
    GetCombatManager()->SetCombatAction(userInput);
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
        AddDelay();
        return;
    }
    return;
}

void MenuManager::PrintSelectedMenu(E_MenuChoices currentMenuChoice)
{
    std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), currentMenuChoice) << std::endl;
    GetScenesManager()->SetIsAllConsoleTextCleared(false);
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentMenuChoice);
    return;
}

void MenuManager::PrintNavigationMenu(E_MenuChoices currentNavigationChoice)
{
    //ClearConsolePreviousLine();
    unsigned int enumToInt = static_cast<unsigned int>(currentNavigationChoice);
    std::string& menuFilePath = GetNarrationManager()->GetMenuFilePath();
    std::string navigationMenuText = GetNarrationManager()->GetTextBetweenLines(menuFilePath, enumToInt, NAVIGATION_MENU_HEIGHT);
    std::cout << navigationMenuText;
    GetScenesManager()->SetIsAllConsoleTextCleared(false);
    SetIsMenuCleared(false);
    SetSelectedMenuLine(currentNavigationChoice);
    return;
}

void MenuManager::PrintEnterNameMenu()
{
    std::cout << "            What name do you want Khai to call you? ";
    GetScenesManager()->SetIsAllConsoleTextCleared(false);
    std::string playerName;
    //GetConsoleHandler()->ActivateConsoleCursor(); // TODO

    std::cin >> playerName;

    //GetConsoleHandler()->DisableConsoleCursor(); // TODO: readd
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

void MenuManager::AddDelay()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}


WeaponManager* MenuManager::GetWeaponManager()
{
    return m_weaponManager;
}

void MenuManager::SetWeaponManager(WeaponManager* weaponManager)
{
    m_weaponManager = weaponManager;
}

CombatManager* MenuManager::GetCombatManager()
{
    return m_combatManager;
}

void MenuManager::SetCombatManager(CombatManager* combatManager)
{
    m_combatManager = combatManager;
}
