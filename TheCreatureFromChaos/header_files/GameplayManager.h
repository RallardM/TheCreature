#pragma once

#include "Scenes.h"
class Scenes;
#include "Combat.h"
class Combat;

class GameplayManager
{
public:
	GameplayManager(Scenes* scenes);
	~GameplayManager();

	Scenes* GetScenes();
	//void SetScenes(Scenes* scenes);

	Combat* GetCombat();
	void SetCombat(Combat* combat);

private:
	Scenes* m_scenes;
	Combat* m_combat;
};

