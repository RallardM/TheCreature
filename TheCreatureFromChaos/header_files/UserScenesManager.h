#pragma once

class UserScenesManager {
public:
	enum class E_SceneSequence { NO_SCENE, INTRO_SCENE, MOVING_SCENE };

	UserScenesManager();
	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

private:
	E_SceneSequence m_userCurrentScene;
};
