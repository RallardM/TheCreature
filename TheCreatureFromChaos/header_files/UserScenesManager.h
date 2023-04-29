#pragma once

class UserScenesManager {
public:
	enum class E_SceneSequence { INTRO, MOVING };

	UserScenesManager();
	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

private:
	E_SceneSequence m_userCurrentScene;
};
