#pragma once

#include "ScenesManager.h"

using namespace PublicConstants;

class WeaponManager
{
public:
	WeaponManager(MenuManager* menuManager) :
		m_menuManager(menuManager),
		m_isMenuCleared(true),
		m_currentWeaponIndex(0)
	{
		m_currentWeapons[0] = S_Weapon("Sword", 5, 15);
		m_currentWeapons[1] = S_Weapon("Wand", 10, 18);
	}

	void SelectWeapon(E_UserInput userInput);
	void PrintBeltMenu(unsigned int short selectedWeaponIndex);

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	unsigned short int GetCurrentWeaponIndex();
	void SetCurrentWeaponIndex(unsigned short int currentWeaponIndex);

	S_Weapon GetCurrentWeapon(unsigned short int weaponIndex);

	MenuManager* GetMenuManager();

	void ClearWeaponLogLine();

private:
	bool m_isMenuCleared;
	S_Weapon m_currentWeapons[2];
	unsigned short int m_currentWeaponIndex;

	MenuManager* m_menuManager;
};