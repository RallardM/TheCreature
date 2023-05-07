#include "CombatManager.h"
#include "DebugMessageSystem.h"
#include "PublicConstants.h"


CombatManager::CombatManager() :
	m_ennemyLifePoints(50)
{
}

void CombatManager::SetCombatAction(E_UserInput userInput)
{
	switch (userInput)
	{		
	case PublicConstants::E_UserInput::LEFT: // Khail help
		break;

	case PublicConstants::E_UserInput::RIGHT: // Potion
		break;

	case PublicConstants::E_UserInput::UP: // Attack
		break;

	case PublicConstants::E_UserInput::DOWN: // Flee
		break;

	default:
		// TODO: Add error message
		break;

	}
}