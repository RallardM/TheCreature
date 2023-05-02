#pragma once

class MenuManager; 
#include "MenuManager.h"

class ScenesManager {
public:
	enum class E_SceneSequence {
		//  NarrationManager.cpp m_sceneMenuLines{ 1, 6 }
		NO_SCENE = -1, 
		INTRO_SCENE = 0, // line 1 
		MOVING_SCENE = 2, // line 6
	};

	ScenesManager();

	E_SceneSequence GetPlayerCurrentScene();

	void SetPlayerCurrentScene(E_SceneSequence scene);
	void SetNextScene(E_MenuChoices menuChoice);

	void ClearAllConsoleText();

private:
	E_SceneSequence m_userCurrentScene;
};
