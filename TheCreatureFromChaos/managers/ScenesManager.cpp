#include <iostream>
//#include <opencv2/opencv.hpp>

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
	m_userData(userData)
{
}

void ScenesManager::SetNextScene(E_MenuChoices menuChoice)
{
	ClearAllConsoleText();
	GetMenuManager()->SetIsMenuCleared(true);
	if (GetUserData()->GetAreWeaponsEquiped() == true)
	{
		GetWeaponManager()->SetIsWeaponBeltCleared(true);
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
		SetPlayerCurrentScene(E_SceneSequence::COMBAT_SCENE);
		break;

	case E_MenuChoices::RUN_AWAY:              // From ENNEMY_SCENE
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO."); // TODO
		GetCombatManager()->TryToFlee();
		break;

	case E_MenuChoices::PLAYER_WON_SELECTED:
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set VICTORY_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::ROOM_THREE_FRONT);
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

	case E_MenuChoices::PLAYER_DIED:
		DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set DEAD_END_SCENE.");
		SetPlayerCurrentScene(E_SceneSequence::YOU_DIED_SCENE);
		break;

	case E_MenuChoices::PLAYER_WON:
		SetPlayerCurrentScene(E_SceneSequence::VICTORY_SCENE);
		break;

	default:
		DEBUG_MSG("#R ScenesManager.cpp : SetNextScene() : Switch statement default case reached.");
		break;
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
	}
	else if (isFacingFront && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_RIGHT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingFront && goesBack)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + FRONT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingRight && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingRight && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + RIGHT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingLeft && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_BACK);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingLeft && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + LEFT_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingBack && turnsLeft)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_RIGHT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingBack && turnsRight)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_LEFT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingBack && goesBack)
	{
		intToEnum = static_cast<E_MenuChoices>(currentSceneEnumToInt + BACK_TO_FRONT);
		nextScene = static_cast<E_SceneSequence>(intToEnum);
	}
	else if (isFacingBack && goesFoward)
	{
		if (currectScene == E_SceneSequence::ROOM_ONE_BACK)
		{
			if (GetUserData()->GetIsPlayerSeenDeadEnd())
			{
				nextScene = E_SceneSequence::ROOM_TWO_BACK;
			}
			else
			{
				nextScene = E_SceneSequence::DEAD_END_SCENE;
				GetUserData()->SetIsPlayerSeenDeadEnd(true);
			}
		}
		else if (currectScene == E_SceneSequence::ROOM_THREE_BACK)
		{
			nextScene = E_SceneSequence::ROOM_ONE_BACK;
		}
		else if (currectScene == E_SceneSequence::ROOM_TWO_BACK)
		{
			nextScene = E_SceneSequence::DEAD_END_SCENE;
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
				}
				else
				{
					nextScene = E_SceneSequence::VICTORY_SCENE;
				}
			}
			else
			{
				nextScene = E_SceneSequence::ENNEMY_SCENE;
			}
		}
		else if (currectScene == E_SceneSequence::ROOM_TWO_FRONT)
		{
			nextScene = E_SceneSequence::ROOM_ONE_FRONT;
		}
		else if (currectScene == E_SceneSequence::ROOM_THREE_FRONT)
		{
			// TODO the end
			
		}
	}
	return nextScene;
}

void ScenesManager::ClearAllConsoleText()
{
	DEBUG_MSG("#Y ScenesManager.cpp : ClearAllConsoleText() : Clear whole scene debug deactivated.");
	system("cls");
	//unsigned short int numberOflinesToDelete = GetCurrentConsololeTextHeight();
	//for (size_t i = 0; i < numberOflinesToDelete; i++)
	//{
	//	GetMenuManager()->ClearConsolePreviousLine();
	//}
}

//unsigned short int ScenesManager::GetCurrentConsololeTextHeight()
//{
//	unsigned short int imageHeight           = GetNarrationManager()->ASCII_IMAGE_HEIGHT;
//	unsigned short int menuHeight            = GetNarrationManager()->NARRATION_MENU_HEIGHT;
//	unsigned short int textHeight            = GetNarrationManager()->STORY_TEXT_HEIGHT;
//	unsigned short int navigationHeight      = GetNarrationManager()->NAVIGATION_MENU_HEIGHT;
//	unsigned short int numberOflinesToDelete = 0
//		;
//	E_SceneSequence scene = GetPlayerCurrentScene();
//
//	switch (scene)
//	{
//	case E_SceneSequence::INTRO_SCENE:
//	case E_SceneSequence::MOVING_SCENE:
//	case E_SceneSequence::KOBOLD_SCENE:
//	case E_SceneSequence::NAME_SCENE:
//	case E_SceneSequence::WEAPONS_SCENE:
//	case E_SceneSequence::ATTACK_KOBOLD_SCENE:
//	case E_SceneSequence::DEAD_END_SCENE:
//	case E_SceneSequence::ENNEMY_SCENE:
//		numberOflinesToDelete = imageHeight + textHeight + menuHeight;
//		break;
//	case E_SceneSequence::ROOM_ONE_FRONT:
//	case E_SceneSequence::ROOM_ONE_BACK:
//	case E_SceneSequence::ROOM_TWO_FRONT:
//	case E_SceneSequence::ROOM_TWO_BACK:
//	case E_SceneSequence::ROOM_THREE_FRONT:
//	case E_SceneSequence::ROOM_THREE_BACK:
//	case E_SceneSequence::ROOM_ONE_RIGHT:
//	case E_SceneSequence::ROOM_ONE_LEFT:
//	case E_SceneSequence::ROOM_TWO_RIGHT:
//	case E_SceneSequence::ROOM_TWO_LEFT:
//	case E_SceneSequence::ROOM_THREE_RIGHT:
//	case E_SceneSequence::ROOM_THREE_LEFT:
//		numberOflinesToDelete = imageHeight + navigationHeight;
//		break;
//	default:
//		break;
//	}
//
//	return numberOflinesToDelete;
//}

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


E_SceneSequence ScenesManager::GetPlayerCurrentScene()
{
	return m_userCurrentScene;
}

void ScenesManager::SetPlayerCurrentScene(E_SceneSequence scene)
{
	m_userCurrentScene = scene;
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