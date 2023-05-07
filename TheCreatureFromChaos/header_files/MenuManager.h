#pragma once

#include <fstream>
#include "ScenesManager.h"
class ScenesManager;

#include "PublicConstants.h"
#include "UserData.h"
#include "ConsoleHandler.h"

using namespace PublicConstants;

class MenuManager {
public:
	enum class E_MenuTypes : const unsigned short int
	{
		ONE_CHOICE_MENU,
		TWO_CHOICES_MENU,
		TWO_WAYS_RIGHT,
		TWO_WAYS_LEFT,
		FOUR_WAYS_FRONT,
		FOUR_WAYS_BACK,
		COMBAT_MENU
	};

	E_MenuTypes SCENE_NUMBER_OF_MENU_CHOICES[20] = {
	E_MenuTypes::TWO_CHOICES_MENU,     // INTRO_SCENE
	E_MenuTypes::TWO_CHOICES_MENU,     // MOVING_SCENE
	E_MenuTypes::TWO_CHOICES_MENU,     // KOBOLD_SCENE
	E_MenuTypes::ONE_CHOICE_MENU,      // NAME_SCENE
	E_MenuTypes::ONE_CHOICE_MENU,      // ATTACK_SCENE
	E_MenuTypes::ONE_CHOICE_MENU,      // WEAPONS_SCENE
	E_MenuTypes::ONE_CHOICE_MENU,      // DEAD_END_SCENE
	E_MenuTypes::TWO_CHOICES_MENU,     // ENNEMY_SCENE

	E_MenuTypes::TWO_WAYS_LEFT,        // ROOM_ONE_LEFT
	E_MenuTypes::FOUR_WAYS_FRONT,      // ROOM_ONE_FRONT
	E_MenuTypes::TWO_WAYS_RIGHT,       // ROOM_ONE_RIGHT
	E_MenuTypes::FOUR_WAYS_BACK,       // ROOM_ONE_BACK

	E_MenuTypes::TWO_WAYS_LEFT,        // ROOM_TWO_LEFT
	E_MenuTypes::FOUR_WAYS_FRONT,      // ROOM_TWO_FRONT
	E_MenuTypes::TWO_WAYS_RIGHT,       // ROOM_TWO_RIGHT
	E_MenuTypes::FOUR_WAYS_BACK,       // ROOM_TWO_BACK

	E_MenuTypes::TWO_WAYS_LEFT,        // ROOM_THREE_LEFT
	E_MenuTypes::FOUR_WAYS_FRONT,      // ROOM_THREE_FRONT
	E_MenuTypes::TWO_WAYS_RIGHT,       // ROOM_THREE_RIGHT
	E_MenuTypes::FOUR_WAYS_BACK,       // ROOM_THREE_BACK
	};

	//MenuText.txt                  
	enum class E_MenuChoices : const unsigned short int {
		ENTER_NAME = 0,    // NAME_SCENE

		NO_MENU_LINE = 1,

		TRY_TO_MOVE = 2,    // INTRO_SCENE
		TRY_TO_REMEBER = 3,    // INTRO_SCENE

		LOOK_AROUND = 5,    // MOVING_SCENE
		TRY_TO_REMEBER_TWO = 6,    // MOVING_SCENE

		WHO_ARE_YOU = 8,    // KOBOLD_SCENE
		ATTACK_KOBOLD = 9,    // KOBOLD_SCENE

		TAKE_WEAPONS = 15,    // WEAPONS_SCENE
		TAKE_WEAPONS_SELECTED = 16,    // WEAPONS_SCENE

		GO_BACK = 18,    // DEAD_END_SCENE
		GO_BACK_SELECTED = 19,    // DEAD_END_SCENE

		ATTACK_ENEMY = 21,    // ENNEMY_SCENE
		RUN_AWAY = 22,    // ENNEMY_SCENE

		NAVIGATION_PLAIN = 26,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_LEFT = 34,     // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_RIGHT = 42,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_FOWARD = 50,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_BACK = 58,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK

		LR_NAVIGATION_PLAIN = 66,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT
		LR_NAVIGATION_LEFT = 74,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT
		LR_NAVIGATION_RIGHT = 82,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT

		COMBAT_PLAIN = 90,
		COMBAT_HELP = 98,
		COMBAT_POTION = 106,
		COMBAT_ATTACK = 114,
		COMBAT_FLEE = 122
	};

	const short int EMPTY_MENU_LINE = -1;
	const std::string EMPTY_MENU_TEXT = "";
	MenuManager(ConsoleHandler* consoleHandler, ScenesManager* sceneManager, NarrationManager* narrationManager, UserData* userData);
	

	void SelectMenuFromScene(E_UserInput userInput);
	void SelectMenuChoice(E_UserInput userInput, E_MenuChoices LeftMenuChoice, E_MenuChoices rightMenuChoice);

	void SelectNavigationElement(E_UserInput userInput, E_MenuChoices menuChoice);
	void PrepareNavigationMenu(E_MenuChoices menuChoice, unsigned short int numberOfUiElementsToJumpOver);

	void SelectCombatChoice(E_UserInput userInput, E_MenuChoices menuChoice);

	void PrintSingleMenuChoice(E_UserInput userInput, E_MenuChoices menuChoice);
	void PrintSelectedMenu(E_MenuChoices currentMenuChoice);
	void PrintNavigationMenu(E_MenuChoices currentMenuChoice);
	void PrintEnterNameMenu();


	std::string GetLastLineInConsole();

	E_MenuChoices GetSelectedMenuLine();
	void SetSelectedMenuLine(E_MenuChoices selectedMenuLine);
	std::string GetMenuAtLine(std::string& filePath, E_MenuChoices atLine);

	void ClearConsolePreviousLine();
	void ClearConsoleNavigationMenu();

	bool GetIsMenuCleared();
	void SetIsMenuCleared(bool isMenuCleared);

	ConsoleHandler* GetConsoleHandler();
	NarrationManager* GetNarrationManager();
	ScenesManager* GetScenesManager();
	UserData* GetUserData();

	void AddDelay();

	WeaponManager* GetWeaponManager();
	void SetWeaponManager(WeaponManager* weaponManager);

private:

	E_MenuChoices m_selectedMenuLine;

	std::ifstream m_menuFilePath;
	bool m_isMenuCleared;

	ConsoleHandler* m_consoleHandler;
	ScenesManager* m_scenesManager;
	NarrationManager* m_narrationManager;
	UserData* m_userData;
	WeaponManager* m_weaponManager;
};


	