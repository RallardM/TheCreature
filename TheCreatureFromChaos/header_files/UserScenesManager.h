#pragma once

enum class E_SceneSequence { INTRO, MOVING };

class UserScenesManager {
public:
	UserScenesManager();
	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);

private:
	E_SceneSequence m_userCurrentScene;
};
