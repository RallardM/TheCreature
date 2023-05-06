#include "WeaponManager.h"
#include "DebugMessageSystem.h"


void WeaponManager::SelectWeapon(E_UserInput userInput)
{
	switch (userInput)
	{
	case E_UserInput::ONE:
		SetCurrentWeaponIndex(0); // Sword
		PrintBeltMenu(0);
		break;
	case E_UserInput::TWO:
		SetCurrentWeaponIndex(1); // Wand
		PrintBeltMenu(1);
		break;
	default:
		PrintBeltMenu(GetCurrentWeaponIndex());
		break;
	}
}

void WeaponManager::PrintBeltMenu(unsigned int short selectedWeaponIndex)
{
	if (GetIsMenuCleared() == false)
	{
		ClearWeaponLogLine();
	}
	std::string currentWeapon = "";
	currentWeapon = GetCurrentWeapon(selectedWeaponIndex).weaponName;
	std::cout << "  " << currentWeapon << " is equiped";
	SetIsMenuCleared(false);
}


bool WeaponManager::GetIsMenuCleared()
{
	return m_isMenuCleared;
}

void WeaponManager::SetIsMenuCleared(bool isMenuCleared)
{
	m_isMenuCleared = isMenuCleared;
}

unsigned short int WeaponManager::GetCurrentWeaponIndex()
{
	return m_currentWeaponIndex;
}

void WeaponManager::SetCurrentWeaponIndex(unsigned short int currentWeaponIndex)
{
	m_currentWeaponIndex = currentWeaponIndex;
}

S_Weapon WeaponManager::GetCurrentWeapon(unsigned short int weaponIndex)
{
	return m_currentWeapons[weaponIndex];
}

MenuManager* WeaponManager::GetMenuManager()
{
	return 	m_menuManager;
}

void WeaponManager::ClearWeaponLogLine()
{
	std::cout << "\r";
	for (int i = 0; i < 80; i++)
	{
		std::cout << " ";
	}
	std::cout << "\r";
}