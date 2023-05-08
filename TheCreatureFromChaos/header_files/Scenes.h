#pragma once

class Menu;
class Narration;
class UserInput;
class Weapons;

#include "UserData.h"
class UserData;
#include "PublicConstants.h"
#include "OutputManager.h"
class OutputManager;
#include "Combat.h"
class Combat;
//#include "GameplayManager.h"
//class GameplayManager;

using namespace PublicConstants;

class Scenes {
public:
	Scenes();

	void SetNextScene(E_MenuChoices menuChoice);
	E_SceneSequence GetUserDirectionScene(E_MenuChoices playerInputDirection);

	void ClearAllConsoleText();

	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	OutputManager* GetOutputManager();
	void SetOutputManager(OutputManager* outputManager);

	Combat* GetCombat();
	void SetCombat(Combat* combat);

	//GameplayManager* GetGameplayManager();
	//void SetGameplayManager(GameplayManager* gameplayManager);

private:
	E_SceneSequence m_userCurrentScene;
	OutputManager* m_outputManager;
	UserData* m_userData;
	Combat* m_combat;
	//GameplayManager* m_gameplayManager;
};
