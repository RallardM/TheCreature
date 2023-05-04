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