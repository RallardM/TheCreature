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

//void MenuManager::PrintMenuFromScene(E_UserInput userInput)
//{
//    //E_UserInput userInput = GetUserInputManager()->GetInput();
//    E_SceneSequence scene = GetSceneManager()->GetPlayerCurrentScene();
//
//    switch (scene)
//    {
//        case E_SceneSequence::INTRO_SCENE:
//            if (userInput != E_UserInput::EMPTY)
//            {
//                ClearConsolePreviousLine();
//                int numMenuChoices = GetNumberOfMenuChoices(scene);
//                int selectedMenuLine = static_cast<int>(GetSelectedMenuLine());
//
//                if (userInput == E_UserInput::LEFT)
//                {
//                    for (int i = 0; i < numMenuChoices; i++)
//                    {
//
//					}
//                }
//                else if (userInput == E_UserInput::RIGHT)
//                {
//
//                }
//
//                SetSelectedMenuLine(selectedMenuLine);
//                std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), selectedMenuLine) << std::endl;
//                SetIsMenuCleared(false);
//                break;
//            }  
//
//        case E_SceneSequence::MOVING_SCENE:
//            DEBUG_MSG("#R MenuManager.cpp : PrintMenuFromScene() : MOVING_SCENE");
//            if (userInput != E_UserInput::EMPTY)
//            {
//                ClearConsolePreviousLine();
//                if (userInput == E_UserInput::LEFT)
//                {
//                    DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print TRY_TO_MOVE menu");
//                    std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::TRY_TO_MOVE) << std::endl;
//                    SetIsMenuCleared(false);
//                    SetSelectedMenuLine(E_MenuChoices::TRY_TO_MOVE);
//                    break;
//                }
//                else if (userInput == E_UserInput::RIGHT)
//                {
//                    DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print DO_NOTHING menu");
//                    std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::DO_NOTHING) << std::endl;
//                    SetIsMenuCleared(false);
//                    SetSelectedMenuLine(E_MenuChoices::DO_NOTHING);
//                    break;
//                }
//            }
//            else
//            {
//                DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : UserInput is EMPTY Print TRY_TO_MOVE menu");
//                std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), E_MenuChoices::TRY_TO_MOVE) << std::endl;
//                SetIsMenuCleared(false);
//                SetSelectedMenuLine(E_MenuChoices::TRY_TO_MOVE);
//                break;
//            }
//
//        default:
//            DEBUG_MSG("#R MenuManager.cpp : PrintMenuFromScene() : Default no menu selected");
//            break;
//    }
//}
//
//unsigned short int GetNumberOfMenuChoices(E_SceneSequence scene)
//{
//    const unsigned short int FOUR_MENU_CHOICES = 4;
//    const unsigned short int THREE_MENU_CHOICES = 3;
//    const unsigned short int TWO_MENU_CHOICES = 2;
//
//    switch (scene)
//    {
//		case E_SceneSequence::INTRO_SCENE:
//			return TWO_MENU_CHOICES;
//		case E_SceneSequence::MOVING_SCENE:
//			return THREE_MENU_CHOICES;
//		default:
//			DEBUG_MSG("#R MenuManager.cpp : GetNumberOfMenuChoices() : Default no number of menu");
//			break;
//	}
//}

void MenuManager::PrintMenuFromScene(E_UserInput userInput)
{
    E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : INTRO_SCENE");
        SelectSceneToPrint(userInput, E_MenuChoices::TRY_TO_MOVE, E_MenuChoices::TRY_TO_REMEBER);
        break;

    case E_SceneSequence::MOVING_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : MOVING_SCENE");
        SelectSceneToPrint(userInput, E_MenuChoices::LOOK_AROUND, E_MenuChoices::TRY_TO_REMEBER_TWO);
        break;

    case E_SceneSequence::KOBOLD_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectSceneToPrint(userInput, E_MenuChoices::WHO_ARE_YOU, E_MenuChoices::ATTACK_KOBOLD);
        break;

    case E_SceneSequence::NAME_SCENE:
    case E_SceneSequence::ATTACK_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : NAME_SCENE TODO");
        // TODO : cin name
        break;

    case E_SceneSequence::DEAD_END_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectSceneToPrint(userInput, E_MenuChoices::GO_BACK, E_MenuChoices::GO_BACK);
        break;

    case E_SceneSequence::ENNEMY_SCENE:
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : KOBOLD_SCENE");
        SelectSceneToPrint(userInput, E_MenuChoices::ATTACK_ENEMY, E_MenuChoices::RUNAWAY);
        break;

    default:
        DEBUG_MSG("#R MenuManager.cpp : PrintMenuFromScene() : Default no menu selected");
        break;
    }
}

void MenuManager::SelectSceneToPrint(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice)
{
    if (userInput != E_UserInput::EMPTY)
    {
        ClearConsolePreviousLine();
        if (userInput == E_UserInput::LEFT)
        {
            DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print LeftMenuChoice");
            std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), LeftMenuChoice) << std::endl;
            SetIsMenuCleared(false);
            SetSelectedMenuLine(LeftMenuChoice);
            return;
        }
        else if (userInput == E_UserInput::RIGHT)
        {
            DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : Print DO_NOTHING menu");
            std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), rightMenuChoice) << std::endl;
            SetIsMenuCleared(false);
            SetSelectedMenuLine(rightMenuChoice);
            return;
        }
    }
    else
    {
        DEBUG_MSG("MenuManager.cpp : PrintMenuFromScene() : UserInput is EMPTY Print TRY_TO_MOVE menu");
        std::cout << GetMenuAtLine(GetNarrationManager()->GetMenuFilePath(), LeftMenuChoice) << std::endl;
        SetIsMenuCleared(false);
        SetSelectedMenuLine(LeftMenuChoice);
        return;
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

NarrationManager* MenuManager::GetNarrationManager()
{
    return m_narrationManager;
}

ScenesManager* MenuManager::GetSceneManager()
{
	return m_sceneManager;
}