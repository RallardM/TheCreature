#include <random>
#include <string>

#include "CombatManager.h"
#include "DebugMessageSystem.h"
#include "PublicConstants.h"


CombatManager::CombatManager(UserData* userData, MenuManager* menuManager) :
	m_ennemyLifePoints(50),
	m_enemyHitPoints(10),
	m_weaponManager(nullptr),
	m_userData(userData),
	m_menuManager(menuManager),
	m_isEnemyDefeated(false),
	m_isFightStarted(false),
	m_isFightLogCleared(true)
{
}

void CombatManager::SetCombatAction(E_UserInput userInput)
{
	switch (userInput)
	{		
	case PublicConstants::E_UserInput::LEFT: // Attack
		ClearLastCombatAction();
		GetMenuManager()->SelectMenuFromScene(E_UserInput::EMPTY);
		GetWeaponManager()->SelectWeapon(E_UserInput::EMPTY);
		PlayerAttack();
		
		break;

	case PublicConstants::E_UserInput::RIGHT: // Potion

		ClearLastCombatAction();
		//EnnemyAttack();
		break;

	case PublicConstants::E_UserInput::UP:  // Khail help

		ClearLastCombatAction();
		//EnnemyAttack();
		break;

	case PublicConstants::E_UserInput::DOWN: // Flee
		break;

	default:
		// TODO: Add error message
		break;

	}
	//GetWeaponManager()->SelectWeapon(E_UserInput::EMPTY);
}

void CombatManager::ClearLastCombatAction()
{
	GetWeaponManager()->ClearWeaponLogLine();
	GetMenuManager()->ClearConsoleNavigationMenu();
	//GetMenuManager()->SetIsMenuCleared(true);
	//SetIsFightLogCleared(true);
	//GetWeaponManager()->SetIsMenuCleared(true);
}

void CombatManager::PlayerAttack()
{
	S_Weapon currentWeapon = GetWeaponManager()->GetCurrentWeapon(GetWeaponManager()->GetCurrentWeaponIndex());

	// Random hit point between the current weapon min and max hit points or fail
	// 
	// Create a random number generator and distribution for hit points
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(currentWeapon.minHitPoints, currentWeapon.maxHitPoints);

	std::string playerHitLog = "";

	// Generate a random hit point value between the current weapon min and max hit points
	unsigned short int hitPoints = dist(gen);

	std::bernoulli_distribution zeroDist(0.2); // Probability of zero/fail
	if (zeroDist(gen)) 
	{
		hitPoints = 0;
	}

	if (hitPoints == 0)
	{
		playerHitLog = "                            You missed!";
	}
	else
	{
		playerHitLog = "              You hit the monster : ";
	}

	InflictDamage(hitPoints);
	PrintCausaltyLog(playerHitLog, hitPoints);
}

void CombatManager::EnnemyAttack()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::string ennemyHitLog = "";

	short int hitPoints = GetEnemyHitPoints();

	std::bernoulli_distribution zeroDist(0.5); // Probability of zero/fail
	if (zeroDist(gen))
	{
		hitPoints = 0;
	}

	if (hitPoints == 0)
	{
		ennemyHitLog = "                    The monster missed!";
	}
	else
	{
		ennemyHitLog = "              The monster hit you : ";
	}
	
	InflictDamage(hitPoints);
	PrintCausaltyLog(ennemyHitLog, hitPoints);
}

void CombatManager::InflictDamage(short int hitPoints)
{
	short int resultingCausalty = GetEnnemyLifePoints() - hitPoints;
	if (resultingCausalty <= 0)
	{
		SetEnnemyLifePoints(0);
		SetIsEnemyDefeated(true);
	}
	else
	{
		SetEnnemyLifePoints(resultingCausalty);
	}
}

void CombatManager::PrintCausaltyLog(std::string logText, short int hitPoints)
{
	if (!GetIsFightLogCleared())
	{
		for (size_t i = 0; i < 40; i++)
		{
			std::cout << "\b";
		}
	}
	if (hitPoints == 0)
	{
		std::cout << logText;
	}
	else if (hitPoints < 0 && hitPoints > 10)      // To fit the number of max characters 
	{											   // to remove in the log
		std::cout << logText << " -" << hitPoints; // add a space before the minus sign
	}
	else
	{
		std::cout << logText << "-" << hitPoints;
	}
	SetIsFightLogCleared(false);
}

WeaponManager* CombatManager::GetWeaponManager()
{
	return m_weaponManager;
}

void CombatManager::SetWeaponManager(WeaponManager* weaponManager)
{
	m_weaponManager = weaponManager;
}

short int CombatManager::GetEnnemyLifePoints()
{
	return m_ennemyLifePoints;
}

void CombatManager::SetEnnemyLifePoints(short int ennemyLifePoints)
{
	m_ennemyLifePoints = ennemyLifePoints;
}

UserData* CombatManager::GetUserData()
{
	return m_userData;
}

void CombatManager::SetUserData(UserData* userData)
{
	m_userData = userData;
}

unsigned short int CombatManager::GetEnemyHitPoints()
{
	return m_enemyHitPoints;
}

bool CombatManager::GetIsFightLogCleared()
{
	return m_isFightLogCleared;
}

void CombatManager::SetIsFightLogCleared(bool fightLogState)
{
	m_isFightLogCleared = fightLogState;
}

bool CombatManager::GetIsEnemyDefeated()
{
	return m_isEnemyDefeated;
}

void CombatManager::SetIsEnemyDefeated(bool isEnemyDefeated)
{
	m_isEnemyDefeated = isEnemyDefeated;
}

bool CombatManager::GetIsFightStarted()
{
	return m_isFightStarted;
}

void CombatManager::SetIsFightStarted(bool isFightStarted)
{
	m_isFightStarted = isFightStarted;
}

void CombatManager::ClearAllConsoleText()
{
	system("cls");
}

MenuManager* CombatManager::GetMenuManager()
{
	return m_menuManager;
}
