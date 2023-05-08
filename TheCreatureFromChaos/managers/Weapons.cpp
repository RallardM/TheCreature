#include "Weapons.h"
#include "DebugMessageSystem.h"


Weapons::Weapons() :
	//m_menuManager(menuManager),
	m_isMenuCleared(true),
	m_currentWeaponIndex(0)
{
	m_currentWeapons[0] = S_Weapon("Sword", 5, 15);
	m_currentWeapons[1] = S_Weapon("Wand", 10, 18);
}

void Weapons::SelectWeapon(E_UserInput userInput)
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

void Weapons::PrintBeltMenu(unsigned int short selectedWeaponIndex)
{
	std::string currentWeapon = "";
	unsigned short int numberOfPotions = 0;

	if (GetIsMenuCleared() == false)
	{
		ClearWeaponLogLine();
	}
	numberOfPotions = GetOutputManager()->GetMenu()->GetUserData()->GetNumberOfPotions();
	currentWeapon = GetCurrentWeapon(selectedWeaponIndex).weaponName;
	std::cout << "   " << currentWeapon << " is equiped | Number of potions : " << numberOfPotions;
	SetIsMenuCleared(false);
}


bool Weapons::GetIsMenuCleared()
{
	return m_isMenuCleared;
}

void Weapons::SetIsMenuCleared(bool isMenuCleared)
{
	m_isMenuCleared = isMenuCleared;
}

unsigned short int Weapons::GetCurrentWeaponIndex()
{
	return m_currentWeaponIndex;
}

void Weapons::SetCurrentWeaponIndex(unsigned short int currentWeaponIndex)
{
	m_currentWeaponIndex = currentWeaponIndex;
}

S_Weapon Weapons::GetCurrentWeapon(unsigned short int weaponIndex)
{
	return m_currentWeapons[weaponIndex];
}

//Menu* Weapons::GetMenuManager()
//{
//	return 	m_menuManager;
//}

void Weapons::ClearWeaponLogLine()
{
	std::cout << "\r";
	for (int i = 0; i < 80; i++)
	{
		std::cout << " ";
	}
	std::cout << "\r";
}

OutputManager* Weapons::GetOutputManager()
{
	return m_outputManager;
}

void Weapons::SetOutputManager(OutputManager* outputManager)
{
	m_outputManager = outputManager;
}
