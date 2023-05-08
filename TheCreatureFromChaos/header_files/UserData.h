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

	unsigned short int GetNumberOfPotions();
	void SetNumberOfPotions(unsigned short int numberOfPotions);

	short int GetPlayerLifePoints();
	void SetPlayerLifePoints(short int playerLifePoints);

	/// TODO
	//bool GetAttackedKobold();
	//void SetAttackedKobold(bool attackedKobold);

private:
	std::string m_playerName;
	bool m_areWeaponsEquiped;
	bool m_isPlayerSeenDeadEnd;
	short int m_playerLifePoints;
	unsigned short int m_numberOfPotions;
	//bool m_attackedKobold; // TODO
};