#include "InputManager.h"
#include <conio.h>



bool InputManager::HasInput()
{
	return m_hasInput;
}

E_UserInput InputManager::GetInput()
{
    while (true) 
    {
        if (_kbhit())
        {
            char key = _getch(); // Read the key
            switch (key)
            {
            case 'a':
            case 'A':
            case 75: // Left arrow key
                return E_UserInput::LEFT;
            case 'd':
            case 'D':
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

            }
        }
     }
}