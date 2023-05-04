#include <conio.h>
#include <iostream>
#include "UserInputManager.h"
#include "DebugMessageSystem.h"

UserInputManager::UserInputManager(ConsoleHandler* m_consoleHandler, ScenesManager* sceneManager, MenuManager* menuManager) :
    m_consoleHandler(),
    m_sceneManager(sceneManager),
    m_menuManager(menuManager),
    m_hasInput(false)
{
}

E_UserInput UserInputManager::GetInput()
{
    char key = 0;
    while (true) 
    {
        //if (_kbhit())
        //{
            key = _getch(); // Read the key
            //std::cout << "Letter " << char(key) << " pressed , number :" << key << std::endl;
            
            switch (key)
            {
                case 'a': 
                case 'A': 
                case 75: // Left arrow keya
                    return E_UserInput::LEFT;
                    break;

                case 100: // Letter d
                    return E_UserInput::RIGHT;
                    break;

                case 68: // Letter D
                    return E_UserInput::RIGHT;
                    break;

                case 77: // Right arrow key
                    return E_UserInput::RIGHT;
                    break;

                case 'w':
                case 'W':
                case 72: // Up arrow key
                    return E_UserInput::UP;
                    break;

                case 's':
                case 'S':
                case 80: // Down arrow key
                    return E_UserInput::DOWN;
                    break;

                case 13: // Enter key
                    return E_UserInput::ENTER;
                    break;

                case 27: // Escape key
                    return E_UserInput::ESC;
                    break;

                default: // Default case - returns an empty input
                    return E_UserInput::EMPTY;
                    break;
            }
     }
}

void UserInputManager::SetAction(E_UserInput userInput)
{
    userInput = GetInput();

    //bool isUserPrompted = GetConsoleHandler()->GetIsUserPrompted();

    //if (isUserPrompted)
    //{
    //    return;
    //}
    if (userInput == E_UserInput::LEFT || userInput == E_UserInput::RIGHT)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User is using LEFT RIGHT.");
        GetMenuManager()->PrintMenuFromScene(userInput);
        GetMenuManager()->SetIsMenuCleared(false);
        SetHasInput(false);
        return;
    }
    if (userInput == E_UserInput::UP)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed UP.");
        return;
	}
    if (userInput == E_UserInput::DOWN)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed DOWN.");
        return;
	}
    if (userInput == E_UserInput::ENTER)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed ENTER.");
        GetScenesManager()->SetNextScene(GetMenuManager()->GetSelectedMenuLine());
        return;
    }
    if (userInput == E_UserInput::ESC)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed ESC.");
        return;
	}
}

bool UserInputManager::HasInput()
{
    return m_hasInput;
}

void UserInputManager::SetHasInput(bool hasInput)
{
    m_hasInput = hasInput;
}

ConsoleHandler* UserInputManager::GetConsoleHandler()
{
    return m_consoleHandler;
}


MenuManager* UserInputManager::GetMenuManager()
{
    return m_menuManager;
}

ScenesManager* UserInputManager::GetScenesManager()
{
    return m_sceneManager;
}