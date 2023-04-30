#pragma once

class UserScenesManager {
public:
	enum class E_SceneSequence {
		//  GameTextManager.cpp m_sceneMenuLines{ 1, 6 }
		NO_SCENE = -1, 
		INTRO_SCENE = 0, // line 1 
		MOVING_SCENE = 2, // line 6
	};

	UserScenesManager();
	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

private:
	E_SceneSequence m_userCurrentScene;
};
