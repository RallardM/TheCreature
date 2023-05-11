#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ScenesManager.h"
#include "MenuManager.h"
#include "DebugMessageSystem.h"
#include "WeaponManager.h"
#include "PublicConstants.h"

ScenesManager::ScenesManager(UserData* userData) :
	m_userCurrentScene(E_SceneSequence::INTRO_SCENE),
	m_narrationManager(),
	m_menuManager(),
	m_weaponManager(),
	m_combatManager(),
	m_userData(userData),
	m_isAllConsoleTextCleared(true),
	m_userOpposingNavigationScene(E_SceneSequence::NO_SCENE)
{
}

void ScenesManager::SetNextScene(E_MenuChoices menuChoice)
{
	if (GetIsAllConsoleTextCleared() == false)
	{
		ClearAllConsoleText();
		SetIsAllConsoleTextCleared(true);
		GetMenuManager()->SetIsMenuCleared(true);
	}
	
	bool areWeaponsEquiped = GetUserData()->GetAreWeaponsEquiped();
	bool isWeaponBeltCleared = GetWeaponManager()->GetIsWeaponBeltCleared();
	if (areWeaponsEquiped && !isWeaponBeltCleared)
	{
		GetWeaponManager()->SetIsWeaponBeltCleared(true);
	}

	bool isCountdownStarted = GetCombatManager()->GetIsCountdownStarted();
	if (isCountdownStarted)
	{
		GetCombatManager()->SetIsCountdownLogCleared(true);
	}

	E_SceneSequence movingTowardScene = E_SceneSequence::NO_SCENE;

	switch (menuChoice)
	{
	case E_MenuChoices::NO_MENU_LINE:
		DEBUG_MSG("#R ScenesManager.cpp : SetNextScene() : Returned no menu choice.");
		break;

	case E_MenuChoices::TRY_TO_MOVE:           // From INTRO_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set MOVING_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::MOVING_SCENE);
		break;

	case E_MenuChoices::TRY_TO_REMEBER:        // From INTRO_SCENE
	case E_MenuChoices::TRY_TO_REMEBER_TWO:    // From MOVING_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set KOBOLD_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
		break;

	case E_MenuChoices::LOOK_AROUND:           // From MOVING_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set KOBOLD_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
		break;

	case E_MenuChoices::WHO_ARE_YOU:           // From KOBOLD_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set NAME_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::NAME_SCENE);
		break;

	case E_MenuChoices::ATTACK_KOBOLD:         // From KOBOLD_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set ATTACK_KOBOLD_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::ATTACK_KOBOLD_SCENE);
		break;

	case E_MenuChoices::ENTER_NAME:            // From NAME_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set WEAPONS_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::WEAPONS_SCENE);
		break;

	case E_MenuChoices::TAKE_WEAPONS_SELECTED: // From WEAPONS_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set ROOM_ONE_RIGHT.");
		GetUserData()->SetAreWeaponsEquiped(true);
		GetUserData()->SetNumberOfPotions(1);
		SetPlayerCurrentScene(E_SceneSequence::ROOM_ONE_LEFT);
		break;

	case E_MenuChoices::GO_BACK_SELECTED:      // From DEAD_END_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set ROOM_TWO_FRONT.");
		SetPlayerCurrentScene(E_SceneSequence::ROOM_TWO_FRONT);
		break;

	case E_MenuChoices::ATTACK_ENEMY:          // From ENNEMY_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set COMBAT_SCENE.");
		GetCombatManager()->FormatCountdown();
		SetPlayerCurrentScene(E_SceneSequence::COMBAT_SCENE);
		break;

	case E_MenuChoices::RUN_AWAY:              // From ENNEMY_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : calls TryToFlee."); 
		GetCombatManager()->TryToFlee();
		break;

	case E_MenuChoices::FLEEING_BACKWARD:       // From ENNEMY_SCENE 1 of 4 chance
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : .");
		if (GetCombatManager()->GetIsSecondEncounter())
		{
			SetPlayerCurrentScene(GetUserOpposingNavigationScene());
		}
		else
		{
			SetPlayerCurrentScene(E_SceneSequence::FLEEING_BACKWARD_SCENE);
		}
		GetCombatManager()->SetIsPlayerFleeing(false);
		break;

	case E_MenuChoices::FLEEING_FORWARD:       // From ENNEMY_SCENE 1 of 4 chance
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : .");
		SetPlayerCurrentScene(E_SceneSequence::FLEEING_FORWARD_SCENE);
		GetCombatManager()->SetIsPlayerFleeing(false);
		break;

	case E_MenuChoices::FLEING_FAILED_DIED:     // From ENNEMY_SCENE 1 of 4 chance
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : .");
		SetPlayerCurrentScene(E_SceneSequence::FLEING_FAILED_DIED_SCENE);
		GetCombatManager()->SetIsPlayerFleeing(false);
		break;

	case E_MenuChoices::WON_LEAVE: 		 // From COMBAT_SCENE The player won the fight
		SetPlayerCurrentScene(E_SceneSequence::VICTORY_SCENE);
		break;

	case E_MenuChoices::WON_LEAVE_SELECTED:  // From VICTORY_SCENE The player selected leave scene
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set ROOM_THREE_FRONT.");
		SetPlayerCurrentScene(E_SceneSequence::ROOM_THREE_FRONT);
		break;

	case E_MenuChoices::QUIT_GAME_SELECTED:
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Stops main loop.");
		GetMenuManager()->GetConsoleHandler()->SetIsGameRunning(false);
		break;

	case E_MenuChoices::RUN_SELECTED:
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : ROOM_THREE_BACK.");
		SetPlayerCurrentScene(E_SceneSequence::ROOM_THREE_BACK);
		GetCombatManager()->SetIsCountdownStarted(true);
		GetCombatManager()->SetIsPlayerFleeing(false);
		break;

	case E_MenuChoices::NAVIGATION_LEFT:
	case E_MenuChoices::NAVIGATION_RIGHT:
	case E_MenuChoices::NAVIGATION_FOWARD:
	case E_MenuChoices::NAVIGATION_BACK:
	case E_MenuChoices::LR_NAVIGATION_LEFT:
	case E_MenuChoices::LR_NAVIGATION_RIGHT:
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : movingTowardScene.");
		movingTowardScene = GetUserDirectionScene(menuChoice);
		SetPlayerCurrentScene(movingTowardScene);
		break;

	default:
		DEBUG_MSG("#R ScenesManager.cpp : SetNextScene() : Switch statement default case reached.");
		break;
	}

	bool isPlayerFleeingg = GetCombatManager()->GetIsPlayerFleeing();
	if (isPlayerFleeingg)
	{
		GetCombatManager()->SetIsPlayerFleeing(false);
		return;
	}

	GetNarrationManager()->PrintLinesFromScene();
}

E_SceneSequence ScenesManager::GetUserDirectionScene(E_MenuChoices playerInputDirection)
{
	E_SceneSequence currectScene = GetPlayerCurrentScene();
	E_SceneSequence nextScene = E_SceneSequence::NO_SCENE;
	E_MenuChoices intToEnum = E_MenuChoices::NO_MENU_LINE;

	unsigned short int currentSceneEnumToInt = static_cast<int>(currectScene);

	bool isFacingFront = (SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt] == FOUR_WAYS_FRONT);
	bool isFacingRight = (SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt] == TWO_WAYS_RIGHT);
	bool isFacingLeft = (SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt] == TWO_WAYS_LEFT);
	bool isFacingBack = (SCENE_NUMBER_OF_MENU_CHOICES[currentSceneEnumToInt] == FOUR_WAYS_BACK);

	bool turnsLeft = (playerInputDirection == E_MenuChoices::NAVIGATION_LEFT || playerInputDirection == E_MenuChoices::LR_NAVIGATION_LEFT);
	bool turnsRight = (playerInputDirection == E_MenuChoices::NAVIGATION_RIGHT || playerInputDirection == E_MenuChoices::LR_NAVIGATION_RIGHT);
	bool goesFoward = (playerInputDirection == E_MenuChoices::NAVIGATION_FOWARD);
	bool goesBack = (playerInputDirection == E_MenuChoices::NAVIGATION_BACK);

	if (isFacingFront && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_LEFT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_RIGHT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
		
	}
	else if (isFacingFront && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_RIGHT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_LEFT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingFront && goesBack)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_FRONT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingRight && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_BACK);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingRight && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_FRONT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingLeft && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_FRONT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingLeft && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_BACK);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingBack && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_RIGHT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_LEFT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingBack && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_LEFT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_RIGHT);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingBack && goesBack)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_BACK);
		SetUserOpposingNavigationScene(static_cast<E_SceneSequence>(intToEnum));
	}
	else if (isFacingBack && goesFoward)
	{
		if (currectScene == E_SceneSequence::ROOM_ONE_BACK)
		{
			if (GetUserData()->GetIsPlayerSeenDeadEnd())
			{
				nextScene = E_SceneSequence::ROOM_TWO_BACK;
				SetUserOpposingNavigationScene(E_SceneSequence::ROOM_TWO_FRONT);
			}
			else
			{
				nextScene = E_SceneSequence::DEAD_END_SCENE;
				GetUserData()->SetIsPlayerSeenDeadEnd(true);
				SetUserOpposingNavigationScene(E_SceneSequence::ROOM_TWO_FRONT);
			}
		}
		else if (currectScene == E_SceneSequence::ROOM_THREE_BACK)
		{
			nextScene = E_SceneSequence::ROOM_ONE_BACK;
			SetUserOpposingNavigationScene(E_SceneSequence::ROOM_ONE_FRONT);
		}
		else if (currectScene == E_SceneSequence::ROOM_TWO_BACK)
		{
			nextScene = E_SceneSequence::DEAD_END_SCENE;
			SetUserOpposingNavigationScene(E_SceneSequence::ROOM_ONE_FRONT);
		}
	}
	else if (isFacingFront && goesFoward)
	{
		if (currectScene == E_SceneSequence::ROOM_ONE_FRONT)
		{
			if (GetCombatManager()->GetIsEnemyDefeated())
			{
				if (GetUserData()->GetIsPlayerSeenVictory())
				{
					nextScene = E_SceneSequence::ROOM_THREE_FRONT;
					SetUserOpposingNavigationScene(E_SceneSequence::ROOM_THREE_BACK);
				}
				else
				{
					nextScene = E_SceneSequence::VICTORY_SCENE;
				}
			}
			else
			{
				nextScene = E_SceneSequence::ENNEMY_SCENE;
				SetUserOpposingNavigationScene(E_SceneSequence::ROOM_THREE_BACK);
			}
		}
		else if (currectScene == E_SceneSequence::ROOM_TWO_FRONT)
		{
			nextScene = E_SceneSequence::ROOM_ONE_FRONT;
			SetUserOpposingNavigationScene(E_SceneSequence::ROOM_ONE_BACK);
		}
		else if (currectScene == E_SceneSequence::ROOM_THREE_FRONT)
		{
			LoadEndingScene();
		}
	}

	return nextScene;
}

void ScenesManager::LoadEndingScene()
{
	SDL_Init(SDL_INIT_VIDEO);

	// Load the image using SDL_image
	SDL_Surface* surface = IMG_Load("resource_files/GameArtEnding.jpg");
	if (!surface)
	{
		std::cout << "Could not read the image" << std::endl;
		return;
	}

	// Create a window and renderer
	SDL_Window* window = SDL_CreateWindow("Window name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, surface->w, surface->h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create a texture from the image surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Render the texture to the screen
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	// Wait for user input
	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		{
			break;
		}
	}

	// Clean up resources
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ScenesManager::ClearAllConsoleText()
{
	system("cls");
}

NarrationManager* ScenesManager::GetNarrationManager()
{
	return m_narrationManager;
}

void ScenesManager::SetNarrationManager(NarrationManager* narrationManager)
{
	m_narrationManager = narrationManager;
}

MenuManager* ScenesManager::GetMenuManager()
{
	return m_menuManager;
}

void ScenesManager::SetMenuManager(MenuManager* menuManager)
{
	m_menuManager = menuManager;
}

WeaponManager* ScenesManager::GetWeaponManager()
{
	return m_weaponManager;
}

void ScenesManager::SetWeaponManager(WeaponManager* weaponManager)
{
	m_weaponManager = weaponManager;
}

UserData* ScenesManager::GetUserData()
{
	return m_userData;
}

void ScenesManager::SetUserData(UserData* userData)
{
	m_userData = userData;
}

CombatManager* ScenesManager::GetCombatManager()
{
	return m_combatManager;
}

void ScenesManager::SetCombatManager(CombatManager* combatManager)
{
	m_combatManager = combatManager;
}

bool ScenesManager::GetIsAllConsoleTextCleared()
{
	return m_isAllConsoleTextCleared;
}

void ScenesManager::SetIsAllConsoleTextCleared(bool isAllConsoleTextCleared)
{
	m_isAllConsoleTextCleared = isAllConsoleTextCleared;
}

E_SceneSequence ScenesManager::GetPlayerCurrentScene()
{
	return m_userCurrentScene;
}

void ScenesManager::SetPlayerCurrentScene(E_SceneSequence scene)
{
	m_userCurrentScene = scene;
}

E_SceneSequence ScenesManager::GetUserOpposingNavigationScene()
{
	return m_userOpposingNavigationScene;
}

void ScenesManager::SetUserOpposingNavigationScene(E_SceneSequence userLastNavigationScene)
{
	m_userOpposingNavigationScene = userLastNavigationScene;
}
