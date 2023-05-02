#include <conio.h>
#include <iostream>
#include "UserInputManager.h"

//#include "ScenesManager.h"
//#include "MenuManager.h"
//#include <MenuManager.h>

UserInputManager::UserInputManager(ScenesManager* sceneManager, MenuManager* menuManager) :
    m_hasInput(false),
    m_sceneManager(sceneManager),
    m_menuManager(menuManager)
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

                case 100: // Letter d
                    return E_UserInput::RIGHT;
                case 68: // Letter D
                    return E_UserInput::RIGHT;
                case 77: // Right arrow key
                    return E_UserInput::RIGHT;

                case 'w':
                case 'W':
                case 72: // Up arrow key
                    return E_UserInput::UP;

                case 's':
                case 'S':
                case 80: // Down arrow key
                    return E_UserInput::DOWN;

                case 13: // Enter key
                    return E_UserInput::ENTER;

                case 27: // Escape key
                    return E_UserInput::ESC;

                default: // Default case - returns an empty input
                    return E_UserInput::EMPTY;
            }
     }
}

void UserInputManager::SetAction(E_UserInput userInput)
{
    userInput = GetInput();


    if (userInput == E_UserInput::LEFT || userInput == E_UserInput::RIGHT)
    {
        GetMenuManager()->PrintMenuFromScene(userInput);
        GetMenuManager()->SetIsMenuCleared(false);
        SetHasInput(false);
    }
    if (userInput == E_UserInput::UP)
    {
	}
    if (userInput == E_UserInput::DOWN)
    {
	}
    if (userInput == E_UserInput::ENTER)
    {
        GetScenesManager()->SetNextScene(GetMenuManager()->GetSelectedMenuLine());
	}
    if (userInput == E_UserInput::ESC)
    {

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

MenuManager* UserInputManager::GetMenuManager()
{
    return m_menuManager;
}

ScenesManager* UserInputManager::GetScenesManager()
{
    return m_sceneManager;
}