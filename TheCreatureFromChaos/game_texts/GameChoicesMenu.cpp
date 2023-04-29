#include <iostream>
#include <Windows.h>
#include <string>

#include "GameChoicesMenu.h"
#include "GameTextManager.h"

GameChoicesMenu::GameChoicesMenu(MainClass* mainClassAcces, UserScenesManager* sceneManager, GameTextManager* textManager) :
    m_gameMenuLines{ 1, 6 },
    m_mainClassAcces(mainClassAcces),
    m_sceneManager(sceneManager),
    m_textManager(textManager),
    m_selectedMenuLine(1),
    m_currentPlainMenu(-1),
    m_currenSceneMenuText("")
{
}

void GameChoicesMenu::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
{

    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();

    unsigned short int gameMenuLine = 0;
    if (!m_mainClassAcces->GetIsMenuCleared())
    {
        return;
    }

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO:
        if (oneLoopOFTwo)
        {
            if (GetCurrentPlainMenu() != GetGameMenuLine(0))
            {
                // Get plain menu for console printing
                gameMenuLine = GetGameMenuLine(0);
                SetCurrentPlainMenu(GetGameMenuLine(0));
                SetCurrentSceneMenu(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
			}
		}
        else
        {
            if (GetCurrentSceneMenu() != GetLastLineInConsole())
            {
                // Get menu with selection gizmo for console printing
                gameMenuLine = GetGameMenuLine(0) + GetSelectedMenuLine();
                SetSelectedMenuLine(GetGameMenuLine(0) + GetSelectedMenuLine());
                SetCurrentSceneMenu(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
            }
		}
        break;

    case UserScenesManager::E_SceneSequence::MOVING:

        break;

    default:
        break;
    }

    std::cout << GetCurrentSceneMenu();
}

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
    getline(std::cin, lastLine);

    return lastLine;
}

std::string GameChoicesMenu::GetCurrentSceneMenu()
{
	return m_currenSceneMenuText;
}

void GameChoicesMenu::SetCurrentSceneMenu(std::string sceneMenu)
{
    m_currenSceneMenuText = sceneMenu;
}

unsigned short int GameChoicesMenu::GetGameMenuLine(unsigned short int atLine)
{
	return m_gameMenuLines[atLine];
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

