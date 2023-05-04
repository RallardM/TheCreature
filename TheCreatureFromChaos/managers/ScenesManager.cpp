#include <iostream>

#include "ScenesManager.h"
#include "MenuManager.h"
#include "DebugMessageSystem.h"

ScenesManager::ScenesManager() :
	m_userCurrentScene(E_SceneSequence::INTRO_SCENE),
	m_narrationManager(),
	m_menuManager()
{
}

E_SceneSequence ScenesManager::GetPlayerCurrentScene()
{
	return m_userCurrentScene;
}

void ScenesManager::SetPlayerCurrentScene(E_SceneSequence scene)
{
	m_userCurrentScene = scene;
}

void ScenesManager::SetNextScene(E_MenuChoices menuChoice)
{
	ClearAllConsoleText();
	GetMenuManager()->SetIsMenuCleared(true);
	//SetIsSceneCleared(true);

	switch (menuChoice)
	{
		case E_MenuChoices::NO_MENU_LINE:
			DEBUG_MSG("#R ScenesManager.cpp : SetNextScene() : Returned no menu choice.");
			break;

		case E_MenuChoices::TRY_TO_MOVE:        // From INTRO_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set MOVING_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::MOVING_SCENE);
			break;

		case E_MenuChoices::TRY_TO_REMEBER:     // From INTRO_SCENE
		case E_MenuChoices::TRY_TO_REMEBER_TWO: // From MOVING_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set KOBOLD_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
			break;

		case E_MenuChoices::LOOK_AROUND:        // From MOVING_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set KOBOLD_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
			break;

		case E_MenuChoices::WHO_ARE_YOU:        // From KOBOLD_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set NAME_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::NAME_SCENE);
			break;

		case E_MenuChoices::ATTACK_KOBOLD:      // From KOBOLD_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set ATTACK_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::ATTACK_SCENE);
			break;

		case E_MenuChoices::ENTER_NAME:         // From NAME_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set WEAPONS_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::WEAPONS_SCENE);
			break;

		case E_MenuChoices::GO_BACK:            // From DEAD_END_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO.");
			//SetPlayerCurrentScene(E_SceneSequence::); 
			break;

		case E_MenuChoices::ATTACK_ENEMY:       // From ENNEMY_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO.");
			//SetPlayerCurrentScene(E_SceneSequence::);
			break;

		case E_MenuChoices::RUN_AWAY:           // From ENNEMY_SCENE
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO.");
			//SetPlayerCurrentScene(E_SceneSequence::);
			break;

		default:
			DEBUG_MSG("#R ScenesManager.cpp : SetNextScene() : Switch statement default case reached.");
			break;
	}
	GetNarrationManager()->PrintLinesFromScene();
}

void ScenesManager::ClearAllConsoleText()
{
	DEBUG_MSG("#Y ScenesManager.cpp : ClearAllConsoleText() : Clear whole scene debug deactivated.");
	unsigned short int numberOflinesToDelete = GetCurrentConsololeTextHeight();
	for (size_t i = 0; i < numberOflinesToDelete; i++)
	{
		GetMenuManager()->ClearConsolePreviousLine();
	}
}

unsigned short int ScenesManager::GetCurrentConsololeTextHeight()
{
	unsigned short int imageHeight           = GetNarrationManager()->ASCII_IMAGE_HEIGHT;
	unsigned short int menuHeight            = GetNarrationManager()->NARRATION_MENU_HEIGHT;
	unsigned short int textHeight            = GetNarrationManager()->STORY_TEXT_HEIGHT;
	unsigned short int navigationHeight      = GetNarrationManager()->NAVIGATION_MENU_HEIGHT;
	unsigned short int numberOflinesToDelete = 0
		;
	E_SceneSequence scene = GetPlayerCurrentScene();

	switch (scene)
	{
	case E_SceneSequence::INTRO_SCENE:
	case E_SceneSequence::MOVING_SCENE:
	case E_SceneSequence::KOBOLD_SCENE:
	case E_SceneSequence::NAME_SCENE:
	case E_SceneSequence::WEAPONS_SCENE:
	case E_SceneSequence::ATTACK_SCENE:
	case E_SceneSequence::DEAD_END_SCENE:
	case E_SceneSequence::ENNEMY_SCENE:
		numberOflinesToDelete = imageHeight + textHeight + menuHeight;
		break;
	case E_SceneSequence::ROOM_ONE_FRONT:
	case E_SceneSequence::ROOM_ONE_BACK:
	case E_SceneSequence::ROOM_TWO_FRONT:
	case E_SceneSequence::ROOM_TWO_BACK:
	case E_SceneSequence::ROOM_THREE_FRONT:
	case E_SceneSequence::ROOM_THREE_BACK:
	case E_SceneSequence::ROOM_ONE_RIGHT:
	case E_SceneSequence::ROOM_ONE_LEFT:
	case E_SceneSequence::ROOM_TWO_RIGHT:
	case E_SceneSequence::ROOM_TWO_LEFT:
	case E_SceneSequence::ROOM_THREE_RIGHT:
	case E_SceneSequence::ROOM_THREE_LEFT:
		numberOflinesToDelete = imageHeight + navigationHeight;
		break;
	default:
		break;
	}

	return numberOflinesToDelete;
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

//bool ScenesManager::GetIsSceneCleared()
//{
//	return m_isSceneCleared;
//}
//
//void ScenesManager::SetIsSceneCleared(bool isSceneCleared)
//{
//	m_isSceneCleared = isSceneCleared;
//}