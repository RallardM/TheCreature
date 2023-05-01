#include "ScenesManager.h"
#include <iostream>

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
