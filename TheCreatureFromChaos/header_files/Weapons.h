#pragma once

#include "PublicConstants.h"
#include "OutputManager.h"
class OutputManager;

//#include "ScenesManager.h"

using namespace PublicConstants;

class Weapons
{
public:
	Weapons();

	void SelectWeapon(E_UserInput userInput);
	void PrintBeltMenu(unsigned int short selectedWeaponIndex);

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	unsigned short int GetCurrentWeaponIndex();
	void SetCurrentWeaponIndex(unsigned short int currentWeaponIndex);

	S_Weapon GetCurrentWeapon(unsigned short int weaponIndex);

	//Menu* GetMenuManager();

	void ClearWeaponLogLine();

	OutputManager* GetOutputManager();
	void SetOutputManager(OutputManager* outputManager);

private:
	bool m_isMenuCleared;
	S_Weapon m_currentWeapons[2];
	unsigned short int m_currentWeaponIndex;

	OutputManager* m_outputManager;
	//Menu* m_menuManager;
};