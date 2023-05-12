#pragma once
#include <string>

class UserData
{
public:
	UserData();

	std::string GetPlayerName();
	void SetPlayerName(std::string playerName);

	bool GetAreWeaponsEquiped();
	void SetAreWeaponsEquiped(bool areWeaponEquiped);

	bool GetIsPlayerSeenDeadEnd();
	void SetIsPlayerSeenDeadEnd(bool isPlayerSeenDeadEnd);

	bool GetIsPlayerSeenVictory();
	void SetIsPlayerSeenVictory(bool isPlayerSeenVictory);

	unsigned short int GetNumberOfPotions();
	void SetNumberOfPotions(unsigned short int numberOfPotions);

	short int GetPlayerLifePoints();
	void SetPlayerLifePoints(short int playerLifePoints);

	bool GetIsPlayerDead();
	void SetIsPlayerDead(bool isPlayerDead);

	std::string GetGameOutputLog();
	void SetGameOutputLog(std::string gameOutputLog);

	void LogOutputstream();

	/// TODO
	//bool GetAttackedKobold();
	//void SetAttackedKobold(bool attackedKobold);

private:
	std::string m_playerName;
	bool m_areWeaponsEquiped;
	bool m_isPlayerSeenDeadEnd;
	bool m_isPlayerSeenVictory;
	bool m_isPlayerDead;
	short int m_playerLifePoints;
	unsigned short int m_numberOfPotions;
	std::string m_gameOutputLog;
	//bool m_attackedKobold; // TODO
};