#pragma once
#include "ScenesManager.h"
#include "MenuManager.h"

class CombatManager
{
public:
	CombatManager(UserData* userData, MenuManager* menuManager);

	void SetCombatAction(E_UserInput userInput);

	void RefreshMenuAndLogFrame();

	void PlayerAttack();
	void EnemyCounterAttack();

	void TakePotion();

	void InflictDamage(short int hitPoints);
	void ReceiveDamage(short int hitPoints);

	void PrintCausaltyLog(std::string logText, short int hitPoints);

	void ReprintCurrentFightLog();

	void PrepareAndClearBeltLog();

	void MoveCursorAfterBeltLog();

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

	short int GetEnnemyLifePoints();
	void SetEnnemyLifePoints(short int ennemyLifePoints);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	unsigned short int GetEnemyHitPoints();

	bool GetIsFightLogCleared();
	void SetIsFightLogCleared(bool fightLogState);

	bool GetIsEnemyDefeated();
	void SetIsEnemyDefeated(bool isEnemyDefeated);

	bool GetIsFightStarted();
	void SetIsFightStarted(bool isFightStarted);

	bool GetIsPlayerTurn();
	void SetIsPlayerTurn(bool isPlayerTurn);

	std::string GetCurrentFightLog();
	void SetCurrentFightLog(std::string currentFightLog);

	void ClearAllConsoleText();

	MenuManager* GetMenuManager();

private:
	WeaponManager* m_weaponManager;
	UserData* m_userData;
	MenuManager* m_menuManager;

	short int m_ennemyLifePoints;
	unsigned short int m_enemyHitPoints;

	std::string m_currentfightLog;

	bool m_isFightLogCleared;
	bool m_isEnemyDefeated;
	bool m_isFightStarted;
	bool m_isPLayerTurn;
};