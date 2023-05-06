#pragma once

class ScenesManager;

#include "ScenesManager.h"
#include "ConsoleHandler.h"
#include "PublicConstants.h"
#include "WeaponManager.h"
using namespace PublicConstants;

class UserInputManager {
public:
	UserInputManager(ConsoleHandler* m_consoleHandler, ScenesManager* sceneManager, MenuManager* menuManager);
	
	void ActivateSelection(E_UserInput userInput);
	void EnterSelection();

	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(E_UserInput userInput);

	ConsoleHandler* GetConsoleHandler();
	MenuManager* GetMenuManager();
	ScenesManager* GetScenesManager();

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

private:
	bool m_hasInput;

	ConsoleHandler* m_consoleHandler;
	MenuManager* m_menuManager;
	ScenesManager* m_sceneManager;
	WeaponManager* m_weaponManager;
};
