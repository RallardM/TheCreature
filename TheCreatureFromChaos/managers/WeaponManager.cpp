#include "WeaponManager.h"
#include "DebugMessageSystem.h"

enum class S_Weapons : unsigned short int
{
	SWORD = 0,
	WAND = 1
};

WeaponManager::WeaponManager(MenuManager* menuManager) :
	m_menuManager(menuManager),
	m_isWeaponBeltCleared(true),
	m_currentWeaponIndex(0)
{
	m_currentWeapons[0] = S_Weapon("Sword", 5, 15);
	m_currentWeapons[1] = S_Weapon("Wand", 10, 18);
}

void WeaponManager::SelectWeapon(E_UserInput userInput)
{
	switch (userInput)
	{
	case E_UserInput::ONE:
		SetCurrentWeaponIndex(0); // Sword
		PrintBeltMenu(static_cast<unsigned int short>(S_Weapons::SWORD));
		break;
	case E_UserInput::TWO:
		SetCurrentWeaponIndex(1); // Wand
		PrintBeltMenu(static_cast<unsigned int short>(S_Weapons::WAND));
		break;
	default:
		PrintBeltMenu(GetCurrentWeaponIndex());
		break;
	}
}

void WeaponManager::PrintBeltMenu(unsigned int short selectedWeaponIndex)
{
	if (GetMenuManager()->GetNarrationManager()->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::DIALOGUES)
	{
		return;
	}
	std::string currentWeapon = "";
	std::string spaceEquilizer = "";
	unsigned short int numberOfPotions = 0;

	if (GetIsWeaponBeltCleared() == false)
	{
		//ClearWeaponLogLine();
		GetMenuManager()->ClearConsolePreviousLine();
		GetMenuManager()->GetCombatManager()->SetIsFightLogCleared(true);
	}
	if (selectedWeaponIndex == static_cast<unsigned int short>(S_Weapons::WAND))
	{
		spaceEquilizer = " ";
	}
	numberOfPotions = GetMenuManager()->GetUserData()->GetNumberOfPotions();
	currentWeapon = GetCurrentWeapon(selectedWeaponIndex).weaponName;
	std::string spacesFrame = "   ";
	std::string isEquiped = " is equiped";
	std::string postionLog = " | Number of potions : ";
	std::string jumpLine = "\n";
	std::string resultOutput = spacesFrame + currentWeapon + isEquiped + spaceEquilizer + postionLog + std::to_string(numberOfPotions) + jumpLine;
	//std::cout << "   " << currentWeapon << " is equiped" << spaceEquilizer<<" | Number of potions : " << numberOfPotions << std::endl;
	std::cout << resultOutput;
	GetMenuManager()->GetScenesManager()->GetUserData()->SetGameOutputLog(resultOutput);
	SetIsWeaponBeltCleared(false);
	GetMenuManager()->GetScenesManager()->SetIsAllConsoleTextCleared(false);
}


bool WeaponManager::GetIsWeaponBeltCleared()
{
	return m_isWeaponBeltCleared;
}

void WeaponManager::SetIsWeaponBeltCleared(bool isMenuCleared)
{
	m_isWeaponBeltCleared = isMenuCleared;
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

//void WeaponManager::ClearWeaponLogLine()
//{
//	std::cout << "\r";
//	for (int i = 0; i < 80; i++)
//	{
//		std::cout << " ";
//	}
//	std::cout << "\r";
//}