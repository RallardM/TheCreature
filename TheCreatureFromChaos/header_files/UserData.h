#pragma once
#include <string>

class UserData
{
public:
	UserData();

	std::string GetPlayerName();
	void SetPlayerName(std::string playerName);

	bool GetIsPlayerSeenDeadEnd();
	void SetIsPlayerSeenDeadEnd(bool isPlayerSeenDeadEnd);

	bool GetIsBossDefeated();
	void SetIsBossDefeated(bool isBossDefeated);

	/// TODO
	//bool GetAttackedKobold();
	//void SetAttackedKobold(bool attackedKobold);

private:
	std::string m_playerName;
	bool m_isPlayerSeenDeadEnd;
	bool m_isBossDefeated;
	//bool m_attackedKobold; // TODO
};