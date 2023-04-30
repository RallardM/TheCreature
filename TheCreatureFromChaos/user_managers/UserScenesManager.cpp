#include "UserScenesManager.h"

UserScenesManager::UserScenesManager() :
	m_userCurrentScene(E_SceneSequence::INTRO_SCENE)
{
}

UserScenesManager::E_SceneSequence UserScenesManager::GetPlayerCurrentScene()
{
	return m_userCurrentScene;
}

void UserScenesManager::SetPlayerCurrentScene(E_SceneSequence scene)
{
	m_userCurrentScene = scene;
}
