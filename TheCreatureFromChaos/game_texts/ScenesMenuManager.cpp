#include <iostream>
#include <Windows.h>
#include <string>

#include "ScenesMenuManager.h"
#include "ScenesNarrationManager.h"
#include "DebugMessageSystem.h"

ScenesMenuManager::ScenesMenuManager(MainClass* mainClassAcces, UserScenesManager* sceneManager, ScenesNarrationManager* textManager) :
    m_gameMenuLines{ 1, 6 },
    m_mainClassAccess(mainClassAcces),
    m_sceneManager(sceneManager),
    m_textManager(textManager),
    m_currentPlainMenu(EMPTY_MENU_LINE),
    m_currenSceneMenuText(EMPTY_MENU_TEXT)
{
    m_selectedMenuLine = static_cast<int>(UserScenesManager::E_SceneSequence::NO_SCENE);
}

void ScenesMenuManager::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
{

    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
    short int gameMenuLine = 0;
    short int selectedMenuLine = GetSelectedMenuLine();
    short int startingMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
    short int currentPlainMenu = GetCurrentPlainMenu();
    std::string currentSceneMenuText = GetCurrentSceneMenuText();
    //std::ifstream& menuFilePath = GetMenuFilePath();

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
        if (oneLoopOFTwo)
        {
            if (GetCurrentPlainMenu() == EMPTY_MENU_LINE)
            {
                // Get no gizmo menu frame
                gameMenuLine = startingMenuLine;
                SetCurrentPlainMenu(startingMenuLine);
                SetCurrentSceneMenuText(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
            }
        }
        else
        {
            if (GetCurrentSceneMenuText() == EMPTY_MENU_TEXT)
            {
                // Get menu frame with gizmo
                selectedMenuLine = 1;
                gameMenuLine = startingMenuLine + selectedMenuLine;
                SetSelectedMenuLine(gameMenuLine);
                SetCurrentSceneMenuText(GetMenuAtLine(m_textManager->GetMenuFilePath(), gameMenuLine));
            }
        }
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:

        break;

    default:
        break;
    }
    std::string newCurrentSceneMenuText = GetMenuAtLine(m_textManager->GetMenuFilePath(), gameMenuLine);
    std::cout << newCurrentSceneMenuText << std::endl;
    //std::cout << GetCurrentSceneMenuText();
}

//void ScenesMenuManager::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
//{
//
//    UserScenesManager::E_SceneSequence scene = m_sceneManager->GetPlayerCurrentScene();
//
//    unsigned short int gameMenuLine = 0;
//
//    switch (scene)
//    {
//    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
//        if (oneLoopOFTwo)
//        {
//            if (GetCurrentPlainMenu() == EMPTY_MENU_LINE)
//            {
//                // Get no gizmo menu frame
//                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
//                SetCurrentPlainMenu(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE));
//                SetCurrentSceneMenuText(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
//            }
//        }
//        else
//        {
//            if (GetCurrentSceneMenuText() == EMPTY_MENU_TEXT)
//            {
//                // Get menu frame with gizmo
//                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine();
//                SetSelectedMenuLine(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine());
//                SetCurrentSceneMenuText(m_textManager->GetTextBetweenLines(m_textManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
//            }
//        }
//        break;
//
//    case UserScenesManager::E_SceneSequence::MOVING_SCENE:
//
//        break;
//
//    default:
//        break;
//    }
//
//    std::cout << GetCurrentSceneMenuText();
//}

std::string ScenesMenuManager::GetLastLineInConsole()
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

std::string ScenesMenuManager::GetMenuAtLine(std::string& filePathStr, unsigned int atLine)
{
    std::ifstream filePath(filePathStr);
    std::string text;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("¢RERROR: Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::string line;
        unsigned int currentLine = 0;

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

std::string ScenesMenuManager::GetCurrentSceneMenuText()
{
	return m_currenSceneMenuText;
}

void ScenesMenuManager::SetCurrentSceneMenuText(std::string sceneMenu)
{
    m_currenSceneMenuText = sceneMenu;
}

unsigned short int ScenesMenuManager::GetGameMenuLine(UserScenesManager::E_SceneSequence atLine)
{
	return m_gameMenuLines[static_cast<int>(atLine)];
}

//UserScenesManager* ScenesMenuManager::GetSceneManager()
//{
//    return m_sceneManager;
//}
//
//ScenesNarrationManager* ScenesMenuManager::GetGameTextManager()
//{
//	return m_textManager;
//}

unsigned short int ScenesMenuManager::GetSelectedMenuLine()
{
    return m_selectedMenuLine;
}

void ScenesMenuManager::SetSelectedMenuLine(unsigned short int selectedMenuLine)
{
    m_selectedMenuLine = selectedMenuLine;
}

void ScenesMenuManager::SetCurrentPlainMenu(short int currentPlainMenu)
{
    m_currentPlainMenu = currentPlainMenu;
}

short int ScenesMenuManager::GetCurrentPlainMenu()
{
    return m_currentPlainMenu;
}