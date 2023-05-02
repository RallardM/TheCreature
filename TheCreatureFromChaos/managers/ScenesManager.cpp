#include <iostream>

#include "ScenesManager.h"
#include "MenuManager.h"



ScenesManager::ScenesManager() :
	m_userCurrentScene(E_SceneSequence::INTRO_SCENE),
	m_narrationManager()
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
	//SetIsSceneCleared(true);

	switch (menuChoice)
	{
		case E_MenuChoices::NO_MENU_LINE:
			std::cout << "Error: ScenesManager::SetNextScene() returned no choice." << std::endl;
			break;

		case E_MenuChoices::TRY_TO_MOVE:
			SetPlayerCurrentScene(E_SceneSequence::MOVING_SCENE);
			break;

		case E_MenuChoices::DO_NOTHING:

			break;

		default:
			std::cout << "Error: ScenesManager::SetNextScene() switch statement default case reached." << std::endl;
			break;
	}
	GetNarrationManager()->PrintLinesFromScene();
}

void ScenesManager::ClearAllConsoleText()
{
	std::cout << "\033[2J\033[1;1H";
}

NarrationManager* ScenesManager::GetNarrationManager()
{
	return m_narrationManager;
}

void ScenesManager::SetNarrationManager(NarrationManager* narrationManager)
{
	m_narrationManager = narrationManager;
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