#pragma once

#include "Scenes.h"
class Scenes;
#include "Combat.h"
class Combat;

class GameplayManager
{
public:
	GameplayManager(Scenes* scenes, Combat* combat);
	~GameplayManager();

	Scenes* GetScenes();
	Combat* GetCombat();

private:
	Scenes* m_scenes;
	Combat* m_combat;
};

