#pragma once
#include "ScenesManager.h"

class CombatManager
{
public:
	CombatManager(UserData* userData);

	void SetCombatAction(E_UserInput userInput);

	void PlayerAttack();
	void EnnemyAttack();
	void InflictDamage(short int hitPoints);

	void PrintCausaltyLog(std::string logText, short int hitPoints);

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

	short int GetEnnemyLifePoints();
	void SetEnnemyLifePoints(short int ennemyLifePoints);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	unsigned short int GetEnemyHitPoints();

	bool GetIsFightLogFull();
	void SetIsFightLogFull(bool fightLogState);

private:
	short int m_ennemyLifePoints;
	unsigned short int m_enemyHitPoints;
	WeaponManager* m_weaponManager;
	UserData* m_userData;
	bool m_isFightLogFull;
};