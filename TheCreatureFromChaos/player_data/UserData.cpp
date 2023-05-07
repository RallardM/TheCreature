#include "UserData.h"

UserData::UserData() :
	m_playerName(""),
	m_playerLifePoints(25),
	m_areWeaponsEquiped(false),
	m_isPlayerSeenDeadEnd(false),
	m_isBossDefeated(false)
{
}

std::string UserData::GetPlayerName()
{
	return m_playerName;
}

void UserData::SetPlayerName(std::string playerName)
{
	m_playerName = playerName;
}

bool UserData::GetAreWeaponsEquiped()
{
	return m_areWeaponsEquiped;
}

void UserData::SetAreWeaponsEquiped(bool areWeaponEquiped)
{
	m_areWeaponsEquiped = areWeaponEquiped;
}

bool UserData::GetIsPlayerSeenDeadEnd()
{
	return m_isPlayerSeenDeadEnd;
}

void UserData::SetIsPlayerSeenDeadEnd(bool isPlayerSeenDeadEnd)
{
	m_isPlayerSeenDeadEnd = isPlayerSeenDeadEnd;
}

bool UserData::GetIsBossDefeated()
{
	return m_isBossDefeated;
}

void UserData::SetIsBossDefeated(bool isBossDefeated)
{
	m_isBossDefeated = isBossDefeated;
}

// TODO
//bool UserData::GetAttackedKobold()
//{
//	return m_attackedKobold;
//}
//
//void UserData::SetAttackedKobold(bool attackedKobold)
//{
//	m_attackedKobold = attackedKobold;
//}
