#pragma once

class MenuManager;
class NarrationManager;
class UserInputManager;
class WeaponManager;

#include "UserData.h"
#include "MenuManager.h"
#include "NarrationManager.h"
#include "UserInputManager.h"
#include "ScenesConstants.h"

using namespace ScenesConstants;

class ScenesManager {
public:
	ScenesManager(UserData* userData);

	E_SceneSequence GetPlayerCurrentScene();
	void SetPlayerCurrentScene(E_SceneSequence scene);
	void SetNextScene(MenuManager::E_MenuChoices menuChoice);
	E_SceneSequence GetUserDirectionScene(MenuManager::E_MenuChoices playerInputDirection);

	void ClearAllConsoleText();

	NarrationManager* GetNarrationManager();
	void SetNarrationManager(NarrationManager* narrationManager);

	MenuManager* GetMenuManager();
	void SetMenuManager(MenuManager* menuManager);

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

private:
	E_SceneSequence m_userCurrentScene;

	NarrationManager* m_narrationManager;
	MenuManager* m_menuManager;
	WeaponManager* m_weaponManager;

	UserData* m_userData;
};
