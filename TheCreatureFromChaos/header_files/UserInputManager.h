#pragma once

//#include "ScenesManager.h"
//#include "MenuManager.h"

class ScenesManager;
class NarrationManager;
class MenuManager;

class UserInputManager {
public:
	UserInputManager(ScenesManager* sceneManager, MenuManager* menuManager);
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(UserInputManager::E_UserInput userInput);
	MenuManager* GetMenuManager();
	ScenesManager* GetScenesManager();

private:
	bool m_hasInput;
	MenuManager* m_menuManager;
	ScenesManager* m_sceneManager;
};
