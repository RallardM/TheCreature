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

		case E_MenuChoices::TRY_TO_MOVE:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set MOVING_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::MOVING_SCENE);
			break;

		case E_MenuChoices::TRY_TO_REMEBER:
		case E_MenuChoices::TRY_TO_REMEBER_TWO:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set KOBOLD_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
			break;

		case E_MenuChoices::LOOK_AROUND:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO.");
			SetPlayerCurrentScene(E_SceneSequence::KOBOLD_SCENE);
			break;

		case E_MenuChoices::WHO_ARE_YOU:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set NAME_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::NAME_SCENE);
			break;

		case E_MenuChoices::ATTACK_KOBOLD:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : Set NAME_SCENE.");
			SetPlayerCurrentScene(E_SceneSequence::ATTACK_SCENE);
			break;

		case E_MenuChoices::GO_BACK:
			DEBUG_MSG("ScenesManager.cpp : SetNextScene() : TODO.");
			//SetPlayerCurrentScene(E_SceneSequence::);
			break;

		case E_MenuChoices::ATTACK_ENEMY:
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
	//std::cout << "\033[2J\033[1;1H";
	// TO DO: Call multiple std::cout << "\033[1A\033[0K"; in MenuManager::ClearConsolePreviousLine() instead
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