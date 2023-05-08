#include <random>
#include <string>

#include "Combat.h"
#include "DebugMessageSystem.h"

Combat::Combat() :
	m_ennemyLifePoints(50),
	m_enemyHitPoints(10),
	m_isEnemyDefeated(false),
	m_isFightStarted(false),
	m_isFightLogCleared(true),
	m_userData(nullptr)
{
}

void Combat::SetCombatAction(E_UserInput userInput)
{
	switch (userInput)
	{		
	case PublicConstants::E_UserInput::LEFT: // Khail help
		PlayerAttack();
		//EnnemyAttack();
		break;

	case PublicConstants::E_UserInput::RIGHT: // Potion

		EnnemyAttack();
		break;

	case PublicConstants::E_UserInput::UP: // Attack

		EnnemyAttack();
		break;

	case PublicConstants::E_UserInput::DOWN: // Flee
		break;

	default:
		// TODO: Add error message
		break;

	}
}

void Combat::PlayerAttack()
{
	S_Weapon currentWeapon = GetUserData()->GetWeapons()->GetCurrentWeapon(GetUserData()->GetWeapons()->GetCurrentWeaponIndex());

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

void Combat::EnnemyAttack()
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

void Combat::InflictDamage(short int hitPoints)
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

void Combat::PrintCausaltyLog(std::string logText, short int hitPoints)
{
	if (GetIsFightLogCleared())
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
	SetIsFightLogCleared(true);
}

short int Combat::GetEnnemyLifePoints()
{
	return m_ennemyLifePoints;
}

void Combat::SetEnnemyLifePoints(short int ennemyLifePoints)
{
	m_ennemyLifePoints = ennemyLifePoints;
}

unsigned short int Combat::GetEnemyHitPoints()
{
	return m_enemyHitPoints;
}

bool Combat::GetIsFightLogCleared()
{
	return m_isFightLogCleared;
}

void Combat::SetIsFightLogCleared(bool fightLogState)
{
	m_isFightLogCleared = fightLogState;
}

bool Combat::GetIsEnemyDefeated()
{
	return m_isEnemyDefeated;
}

void Combat::SetIsEnemyDefeated(bool isEnemyDefeated)
{
	m_isEnemyDefeated = isEnemyDefeated;
}

bool Combat::GetIsFightStarted()
{
	return m_isFightStarted;
}

void Combat::SetIsFightStarted(bool isFightStarted)
{
	m_isFightStarted = isFightStarted;
}

UserData* Combat::GetUserData()
{
	return m_userData;
}

void Combat::SetUserData(UserData* userData)
{
	m_userData = userData;
}
