#pragma once

class ScenesManager;

#include "ScenesManager.h"
#include "ConsoleHandler.h"
#include "PublicConstants.h"
#include "WeaponManager.h"

class CombatManager;
using namespace PublicConstants;

class UserInputManager {
public:
	UserInputManager(ConsoleHandler* m_consoleHandler, ScenesManager* sceneManager, MenuManager* menuManager, CombatManager* combatManager);
	
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

	CombatManager* GetCombatManager();

private:
	bool m_hasInput;

	ConsoleHandler* m_consoleHandler;
	MenuManager* m_menuManager;
	ScenesManager* m_sceneManager;
	WeaponManager* m_weaponManager;
	CombatManager* m_combatManager;
};
