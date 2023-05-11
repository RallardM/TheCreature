#pragma once
#include <chrono>

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

	void TryToFlee();

	void InflictDamage(short int hitPoints);
	void ReceiveDamage(short int hitPoints);

	void PrintCausaltyLog(std::string logText, short int hitPoints);

	void PreparePlayerWonScene();
	void PreparePlayerDiedScene();

	void ReprintCurrentFightLog();

	void PrepareAndClearBeltLog();

	void MoveCursorAfterBeltLog();

	void Countdown(int seconds, std::chrono::steady_clock::time_point& start_time, std::chrono::steady_clock::time_point& next_print_time);

	void FormatCountdown();

	void PrintRemaningSeconds();

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

	short int GetEnnemyLifePoints();
	void SetEnnemyLifePoints(short int ennemyLifePoints);

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	unsigned short int GetEnemyHitPoints();

	bool GetIsFightLogCleared();
	void SetIsFightLogCleared(bool fightLogState);

	bool GetIsCurrentFightStartedLog();
	void SetIsCurrentFightStartedLog(bool isCurrentFightStartedLog);

	bool GetIsEnemyDefeated();
	void SetIsEnemyDefeated(bool isEnemyDefeated);

	bool GetIsFightStarted();
	void SetIsFightStarted(bool isFightStarted);

	bool GetIsPlayerTurn();
	void SetIsPlayerTurn(bool isPlayerTurn);

	std::string GetCurrentFightLog();
	void SetCurrentFightLog(std::string currentFightLog);

	bool GetIsPlayerFleeing();
	void SetIsPlayerFleeing(bool isPlayerFleeing);

	bool GetIsSecondEncounter();
	void SetIsSecondEncounter(bool isSecondEncounter);

	bool GetIsCountdownStarted();
	void SetIsCountdownStarted(bool isCountdownStarted);

	bool GetAreCountdownVariablesInitiated();
	void SetAreCountdownVariablesInitiated(bool areCountdownVariablesInitiated);

	bool GetIsCountdownLogCleared();
	void SetIsCountdownLogCleared(bool isCountdownLogCleared);

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
	bool m_isCurrentFightStartedLog;

	bool m_isEnemyDefeated;
	bool m_isFightStarted;
	bool m_isPLayerTurn;
	bool m_isPlayerFleeing;
	bool m_isSecondEncounter;

	bool m_isCountdownStarted;
	bool m_areCountdownVariablesInitiated;
	bool m_time_up;
	bool m_isCountdownLogCleared;
	int short m_remainingSeconds;
	

};