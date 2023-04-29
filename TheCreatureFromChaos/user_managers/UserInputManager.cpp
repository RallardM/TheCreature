#include "UserInputManager.h"
#include <conio.h>

bool UserInputManager::HasInput()
{
    if (_kbhit())
    {
		return true;
	}
    else
    {
		return false;
	}
}

E_UserInput UserInputManager::GetInput()
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

                case 13: // Enter key
                    return E_UserInput::ENTER;

                case 27: // Escape key
                    return E_UserInput::ESC;
            }
        }
     }
}