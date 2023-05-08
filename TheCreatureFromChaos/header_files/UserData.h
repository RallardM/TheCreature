#pragma once
#include <string>
#include "Weapons.h"

class UserData
{
public:
	UserData(Weapons* weapon);

	std::string GetPlayerName();
	void SetPlayerName(std::string playerName);

	bool GetAreWeaponsEquiped();
	void SetAreWeaponsEquiped(bool areWeaponEquiped);

	bool GetIsPlayerSeenDeadEnd();
	void SetIsPlayerSeenDeadEnd(bool isPlayerSeenDeadEnd);

	unsigned short int GetNumberOfPotions();
	void SetNumberOfPotions(unsigned short int numberOfPotions);

	Weapons* GetWeapons();
	void SetWeapons(Weapons* weapon);

	/// TODO
	//bool GetAttackedKobold();
	//void SetAttackedKobold(bool attackedKobold);

private:
	std::string m_playerName;
	bool m_areWeaponsEquiped;
	bool m_isPlayerSeenDeadEnd;
	short int m_playerLifePoints;
	unsigned short int m_numberOfPotions;

	Weapons* m_weapons;
	//bool m_attackedKobold; // TODO
};