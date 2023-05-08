#include <conio.h>
#include <iostream>
#include "UserInput.h"
#include "DebugMessageSystem.h"
//#include "CombatManager.h"

UserInput::UserInput() :
    //m_consoleHandler(),
    //m_weaponManager(),
    //m_combatManager(combatManager),
    //m_sceneManager(sceneManager),
    //m_menuManager(menuManager),
    m_hasInput(false)
{
    SetCurrentInputType(E_CurrentInputType::DIALOGUES);
}

E_UserInput UserInput::GetInput()
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
                case    97:    //'a':           // Attack - move left
                case    65:    //'A':
  					return E_UserInput::LEFT;
                    break;

                case    75:    // Left arrow key
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

                case   119:    //'w':           // Move forward - Khai Attack
                case    87:    //'W':
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

                case  100:     //'d':           // Move right - Potion
                case   68:     //'D':
                    return E_UserInput::RIGHT;
                    break;

                case   112:    //'p':           
                case    80:    //'P': 
                    if (GetCurrentInputType() == E_CurrentInputType::COMBAT)
                    {
                        return E_UserInput::RIGHT; // Potion
                    }
                    else if (GetCurrentInputType() == E_CurrentInputType::NAVIGATION)
                    {
                         return E_UserInput::DOWN;

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
                            return E_UserInput::RIGHT; // Potion
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

                //case    80:    // Down arrow key Taken by potion
                case   115:     //'s':
                case    83:     //'S':
                case '\033[B':  // Down arrow key
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

void UserInput::SetAction(E_UserInput userInput)
{
    bool left = (userInput == E_UserInput::LEFT);
    bool right = (userInput == E_UserInput::RIGHT);
    bool up = (userInput == E_UserInput::UP);
    bool down = (userInput == E_UserInput::DOWN);


    if (left || right || up || down)
    {
        DEBUG_MSG("UserInput.cpp : SetAction() : User is using LEFT RIGHT.");
        ActivateSelection(userInput);
        SetHasInput(false);
        return;
	}
    if (userInput == E_UserInput::ENTER)
    {
        DEBUG_MSG("UserInput.cpp : SetAction() : User pressed ENTER.");
        EnterSelection();
        SetHasInput(false);
        return;
    }
    if (userInput == E_UserInput::ONE || userInput == E_UserInput::TWO)
    {
        GetUserData()->GetWeapons()->SelectWeapon(userInput);
        SetHasInput(false);
        return;
    }
    if (userInput == E_UserInput::ESC)
    {
        DEBUG_MSG("UserInput.cpp : SetAction() : User pressed ESC.");
        return;
	}
}

void UserInput::ActivateSelection(E_UserInput userInput)
{
    E_SceneSequence currentScene = GetGameplayManager()->GetScenes()->GetPlayerCurrentScene();
    unsigned short int currentSceneEnumToInt = static_cast<int>(currentScene);
    unsigned short int currentNumberOfChoices = SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt];
    bool bidirectionalMenus = (currentNumberOfChoices == TWO_WAYS_RIGHT || currentNumberOfChoices == TWO_WAYS_LEFT);
    bool quadridiractionalMenus = (currentNumberOfChoices == FOUR_WAYS_FRONT || currentNumberOfChoices == FOUR_WAYS_BACK);
    bool combatMenu = (currentNumberOfChoices == COMBAT_MENU);

    if (currentNumberOfChoices == TWO_CHOICES_MENU)
    {
        GetOutputManager()->GetMenu()->SelectMenuFromScene(userInput);
        return;
    }
    else if (bidirectionalMenus)
    {
        if (userInput == E_UserInput::LEFT)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::LEFT);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::LR_NAVIGATION_LEFT);
        }
        else if (userInput == E_UserInput::RIGHT)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::RIGHT);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::LR_NAVIGATION_RIGHT);
        }
    }
    else if (quadridiractionalMenus)
    {
        if (userInput == E_UserInput::LEFT)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::LEFT);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::NAVIGATION_LEFT);
        }
        else if (userInput == E_UserInput::RIGHT)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::RIGHT);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::NAVIGATION_RIGHT);
        }
        else if (userInput == E_UserInput::UP)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::UP);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::NAVIGATION_FOWARD);
        }
        else if (userInput == E_UserInput::DOWN)
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::DOWN);
            GetGameplayManager()->GetScenes()->SetNextScene(E_MenuChoices::NAVIGATION_BACK);
        }
    }
    else if (combatMenu)
    {
        if (userInput == E_UserInput::LEFT) // Khail help
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::LEFT);
        }
        else if (userInput == E_UserInput::RIGHT) // Potion
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::RIGHT);
        }
        else if (userInput == E_UserInput::UP) // Attack
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::UP);
        }
        else if (userInput == E_UserInput::DOWN) // Flee
        {
            GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::DOWN);
        }
        GetGameplayManager()->GetCombat()->SetCombatAction(userInput);
    }
}

void UserInput::EnterSelection()
{
    E_SceneSequence currentScene = GetGameplayManager()->GetScenes()->GetPlayerCurrentScene();
    unsigned short int currentNumberOfChoices = SCENE_NUMBER_OF_MENU_CHOICES[int(currentScene)];
    if (currentNumberOfChoices == ONE_CHOICE_MENU)
    {
        GetOutputManager()->GetMenu()->SelectMenuFromScene(E_UserInput::ENTER);
        GetGameplayManager()->GetScenes()->SetNextScene(GetOutputManager()->GetMenu()->GetSelectedMenuLine());
        return;
	}
    else if (currentNumberOfChoices == TWO_CHOICES_MENU)
    {
        GetGameplayManager()->GetScenes()->SetNextScene(GetOutputManager()->GetMenu()->GetSelectedMenuLine());
        return;
    }
}

UserInput::E_CurrentInputType UserInput::GetCurrentInputType()
{
    return m_currentInputType;
}

void UserInput::SetCurrentInputType(E_CurrentInputType currentInputType)
{
    m_currentInputType = currentInputType;
}

bool UserInput::HasInput()
{
    return m_hasInput;
}

void UserInput::SetHasInput(bool hasInput)
{
    m_hasInput = hasInput;
}

//ConsoleHandler* UserInput::GetConsoleHandler()
//{
//    return m_consoleHandler;
//}

//Menu* UserInput::GetMenuManager()
//{
//    return m_menuManager;
//}
//
//Scenes* UserInput::GetScenesManager()
//{
//    return m_sceneManager;
//}
//
//Weapons* UserInput::GetWeaponManager()
//{
//    return m_weaponManager;
//}
//
//void UserInput::SetWeaponManager(Weapons* weaponManager)
//{
//    m_weaponManager = weaponManager;
//}

//Combat* UserInput::GetCombatManager()
//{
//    return m_combatManager;
//}

UserData* UserInput::GetUserData()
{
    return m_userData;
}

void UserInput::SetUserData(UserData* userData)
{
    m_userData = userData;
}

OutputManager* UserInput::GetOutputManager()
{
    return m_outputManager;
}

void UserInput::SetOutputManager(OutputManager* outputManager)
{
    this->m_outputManager = outputManager;
}

GameplayManager* UserInput::GetGameplayManager()
{
    return m_gameplayManager;
}

void UserInput::SetGameplayManager(GameplayManager* gameplayManager)
{
    m_gameplayManager = gameplayManager;
}
