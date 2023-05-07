#include <conio.h>
#include <iostream>
#include "UserInputManager.h"
#include "DebugMessageSystem.h"
#include "CombatManager.h"

UserInputManager::UserInputManager(ConsoleHandler* m_consoleHandler, ScenesManager* sceneManager, MenuManager* menuManager, CombatManager* combatManager) :
    m_consoleHandler(),
    m_weaponManager(),
    m_currentInputType(E_CurrentInputType::DIALOGUES),
    m_combatManager(combatManager),
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
                case    97:    //'a':           // Attack
                case    65:    //'A':
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
						return E_UserInput::UP;
					}
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
						return E_UserInput::LEFT;
					}
                    else
                    {
						return E_UserInput::EMPTY;
					}
                    break;

                case    72:    // Up arrow key
                case '\033[A': // Up arrow key
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT || GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
                        return E_UserInput::UP;
                    }
                    else
                    {
                        return E_UserInput::EMPTY;
                    }

                case   107:    //'k':           // Khai help
                case    75:    //'K': // Is the smae as Left arrow key
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        return E_UserInput::LEFT;
                    }
                    // If is in navigation mode and the input is not the left arrow key then return nothing
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION && key != '\033[D')
                    {
                        return E_UserInput::EMPTY;
                    }
                    break;

                case '\033[D': // Left arrow key
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        return E_UserInput::LEFT;
                    }
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
                        return E_UserInput::LEFT;
                    }
                    else
                    {
                        return E_UserInput::EMPTY;
                    }
                    break;

                case   112:    //'p':           // Potion
                case    80:    //'P': 
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        return E_UserInput::RIGHT;
                    }
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
					    if (key == '\033[B') // Down arrow key = 80
                        {
                            return E_UserInput::DOWN;
                        }
					}
                    else
                    {
                        return E_UserInput::EMPTY;
                    }
                    break;

                case    77:    // Right arrow key
                case '\033[C': // Right arrow key
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        if (key != '\033[B') // Down arrow key = 80
                        {
							return E_UserInput::RIGHT;
						}
                        else
                        {
							return E_UserInput::EMPTY;
						}
                    }
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
                        return E_UserInput::RIGHT;
                    }
                    else
                    {
                        return E_UserInput::EMPTY;
                    }
                    break;


                case   102:    //'f':           // Flee
                case    70:    //'F': 
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        return E_UserInput::DOWN;
                    }
                    else
                    {
                        return E_UserInput::EMPTY;
                    }
                    break;

                case '\033[B': // Down arrow key
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
    bool left = (userInput == E_UserInput::LEFT);
    bool right = (userInput == E_UserInput::RIGHT);
    bool up = (userInput == E_UserInput::UP);
    bool down = (userInput == E_UserInput::DOWN);


    if (left || right || up || down)
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
        if (userInput == E_UserInput::LEFT) // Khail help
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::LEFT);
        }
        else if (userInput == E_UserInput::RIGHT) // Potion
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::RIGHT);
        }
        else if (userInput == E_UserInput::UP) // Attack
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::UP);
        }
        else if (userInput == E_UserInput::DOWN) // Flee
        {
            GetMenuManager()->SelectMenuFromScene(E_UserInput::DOWN);
        }
        GetCombatManager()->SetCombatAction(userInput);
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

UserInputManager::E_CurrentInputType UserInputManager::GetCurrentInputType()
{
    return m_currentInputType;
}

void UserInputManager::SetCurrentInputType(E_CurrentInputType currentInputType)
{
    m_currentInputType = currentInputType;
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

CombatManager* UserInputManager::GetCombatManager()
{
    return m_combatManager;
}