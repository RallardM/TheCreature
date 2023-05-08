#include "GameplayManager.h"

GameplayManager::GameplayManager(Scenes* scenes) :
	m_scenes(scenes),
	m_combat(nullptr)
{
}

GameplayManager::~GameplayManager()
{
}

Scenes* GameplayManager::GetScenes()
{
	return m_scenes;
}

//void GameplayManager::SetScenes(Scenes* scenes)
//{
//	m_scenes = scenes;
//}

Combat* GameplayManager::GetCombat()
{
	return m_combat;
}

void GameplayManager::SetCombat(Combat* combat)
{
	m_combat = combat;
}
