#pragma once
#include <string>

class UserData
{
public:
	UserData();

	std::string GetPlayerName();
	void SetPlayerName(std::string playerName);

private:
	std::string m_playerName;
};