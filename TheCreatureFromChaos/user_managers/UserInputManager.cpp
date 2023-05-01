#include "UserInputManager.h"
#include <conio.h>
#include <iostream>

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
                    //std::cout << "Up arrow key pressed" << std::endl;
                    return E_UserInput::UP;

                case 's':
                case 'S':
                case 80: // Down arrow key
                    //std::cout << "Down arrow key pressed" << std::endl;
                    return E_UserInput::DOWN;

                case 13: // Enter key
                    //std::cout << "Enter key pressed" << std::endl;
                    return E_UserInput::ENTER;

                case 27: // Escape key
                    //std::cout << "Escape key pressed" << std::endl;
                    //SetHasInput(true);
                    return E_UserInput::ESC;

                default: // Default case - returns an empty input
                    //std::cout << "Default case - returns an empty input" << std::endl;
                    //SetHasInput(false);
                    return E_UserInput::EMPTY;
            }
            
        //}
        //else
        //{
        //    //std::cout << "No input detected" << std::endl;
        //    SetHasInput(false);
        //    return E_UserInput::EMPTY;
        //}
     }
}

//bool UserInputManager::HasInput()
//{
//    if (_kbhit()) // check if a key is being pressed
//    {
//        //_getch(); // read the key from the buffer to clear it
//        //return true;
//        return _getch();
//    }
//    else
//    {
//        return false;
//    }
//}

//bool UserInputManager::HasInput()
//{
//    if (GetInput() != E_UserInput::EMPTY)
//    {
//		return true;
//	}
//    else
//    {
//		return false;
//	}
//}

bool UserInputManager::HasInput()
{
    return m_hasInput;
}

void UserInputManager::SetHasInput(bool hasInput)
{
    m_hasInput = hasInput;
}