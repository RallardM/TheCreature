#pragma once

class MenuManager;
class NarrationManager;
class UserInputManager;

#include "MenuManager.h"
#include "NarrationManager.h"
#include "UserInputManager.h"
#include "Globals.h"

class ScenesManager {
public:
	ScenesManager();

	E_SceneSequence GetPlayerCurrentScene();

	void SetPlayerCurrentScene(E_SceneSequence scene);
	void SetNextScene(E_MenuChoices menuChoice);

	void ClearAllConsoleText();
	NarrationManager* GetNarrationManager();
	void SetNarrationManager(NarrationManager* narrationManager);

	//bool GetIsSceneCleared();
	//void SetIsSceneCleared(bool isSceneCleared);

private:
	E_SceneSequence m_userCurrentScene;
	NarrationManager* m_narrationManager;
	//bool m_isSceneCleared;
};
