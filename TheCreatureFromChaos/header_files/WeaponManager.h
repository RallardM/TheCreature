#pragma once

#include "ScenesManager.h"

using namespace PublicConstants;

class WeaponManager
{
public:

	WeaponManager(MenuManager* menuManager);

	void SelectWeapon(E_UserInput userInput);
	void PrintBeltMenu(unsigned int short selectedWeaponIndex);

	void CheckAndPrintIfFightingLog();

	void CheckAndPrintIfFleeingLog();

	bool GetIsWeaponBeltCleared();
	void SetIsWeaponBeltCleared(bool isWeaponBeltCleared);

	unsigned short int GetCurrentWeaponIndex();
	void SetCurrentWeaponIndex(unsigned short int currentWeaponIndex);

	S_Weapon GetCurrentWeapon(unsigned short int weaponIndex);

	MenuManager* GetMenuManager();

	//void ClearWeaponLogLine();

private:
	bool m_isWeaponBeltCleared;
	S_Weapon m_currentWeapons[2];
	unsigned short int m_currentWeaponIndex;

	MenuManager* m_menuManager;
};