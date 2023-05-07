#include <conio.h>
#include <iostream>
#include "UserInputManager.h"
#include "DebugMessageSystem.h"

UserInputManager::UserInputManager(ConsoleHandler* m_consoleHandler, ScenesManager* sceneManager, MenuManager* menuManager) :
    m_consoleHandler(),
    m_weaponManager(),
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

                case 'w':
                case 'W':
                    return E_UserInput::UP;
                    break;

                case 's':
                case 'S':
                    return E_UserInput::DOWN;
                    break;
                
                case 'e':
                case 'E':
                case 13: // Enter key
                    return E_UserInput::ENTER;
                    break;

                case '1':
                    return E_UserInput::ONE;
					break;

                case '2':
					return E_UserInput::TWO;

                case 'f':
                case 'F':
                    return E_UserInput::FLEE;
                    break;

                case 'p':
                case 'P':
                    return E_UserInput::POTION;
                    break;

                case 'h':
                case 'H':
                    return E_UserInput::HELP;

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
    bool left = (userInput == E_UserInput::LEFT);
    bool right = (userInput == E_UserInput::RIGHT);
    bool up = (userInput == E_UserInput::UP);
    bool down = (userInput == E_UserInput::DOWN);
    bool potion = (userInput == E_UserInput::POTION);
    bool flee = (userInput == E_UserInput::FLEE);
    bool help = (userInput == E_UserInput::HELP);

    if (left || right || up || down || potion || flee || help)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User is using LEFT RIGHT.");
        ActivateSelection(userInput);
        SetHasInput(false);
        return;
	}
    if (userInput == E_UserInput::ENTER)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed ENTER.");
        EnterSelection();
        SetHasInput(false);
        return;
    }
    if (userInput == E_UserInput::ONE || userInput == E_UserInput::TWO)
    {
        GetWeaponManager()->SelectWeapon(userInput);
        SetHasInput(false);
        return;
    }
    if (userInput == E_UserInput::ESC)
    {
        DEBUG_MSG("UserInputManager.cpp : SetAction() : User pressed ESC.");
        return;
	}
}

void UserInputManager::ActivateSelection(E_UserInput userInput)
{
    E_SceneSequence currentScene = GetScenesManager()->GetPlayerCurrentScene();
    unsigned short int currentSceneEnumToInt = static_cast<int>(currentScene);
    unsigned short int currentNumberOfChoices = SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt];
    bool bidirectionalMenus = (currentNumberOfChoices == TWO_WAYS_RIGHT || currentNumberOfChoices == TWO_WAYS_LEFT);
    bool quadridiractionalMenus = (currentNumberOfChoices == FOUR_WAYS_FRONT || currentNumberOfChoices == FOUR_WAYS_BACK);
    bool combatMenu = (currentNumberOfChoices == COMBAT_MENU);

    if (currentNumberOfChoices == TWO_CHOICES_MENU)
    {
        GetMenuManager()->SelectMenuFromScene(userInput);
        return;
    }
    else if (bidirectionalMenus)
    {
        if (userInput == E_UserInput::LEFT)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::LEFT);
            GetScenesManager()->SetNextScene(E_MenuChoices::LR_NAVIGATION_LEFT);
        }
        else if (userInput == E_UserInput::RIGHT)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::RIGHT);
            GetScenesManager()->SetNextScene(E_MenuChoices::LR_NAVIGATION_RIGHT);
        }
    }
    else if (quadridiractionalMenus)
    {
        if (userInput == E_UserInput::LEFT)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::LEFT);
            GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_LEFT);
        }
        else if (userInput == E_UserInput::RIGHT)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::RIGHT);
            GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_RIGHT);
        }
        else if (userInput == E_UserInput::UP)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::UP);
            GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_FOWARD);
        }
        else if (userInput == E_UserInput::DOWN)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::DOWN);
            GetScenesManager()->SetNextScene(E_MenuChoices::NAVIGATION_BACK);
        }
    }
    else if (combatMenu)
    {
        if (userInput == E_UserInput::LEFT || userInput == E_UserInput::HELP)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::LEFT);

        }
        else if (userInput == E_UserInput::RIGHT || userInput == E_UserInput::POTION)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::RIGHT);

        }
        else if (userInput == E_UserInput::UP)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::UP);

        }
        else if (userInput == E_UserInput::DOWN || userInput == E_UserInput::FLEE)
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::DOWN);

        }
    }
}

void UserInputManager::EnterSelection()
{
    E_SceneSequence currentScene = GetScenesManager()->GetPlayerCurrentScene();
    unsigned short int currentNumberOfChoices = SCENE_NUMBER_OF_MENU_CHOICES[int(currentScene)];
    if (currentNumberOfChoices == ONE_CHOICE_MENU)
    {
        GetMenuManager()->SelectMenuFromScene(E_UserInput::ENTER);
        GetScenesManager()->SetNextScene(GetMenuManager()->GetSelectedMenuLine());
        return;
	}
    else if (currentNumberOfChoices == TWO_CHOICES_MENU)
    {
        GetScenesManager()->SetNextScene(GetMenuManager()->GetSelectedMenuLine());
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

WeaponManager* UserInputManager::GetWeaponManager()
{
    return m_weaponManager;
}

void UserInputManager::SetWeaponManager(WeaponManager* weaponManager)
{
    m_weaponManager = weaponManager;
}