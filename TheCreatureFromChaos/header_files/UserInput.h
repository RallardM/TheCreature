#pragma once

//class Scenes;

//#include "ScenesManager.h"
//#include "ConsoleHandler.h"
#include "PublicConstants.h"
#include "UserData.h"
class UserData;
#include "OutputManager.h"
class OutputManager;
#include "GameplayManager.h"
class GameplayManager;
//#include "WeaponManager.h"

//class Combat;
using namespace PublicConstants;

class UserInput {
public:

	enum class E_CurrentInputType : const unsigned short int {
		DIALOGUES,
		NAVIGATION,
		COMBAT
	};

	UserInput();
	
	void ActivateSelection(E_UserInput userInput);
	void EnterSelection();

	E_CurrentInputType GetCurrentInputType();
	void SetCurrentInputType(E_CurrentInputType currentInputType);

	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(E_UserInput userInput);

	//ConsoleHandler* GetConsoleHandler();
	//Menu* GetMenuManager();
	//Scenes* GetScenesManager();

	//Weapons* GetWeaponManager();
	//void SetWeaponManager(Weapons* weaponManager);

	//Combat* GetCombatManager();

	UserData* GetUserData();
	void SetUserData(UserData* userData);

	OutputManager* GetOutputManager();
	void SetOutputManager(OutputManager* outputManager);

	GameplayManager* GetGameplayManager();
	void SetGameplayManager(GameplayManager* gameplayManager);

private:
	bool m_hasInput;
	E_CurrentInputType m_currentInputType;

	UserData* m_userData;
	OutputManager* m_outputManager;
	GameplayManager* m_gameplayManager;
};
