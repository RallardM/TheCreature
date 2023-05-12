#pragma once


class MainClass
{
public:
	MainClass();
	~MainClass();

	void InitializeConsoleHandler();

	void InitializeClasses();

	NarrationManager* GetNarrationManager();
	void SetNarrationManager(NarrationManager* narrationManager);

	UserInputManager* GetUserInputManager();
	void SetUserInputManager(UserInputManager* useInputManager);

	MenuManager* GetMenuManager();
	void SetMenuManager(MenuManager* menuManager);

	CombatManager* GetCombatManager();
	void SetCombatManager(CombatManager* combatManager);

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* m_weaponManager);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	ScenesManager* GetScenesManager();
	void SetScenesManager(ScenesManager* scenesManager);

	ConsoleHandler* GetConsoleHandler();
	void SetConsoleHandler(ConsoleHandler* consoleHandler);

private:
	NarrationManager* m_narrationManager;
	MenuManager* m_menuManager;
	CombatManager* m_combatManager;
	UserInputManager* m_userInputManager;
	WeaponManager* m_weaponManager;
	UserData* m_userData;
	ScenesManager* m_scenesManager;
	ConsoleHandler* m_consoleHandler;
};