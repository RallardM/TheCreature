#pragma once

class UserInputManager;
class ScenesMenuManager;
class ScenesNarrationManager;
class ScenesMenuManager;

#include "UserScenesManager.h"

class MainClass {
public:
	//void SetIsSceneCleared(bool isSceneCleared);
	//bool GetIsSceneCleared();
	void SetIsMenuCleared(bool isMenuCleared);
	bool GetIsMenuCleared();


	UserInputManager* GetMainInputManager();
	UserScenesManager* GetMainSceneManager();
	ScenesNarrationManager* GetMainNarrationManager();
	ScenesMenuManager* GetMainMenuManager();

	void SetMainInputManager(UserInputManager* inputManager);
	void SetMainSceneManager(UserScenesManager* sceneManager);
	void SetMainNarrationManager(ScenesNarrationManager* textManager);
	void SetMainMenuManager(ScenesMenuManager* menuManager);

private:
	//bool m_isSceneCleared;
	bool m_isMenuCleared;

	UserInputManager* m_inputManager;
	UserScenesManager* m_sceneManager;
	ScenesNarrationManager* m_narrationManager;
	ScenesMenuManager* m_menuManager;
};