#include <random>
#include <string>

#include "CombatManager.h"
#include "DebugMessageSystem.h"
#include "PublicConstants.h"

CombatManager::CombatManager(UserData* userData, MenuManager* menuManager) :
	m_ennemyLifePoints(50),
	m_enemyHitPoints(10),
	m_weaponManager(nullptr),
	m_userData(userData),
	m_menuManager(menuManager),
	m_isEnemyDefeated(false),
	m_isFightStarted(false),
	m_isFightLogCleared(true),
	m_isCurrentFightStartedLog(false),
	m_isPLayerTurn(false),
	m_currentfightLog(""),
	m_isPlayerSuccessFlee(false),
	m_isSecondEncounter(false),
	m_isCountdownStarted(false),
	m_areCountdownVariablesInitiated(false),
	m_isCountdownLogCleared(true),
	m_time_up(true),
	m_remainingSeconds(0)
{
}

void CombatManager::SetCombatAction(E_UserInput userInput)
{
	//SetIsPlayerTurn(true);
	switch (userInput)
	{	
	case PublicConstants::E_UserInput::EMPTY:
		ReprintCurrentFightLog();
		break;

	case PublicConstants::E_UserInput::LEFT: // Attack
		RefreshMenuAndLogFrame();
		PlayerAttack();
		SetIsPlayerTurn(false);
		SetIsFightStarted(true);
		break;

	case PublicConstants::E_UserInput::RIGHT: // Potion
		RefreshMenuAndLogFrame();
		TakePotion();
		SetIsPlayerTurn(false);
		SetIsFightStarted(true);
		break;

	case PublicConstants::E_UserInput::UP:  // Khail help // TODO: 
		RefreshMenuAndLogFrame();
		SetIsPlayerTurn(false);
		SetIsFightStarted(true);
		break;

	case PublicConstants::E_UserInput::DOWN: // Flee
		RefreshMenuAndLogFrame();
		TryToFlee();
		SetIsPlayerTurn(false);
		SetIsFightStarted(true);
		break;

	default:
		// TODO: Add error message
		break;

	}

}

void CombatManager::RefreshMenuAndLogFrame()
{
	GetMenuManager()->ClearConsolePreviousLine();
	SetIsFightLogCleared(true);
	GetWeaponManager()->SetIsWeaponBeltCleared(true);
	GetMenuManager()->ClearConsoleNavigationMenu();
	GetMenuManager()->SelectMenuFromScene(E_UserInput::EMPTY);
	GetWeaponManager()->SelectWeapon(E_UserInput::EMPTY);
}

void CombatManager::PlayerAttack()
{
	S_Weapon currentWeapon = GetWeaponManager()->GetCurrentWeapon(GetWeaponManager()->GetCurrentWeaponIndex());

	// Random hit point between the current weapon min and max hit points or fail
	// Create a random number generator and distribution for hit points

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(currentWeapon.minHitPoints, currentWeapon.maxHitPoints);

	std::string playerHitLog = "";

	// Generate a random hit point value between the current weapon min and max hit points
	unsigned short int hitPoints = dist(gen);

	std::bernoulli_distribution zeroDist(0.2); // Probability of zero/fail
	if (zeroDist(gen)) 
	{
		hitPoints = 0;
	}

	if (hitPoints == 0)
	{
		//std::string spaces = "                           ";
		std::string spaces = "..........................."; // Debug TODO : Remove
		std::string text = "You missed!";
		std::string nextLine = "\n";
		playerHitLog = spaces + text + nextLine;
	}
	else
	{
		//std::string spaces = "             ";
		std::string spaces = "............."; // Debug TODO : Remove
		std::string text = "You hit the monster : ";
		playerHitLog = spaces + text;
	}

	InflictDamage(hitPoints);
	PrintCausaltyLog(playerHitLog, hitPoints);
}

void CombatManager::EnemyCounterAttack()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::string ennemyHitLog = "";

	short int hitPoints = GetEnemyHitPoints();

	std::bernoulli_distribution zeroDist(0.5); // Probability of zero/fail
	if (zeroDist(gen))
	{
		hitPoints = 0;
	}

	if (hitPoints == 0)
	{
		//std::string spaces = "                    ";
		std::string spaces = "...................."; // Debug TODO : Remove
		std::string text = "The monster missed!";
		std::string nextLine = "\n";
		ennemyHitLog = spaces + text + nextLine;
	}
	else
	{
		//std::string spaces = "             ";
		std::string spaces = "............."; // Debug TODO : Remove
		std::string text = "The monster hit you : ";
		ennemyHitLog = spaces + text;
	}
	
	ReceiveDamage(hitPoints);
	if (GetUserData()->GetIsPlayerDead())
	{
		GetMenuManager()->SetIsMenuCleared(false);
		GetUserData()->SetAreWeaponsEquiped(false);
		GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::QUIT_GAME);
		return;
	}

	RefreshMenuAndLogFrame();
	PrintCausaltyLog(ennemyHitLog, hitPoints);
	SetIsPlayerTurn(true);
}

void CombatManager::TakePotion()
{
	std::string playerHealLog = "";

	if (GetUserData()->GetNumberOfPotions() == 0)
	{
		//std::string spaces = "       ";
		std::string spaces = "......."; // Debug TODO : Remove
		std::string text = "You don't have any potions left!";
		std::string nextLine = "\n";
		playerHealLog = spaces + text + nextLine;
	}
	else
	{
		GetUserData()->SetPlayerLifePoints(25);
		GetUserData()->SetNumberOfPotions(GetUserData()->GetNumberOfPotions() - 1);
		//std::string spaces = "                     ";
		std::string spaces = "....................."; // Debug TODO : Remove
		std::string text = "You took a potion!";
		std::string nextLine = "\n";
		playerHealLog = spaces + text + nextLine;
	}

	PrepareAndClearBeltLog();
	std::cout << playerHealLog;
	GetUserData()->SetGameOutputLog(playerHealLog);
	GetMenuManager()->GetScenesManager()->SetIsAllConsoleTextCleared(false);
	SetCurrentFightLog(playerHealLog);
	SetIsFightLogCleared(false);
	SetIsCurrentFightStartedLog(true);
}

void CombatManager::TryToFlee()
{
	
	srand(static_cast<unsigned int>(time(nullptr))); // seed the random number generator with the current time

	// generate a random number between 0 and 3 (inclusive)
	int choice = rand() % 4;

	switch (0) // TODO: put back 'choice' after debug
	{
	case 0:
		// Handle fleeing backwards
		GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::FLEEING_BACKWARD);
		SetIsCurrentFightStartedLog(false);
		SetIsPlayerSuccessFlee(true);
		break;

	case 1:
		// Handle fleeing foward
		GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::FLEEING_FORWARD);
		SetIsEnemyDefeated(true);
		SetIsCurrentFightStartedLog(false);
		SetIsPlayerSuccessFlee(false); // False because the player is not fleeing anymore
		break;

	case 2:
		// Handle dying while fleeing
		GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::FLEING_FAILED_DIED);
		SetIsCurrentFightStartedLog(false);
		SetIsPlayerSuccessFlee(false); // False because the player is not fleeing anymore
		break;

	case 3:
		// Handle failing to flee leading to combat
		GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::ATTACK_ENEMY);
		SetIsSecondEncounter(true);
		SetIsPlayerSuccessFlee(false); // False because the player is not fleeing anymore
		break;

	default:
    	// TODO:
		std::cerr << "Error: invalid choice generated.\n";
		break;
	}
	
}

void CombatManager::InflictDamage(short int hitPoints)
{
	short int resultingCausalty = GetEnnemyLifePoints() - hitPoints;
	if (resultingCausalty <= 0)
	{
		PreparePlayerWonScene();
		return;
	}

	SetEnnemyLifePoints(resultingCausalty);
}

void CombatManager::ReceiveDamage(short int hitPoints)
{
	short int resultingCausalty = GetUserData()->GetPlayerLifePoints() - hitPoints;
	if (resultingCausalty <= 0)
	{
		PreparePlayerDiedScene();
		return;
	}

	GetUserData()->SetPlayerLifePoints(resultingCausalty);
}

void CombatManager::PrintCausaltyLog(std::string logText, short int hitPoints)
{
	bool isPlayerInDialogueMode = (GetMenuManager()->GetNarrationManager()->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::DIALOGUES);
	bool isPlayerInNavigationMode = (GetMenuManager()->GetNarrationManager()->GetUserInputManager()->GetCurrentInputType() == UserInputManager::E_CurrentInputType::NAVIGATION);
	std::string finalOutput = "";

	if (isPlayerInDialogueMode || isPlayerInNavigationMode)
	{
		return;
	}

	PrepareAndClearBeltLog();

	if (hitPoints == 0)
	{
		finalOutput= logText;
		//std::cout << logText;
	}
	else if (hitPoints > 0 && hitPoints < 10)      // To fit the number of max characters 
	{											   // to remove in the log
		//std::cout << logText << " -" << hitPoints; // add a space before the minus sign
		//std::cout << logText << ".-" << hitPoints << std::endl; // Debug TODO : Remove
		//finalOutput = logText + " -" + std::to_string(hitPoints) + "\n";
		finalOutput = logText + ".-" + std::to_string(hitPoints) + "\n"; // Debug TODO : Remove
	}
	else
	{
		//std::cout << logText << "-" << hitPoints << std::endl;
		finalOutput = logText + "-" + std::to_string(hitPoints) + "\n";
	}
	std::cout << finalOutput;
	GetUserData()->SetGameOutputLog(finalOutput);
	GetMenuManager()->GetScenesManager()->SetIsAllConsoleTextCleared(false);
	SetCurrentFightLog(finalOutput);
	SetIsFightLogCleared(false);
	SetIsCurrentFightStartedLog(true);
}

void CombatManager::ReprintCurrentFightLog()
{
	std::string currentFightLog = GetCurrentFightLog();
}

void CombatManager::PrepareAndClearBeltLog()
{
	MoveCursorAfterBeltLog();

	if (!GetIsFightLogCleared())
	{
		for (size_t i = 0; i < 38; i++)
		{
			std::cout << "\b";
		}
		GetMenuManager()->GetScenesManager()->SetIsAllConsoleTextCleared(false);
	}
}

void CombatManager::PreparePlayerWonScene()
{
	SetEnnemyLifePoints(0);
	SetIsEnemyDefeated(true);
	SetIsFightStarted(false);
	SetIsEnemyDefeated(true);
	GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::WON_LEAVE);
}

void CombatManager::PreparePlayerDiedScene()
{
	GetUserData()->SetPlayerLifePoints(0);
	GetUserData()->SetIsPlayerDead(true);
}

void CombatManager::MoveCursorAfterBeltLog()
{
	std::cout << "\033[A";
	std::cout << "\033[43C";
}

void CombatManager::Countdown(int seconds, std::chrono::steady_clock::time_point& start_time, std::chrono::steady_clock::time_point& next_print_time)
{
	if (!GetAreCountdownVariablesInitiated())
	{
		start_time = std::chrono::steady_clock::now();
		next_print_time = start_time + std::chrono::seconds(1);
		m_remainingSeconds = seconds;
		m_time_up = false;
		SetAreCountdownVariablesInitiated(true);
	}

	if (!m_time_up)
	{
		auto current_time = std::chrono::steady_clock::now();
		auto time_diff = std::chrono::duration_cast<std::chrono::seconds>(current_time - next_print_time);

		if (time_diff >= std::chrono::seconds(1))
		{
			next_print_time += std::chrono::seconds(1);
			m_remainingSeconds--;
			PrintRemaningSeconds();
			GetMenuManager()->GetScenesManager()->SetIsAllConsoleTextCleared(false);
		}

		// Check if countdown is over
		if (m_remainingSeconds <= 0)
		{
			m_time_up = true;
		}

		// Sleep for a short period to avoid high CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return;
	}

	FormatCountdown();
	GetMenuManager()->GetScenesManager()->SetNextScene(E_MenuChoices::ATTACK_ENEMY);
	SetIsSecondEncounter(true);
}

void CombatManager::FormatCountdown()
{
	m_remainingSeconds = 0;
	SetIsCountdownStarted(false);
	SetAreCountdownVariablesInitiated(false);
	m_time_up = true;

}

void CombatManager::PrintRemaningSeconds()
{
	MoveCursorAfterBeltLog();
	std::string timeRemaining = "              Time remaining: ";
	std::string seconds = " seconds";
	std::string jumpLine = "\n";
	std::string outputResult = timeRemaining + std::to_string(m_remainingSeconds) + seconds + jumpLine;
	std::cout << outputResult;
	GetUserData()->SetGameOutputLog(outputResult);
}

WeaponManager* CombatManager::GetWeaponManager()
{
	return m_weaponManager;
}

void CombatManager::SetWeaponManager(WeaponManager* weaponManager)
{
	m_weaponManager = weaponManager;
}

short int CombatManager::GetEnnemyLifePoints()
{
	return m_ennemyLifePoints;
}

void CombatManager::SetEnnemyLifePoints(short int ennemyLifePoints)
{
	m_ennemyLifePoints = ennemyLifePoints;
}

UserData* CombatManager::GetUserData()
{
	return m_userData;
}

void CombatManager::SetUserData(UserData* userData)
{
	m_userData = userData;
}

unsigned short int CombatManager::GetEnemyHitPoints()
{
	return m_enemyHitPoints;
}

bool CombatManager::GetIsFightLogCleared()
{
	return m_isFightLogCleared;
}

void CombatManager::SetIsFightLogCleared(bool fightLogState)
{
	m_isFightLogCleared = fightLogState;
}

bool CombatManager::GetIsCurrentFightStartedLog()
{
	return m_isCurrentFightStartedLog;
}

void CombatManager::SetIsCurrentFightStartedLog(bool isCurrentFightStartedLog)
{
	m_isCurrentFightStartedLog = isCurrentFightStartedLog;
}

bool CombatManager::GetIsEnemyDefeated()
{
	return m_isEnemyDefeated;
}

void CombatManager::SetIsEnemyDefeated(bool isEnemyDefeated)
{
	m_isEnemyDefeated = isEnemyDefeated;
}

bool CombatManager::GetIsFightStarted()
{
	return m_isFightStarted;
}

void CombatManager::SetIsFightStarted(bool isFightStarted)
{
	m_isFightStarted = isFightStarted;
}

bool CombatManager::GetIsPlayerTurn()
{
	return m_isPLayerTurn;
}

void CombatManager::SetIsPlayerTurn(bool isPlayerTurn)
{
	m_isPLayerTurn = isPlayerTurn;
}

std::string CombatManager::GetCurrentFightLog()
{
	return m_currentfightLog;
}

void CombatManager::SetCurrentFightLog(std::string currentFightLog)
{
	m_currentfightLog = currentFightLog;
}

void CombatManager::ClearAllConsoleText()
{
	system("cls");
}

MenuManager* CombatManager::GetMenuManager()
{
	return m_menuManager;
}

bool CombatManager::GetIsPlayerSuccessFlee()
{
	return m_isPlayerSuccessFlee;
}

void CombatManager::SetIsPlayerSuccessFlee(bool isPlayerSuccessFlee)
{
	m_isPlayerSuccessFlee = isPlayerSuccessFlee;
}

bool CombatManager::GetIsSecondEncounter()
{
	return m_isSecondEncounter;
}

void CombatManager::SetIsSecondEncounter(bool isSecondEncounter)
{
	m_isSecondEncounter = isSecondEncounter;
}

bool CombatManager::GetIsCountdownStarted()
{
	return m_isCountdownStarted;
}

void CombatManager::SetIsCountdownStarted(bool isCountdownStarted)
{
	m_isCountdownStarted = isCountdownStarted;
}

bool CombatManager::GetAreCountdownVariablesInitiated()
{
	return m_areCountdownVariablesInitiated;
}

void CombatManager::SetAreCountdownVariablesInitiated(bool areCountdownVariablesInitiated)
{
	m_areCountdownVariablesInitiated = areCountdownVariablesInitiated;
}

bool CombatManager::GetIsCountdownLogCleared()
{
	return m_isCountdownLogCleared;
}

void CombatManager::SetIsCountdownLogCleared(bool isCountdownLogCleared)
{
	m_isCountdownLogCleared = isCountdownLogCleared;
}
