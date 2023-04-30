#include <iostream>
#include <Windows.h>
#include <string>

#include "GameChoicesMenu.h"
#include "GameTextManager.h"
#include "DebugMessageSystem.h"


GameChoicesMenu::GameChoicesMenu(MainClass* mainClassAcces, UserScenesManager* sceneManager, GameTextManager* textManager) :
    m_gameMenuLines{ 1, 6 },
    m_mainClassAccess(mainClassAcces),
    m_sceneManager(sceneManager),
    m_textManager(textManager),
    m_currentPlainMenu(EMPTY_MENU_LINE),
    m_currenSceneMenuText(EMPTY_MENU_TEXT),
    m_menuFilePath("resouce_files/GameChoicesMenu.txt")
{
    m_selectedMenuLine = static_cast<int>(UserScenesManager::E_SceneSequence::NO_SCENE);
}

void GameChoicesMenu::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
{
    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
    short int gameMenuLine = 0;
    short int selectedMenuLine = GetSelectedMenuLine();
    short int startingMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
    short int currentPlainMenu = GetCurrentPlainMenu();
    std::string currentSceneMenuText = GetCurrentSceneMenuText();
    std::ifstream& menuFilePath = GetMenuFilePath();

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
        if (oneLoopOFTwo)
        {
            if (currentPlainMenu == EMPTY_MENU_LINE)
            {
                // Get no gizmo menu frame
                gameMenuLine = startingMenuLine;
                SetCurrentPlainMenu(startingMenuLine);
                SetCurrentSceneMenuText(GetMenuAtLine(menuFilePath, gameMenuLine));
            }
        }
        else
        {
            if (currentSceneMenuText == EMPTY_MENU_TEXT)
            {
                // Get menu frame with gizmo
                selectedMenuLine = 1;
                gameMenuLine = startingMenuLine + selectedMenuLine;
                SetSelectedMenuLine(gameMenuLine);
                SetCurrentSceneMenuText(GetMenuAtLine(menuFilePath, gameMenuLine));
            }
        }
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:

        break;

    default:
        break;
    }

    std::string newCurrentSceneMenuText = GetMenuAtLine(GetMenuFilePath(), gameMenuLine);
    std::cout << newCurrentSceneMenuText << std::endl;
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

    // Check if the last line is empty
    if (screenBufferInfo.dwCursorPosition.X == 0) 
    {
        return "";
    }

    getline(std::cin, lastLine);

    return lastLine;
}

std::string GameChoicesMenu::GetMenuAtLine(std::ifstream& filePath, unsigned int atLine)
{
    //std::ifstream& fileInputStream;
    std::string text;


    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("¢RERROR: Could not open the menu text file.");
        exit(EXIT_FAILURE);
    }

    // Move to the beginning of the file
    filePath.seekg(0, std::ios::beg);

    // Loop through each line in the file
    for (unsigned int i = 1; i <= atLine; i++)
    {
        // Read the line from the file
        std::getline(filePath, text);

        // Check if we have reached the desired line
        if (i == atLine)
        {
            // We have found the line, so break the loop
            break;
        }
    }

    // Close the file
    filePath.close();

    // Return the line at the specified index
    return text;
}


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

std::ifstream& GameChoicesMenu::GetMenuFilePath()
{
    return m_menuFilePath;
}

