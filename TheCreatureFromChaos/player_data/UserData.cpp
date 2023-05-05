#include "UserData.h"

UserData::UserData() :
	m_playerName("")
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
