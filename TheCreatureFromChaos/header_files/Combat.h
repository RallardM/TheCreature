#pragma once
//#include "ScenesManager.h"

#include "PublicConstants.h"
#include "UserData.h"
class UserData;
using namespace PublicConstants;
class Combat
{
public:
	Combat();

	void SetCombatAction(E_UserInput userInput);

	void PlayerAttack();
	void EnnemyAttack();
	void InflictDamage(short int hitPoints);

	void PrintCausaltyLog(std::string logText, short int hitPoints);

	//Weapons* GetWeaponManager();
	//void SetWeaponManager(Weapons* weaponManager);

	short int GetEnnemyLifePoints();
	void SetEnnemyLifePoints(short int ennemyLifePoints);

	//UserData* GetUserData();
	//void SetUserData(UserData* userData);

	unsigned short int GetEnemyHitPoints();

	bool GetIsFightLogCleared();
	void SetIsFightLogCleared(bool fightLogState);

	bool GetIsEnemyDefeated();
	void SetIsEnemyDefeated(bool isEnemyDefeated);

	bool GetIsFightStarted();
	void SetIsFightStarted(bool isFightStarted);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

private:
	UserData* m_userData;

	short int m_ennemyLifePoints;
	unsigned short int m_enemyHitPoints;
	//Weapons* m_weaponManager;
	//UserData* m_userData;
	bool m_isFightLogCleared;
	bool m_isEnemyDefeated;
	bool m_isFightStarted;
};