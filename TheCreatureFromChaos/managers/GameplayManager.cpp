#include "GameplayManager.h"

GameplayManager::GameplayManager(Scenes* scenes, Combat* combat) :
	m_scenes(scenes), 
	m_combat(combat)
{
}

GameplayManager::~GameplayManager()
{
}

Scenes* GameplayManager::GetScenes()
{
	return m_scenes;
}

Combat* GameplayManager::GetCombat()
{
	return m_combat;
}
