#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>

#include "ScenesMenuManager.h"
#include "ScenesNarrationManager.h"
#include "DebugMessageSystem.h"

ScenesMenuManager::ScenesMenuManager(MainClass* mainClassAcces, UserScenesManager* sceneManager, ScenesNarrationManager* narrationManager) :
    m_gameMenuLines{ 1, 6 },
    m_mainClassAccess(mainClassAcces),
    m_narrationManager(narrationManager),
    m_sceneManager(sceneManager),
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
        PrintSceneMenu(userInput, UserScenesManager::E_SceneSequence::INTRO_SCENE);
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:
        PrintSceneMenu(userInput, UserScenesManager::E_SceneSequence::MOVING_SCENE);
        break;

    default:
        break;
    }
    //std::string newCurrentSceneMenuText = GetMenuAtLine(m_narrationManager->GetMenuFilePath(), gameMenuLine);
    //std::cout << newCurrentSceneMenuText << std::endl;
    //std::cout << GetCurrentSceneMenuText();
}

void ScenesMenuManager::PrintSceneMenu(UserInputManager::E_UserInput userInput, UserScenesManager::E_SceneSequence scene)
{
    unsigned short int gameMenuLine = 0;
    unsigned short int selectedChoiceIndex = 0;
    unsigned short int* sceneMenuChoicesArray = GetSceneMenuLines(scene);

    switch (userInput)
    {
    case UserInputManager::E_UserInput::LEFT:
        if (selectedChoiceIndex > 0) 
        {
            selectedChoiceIndex--;
        }
        break;

    case UserInputManager::E_UserInput::RIGHT:
        if (selectedChoiceIndex < (NUMBER_OF_HIGHLIGHTED_MENU_LINES - 1))
        {
            selectedChoiceIndex++;
        }
        break;

    default:
        break;
    }

    std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), sceneMenuChoicesArray[selectedChoiceIndex]);
    std::cout << std::endl;

    //if (oneLoopOFTwo)
    //{
    //    if (GetCurrentPlainMenu() == EMPTY_MENU_LINE)
    //    {
    //        // Get no gizmo menu frame
    //        gameMenuLine = startingMenuLine;
    //        SetCurrentPlainMenu(startingMenuLine);
    //        SetCurrentSceneMenuText(m_narrationManager->GetTextBetweenLines(m_narrationManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
    //    }
    //}
    //else
    //{
    //    if (GetCurrentSceneMenuText() == EMPTY_MENU_TEXT)
    //    {
    //        // Get menu frame with gizmo
    //        selectedMenuLine = 1;
    //        gameMenuLine = startingMenuLine + selectedMenuLine;
    //        SetSelectedMenuLine(gameMenuLine);
    //        SetCurrentSceneMenuText(GetMenuAtLine(m_narrationManager->GetMenuFilePath(), gameMenuLine));
    //    }
    //}
}

unsigned short int* ScenesMenuManager::GetSceneMenuLines(UserScenesManager::E_SceneSequence scene)
{
    unsigned short int* sceneMenuLines = new unsigned short int[NUMBER_OF_HIGHLIGHTED_MENU_LINES];
    int startingNumber = 0;

    switch (scene)
    {
    case UserScenesManager::E_SceneSequence::INTRO_SCENE:
        startingNumber = m_narrationManager->GetSceneMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE);
        startingNumber += UNHIGHLIGHTED_MENU_LINE;

        for (unsigned short int i = 0; i < NUMBER_OF_HIGHLIGHTED_MENU_LINES; i++)
        {
            sceneMenuLines[i] = startingNumber + i;
        }
        break;

    case UserScenesManager::E_SceneSequence::MOVING_SCENE:
        startingNumber = m_narrationManager->GetSceneMenuLine(UserScenesManager::E_SceneSequence::MOVING_SCENE);
        for (unsigned short int i = 0; i < NUMBER_OF_HIGHLIGHTED_MENU_LINES; i++)
        {
            sceneMenuLines[i] = startingNumber + i;
        }
        break;

    default:
        return nullptr;
    }

    return sceneMenuLines;
}
 

//void ScenesMenuManager::PrintMenuFromScene(UserInputManager::E_UserInput userInput, bool oneLoopOFTwo)
//{
//
//    UserScenesManager::E_SceneSequence scene = m_narrationManager->GetPlayerCurrentScene();
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
//                SetCurrentSceneMenuText(m_narrationManager->GetTextBetweenLines(m_narrationManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
//            }
//        }
//        else
//        {
//            if (GetCurrentSceneMenuText() == EMPTY_MENU_TEXT)
//            {
//                // Get menu frame with gizmo
//                gameMenuLine = GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine();
//                SetSelectedMenuLine(GetGameMenuLine(UserScenesManager::E_SceneSequence::INTRO_SCENE) + GetSelectedMenuLine());
//                SetCurrentSceneMenuText(m_narrationManager->GetTextBetweenLines(m_narrationManager->GetMenuFilePath(), gameMenuLine, gameMenuLine));
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
//    return m_narrationManager;
//}
//
//ScenesNarrationManager* ScenesMenuManager::GetGameTextManager()
//{
//	return m_narrationManager;
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