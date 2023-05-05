#pragma once

class MenuManager;
class NarrationManager;
class UserInputManager;
#include "UserData.h"

#include "MenuManager.h"
#include "NarrationManager.h"
#include "UserInputManager.h"
#include "ScenesControllers.h"

using namespace ScenesControllers;

class ScenesManager {
public:
	ScenesManager(UserData* userData);

	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);
	void SetNextScene(E_MenuChoices menuChoice);
	E_SceneSequence GetUserDirectionScene(E_MenuChoices playerInputDirection);

	void ClearAllConsoleText();
	unsigned short int GetCurrentConsololeTextHeight();

	NarrationManager* GetNarrationManager();
	void SetNarrationManager(NarrationManager* narrationManager);

	MenuManager* GetMenuManager();
	void SetMenuManager(MenuManager* menuManager);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

private:
	E_SceneSequence m_userCurrentScene;
	NarrationManager* m_narrationManager;
	MenuManager* m_menuManager;
	UserData* m_userData;
};
