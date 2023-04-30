#include <iostream>
#include <Windows.h>
#include <string>

#include "GameChoicesMenu.h"
#include "GameTextManager.h"
#include "DebugMessageSystem.h"

const short int EMPTY_MENU_LINE = -1;
const std::string EMPTY_MENU_TEXT = "";

GameChoicesMenu::GameChoicesMenu(MainClass* mainClassAcces, UserScenesManager* sceneManager, GameTextManager* textManager) :
    m_gameMenuLines{ 1, 6 },
    m_mainClassAccess(mainClassAcces),
    m_sceneManager(sceneManager),
    m_textManager(textManager),
    m_currentPlainMenu(EMPTY_MENU_LINE),
    m_currenSceneMenuText(EMPTY_MENU_TEXT)
{
    m_selectedMenuLine = static_cast<int>(UserScenesManager::E_SceneSequence::NO_SCENE);
}

void GameChoicesMenu::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
{

    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();

    unsigned short int gameMenuLine = 0;

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
        if (oneLoopOFTwo)
        {
            if (GetCurrentPlainMenu() == EMPTY_MENU_LINE)
            {
                // Get no gizmo menu frame
                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
                SetCurrentPlainMenu(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE));
                SetCurrentSceneMenuText(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
            }
        }
        else
        {
            if (GetCurrentSceneMenuText() == EMPTY_MENU_TEXT)
            {
                // Get menu frame with gizmo
                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine();
                SetSelectedMenuLine(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine());
                SetCurrentSceneMenuText(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
            }
        }
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:

        break;

    default:
        break;
    }

    std::cout << GetCurrentSceneMenuText();
    //m_mainClassAcces->SetIsMenuCleared(false);
}

//void GameChoicesMenu::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
//{
//
//    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
//
//    unsigned short int gameMenuLine = 0;
//
//    switch (scene)
//    {
//    case UserScenesManager::E_SceneSequence::INTRO:
//        if (oneLoopOFTwo)
//        {
//            //std::cout << GetCurrentPlainMenu() << std::endl;
//            //std::cout << GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO) << std::endl;
//
//            if (GetCurrentPlainMenu() != GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO))
//            {
//                // Get no gizmo menu frame
//                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO);
//                SetCurrentPlainMenu(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO));
//                SetCurrentSceneMenu(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
//            }
//		}
//        else
//        {
//            if ((GetCurrentSceneMenu() != GetLastLineInConsole()))
//            {
//                // Get menu frame with gizmo
//                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO) + GetSelectedMenuLine();
//                SetSelectedMenuLine(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO) + GetSelectedMenuLine());
//                SetCurrentSceneMenu(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
//            }
//		}
//        break;
//
//    case UserScenesManager::E_SceneSequence::MOVING:
//
//        break;
//
//    default:
//        break;
//    }
//
//    std::cout << GetCurrentSceneMenu();
//    //m_mainClassAcces->SetIsMenuCleared(false);
//}

std::string GameChoicesMenu::GetLastLineInConsole()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);

    COORD position;
    position.X = 0;
    position.Y = screenBufferInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(consoleHandle, position);

    std::string lastLine;
   // DEBUG_MSG("¢R Last line:");
    //std::cout << "\n" << lastLine << std::endl;
    //DEBUG_MSG("¢R :Last line");

    // Check if the last line is empty
    if (screenBufferInfo.dwCursorPosition.X == 0) 
    {
        return "";
    }

    getline(std::cin, lastLine);

    return lastLine;
}

//std::string GameChoicesMenu::GetLastLineInConsole()
//{
//    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
//    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
//
//    COORD position;
//    position.X = 0;
//    position.Y = screenBufferInfo.dwCursorPosition.Y;
//
//    SetConsoleCursorPosition(consoleHandle, position);
//
//    std::string lastLine;
//    DEBUG_MSG("¢R Last line:");
//    std::cout << "\n" << lastLine << std::endl;
//    DEBUG_MSG("¢R :Last line");
//    getline(std::cin, lastLine);
//
//    return lastLine;
//}

std::string GameChoicesMenu::GetCurrentSceneMenuText()
{
	return m_currenSceneMenuText;
}

void GameChoicesMenu::SetCurrentSceneMenuText(std::string sceneMenu)
{
    m_currenSceneMenuText = sceneMenu;
}

unsigned short int GameChoicesMenu::GetGameMenuLine(UserScenesManager::E_SceneSequence atLine)
{
	return m_gameMenuLines[static_cast<int>(atLine)];
}

//UserScenesManager* GameChoicesMenu::GetSceneManager()
//{
//    return m_sceneManager;
//}
//
//GameTextManager* GameChoicesMenu::GetGameTextManager()
//{
//	return m_textManager;
//}

unsigned short int GameChoicesMenu::GetSelectedMenuLine()
{
    return m_selectedMenuLine;
}

void GameChoicesMenu::SetSelectedMenuLine(unsigned short int selectedMenuLine)
{
    m_selectedMenuLine = selectedMenuLine;
}

void GameChoicesMenu::SetCurrentPlainMenu(short int currentPlainMenu)
{
    m_currentPlainMenu = currentPlainMenu;
}

short int GameChoicesMenu::GetCurrentPlainMenu()
{
    return m_currentPlainMenu;
}