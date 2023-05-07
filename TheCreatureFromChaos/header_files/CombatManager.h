#pragma once
#include "ScenesManager.h"

class CombatManager
{
public:
	CombatManager();

	void SetCombatAction(E_UserInput userInput);

private:
	unsigned short int m_ennemyLifePoints;

};