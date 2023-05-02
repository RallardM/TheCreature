#include <iostream>

#include "ScenesManager.h"
#include "MenuManager.h"

ScenesManager::ScenesManager() :
	m_userCurrentScene(E_SceneSequence::INTRO_SCENE)
{
}

ScenesManager::E_SceneSequence ScenesManager::GetPlayerCurrentScene()
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

	switch (menuChoice)
	{
		case E_MenuChoices::G_NO_MENU_LINE:
			std::cout << "Error: ScenesManager::SetNextScene() returned no choice." << std::endl;
			break;
		case E_MenuChoices::G_TRY_TO_MOVE:

			break;
		case E_MenuChoices::G_DO_NOTHING:

			break;
		default:
			std::cout << "Error: ScenesManager::SetNextScene() switch statement default case reached." << std::endl;
			break;
	}
}

void ScenesManager::ClearAllConsoleText()
{
	std::cout << "\033[2J\033[1;1H";
}