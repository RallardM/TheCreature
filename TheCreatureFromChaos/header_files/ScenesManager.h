#pragma once

class MenuManager;
class NarrationManager;
class UserInputManager;

#include "MenuManager.h"
#include "NarrationManager.h"
#include "UserInputManager.h"
#include "ScenesControllers.h"

using namespace ScenesControllers;



class ScenesManager {
public:
	ScenesManager();


	E_SceneSequence GetPlayerCurrentScene();

	void SetPlayerCurrentScene(E_SceneSequence scene);
	void SetNextScene(E_MenuChoices menuChoice);

	void ClearAllConsoleText();

	NarrationManager* GetNarrationManager();
	void SetNarrationManager(NarrationManager* narrationManager);

	MenuManager* GetMenuManager();
	void SetMenuManager(MenuManager* menuManager);
	//bool GetIsSceneCleared();
	//void SetIsSceneCleared(bool isSceneCleared);

private:
	E_SceneSequence m_userCurrentScene;
	NarrationManager* m_narrationManager;
	MenuManager* m_menuManager;
	//bool m_isSceneCleared;
};
