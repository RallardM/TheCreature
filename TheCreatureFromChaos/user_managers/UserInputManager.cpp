
#include <conio.h>
#include <iostream>

#include "UserInputManager.h"
#include "ScenesMenuManager.h"

//UserInputManager::UserInputManager(MainClass* mainClassAccess) :
//    m_mainClassAccess(mainClassAccess),
//	m_hasInput(false)
//{
//}

UserInputManager::E_UserInput UserInputManager::GetInput()
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

void UserInputManager::SetAction(UserInputManager::E_UserInput userInput)
{
    userInput = GetInput();
    ScenesMenuManager menuManager;
    MainClass mainClass{};

    if (userInput == UserInputManager::E_UserInput::LEFT || userInput == UserInputManager::E_UserInput::RIGHT)
    {
        menuManager.PrintMenuFromScene(userInput);
        mainClass.SetIsMenuCleared(false);
        SetHasInput(false);
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