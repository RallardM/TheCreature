#pragma once

class ScenesManager;

#include "ScenesManager.h"
#include "ScenesControllers.h"
using namespace ScenesControllers;

class UserInputManager {
public:
	UserInputManager(ScenesManager* sceneManager, MenuManager* menuManager);
	
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(E_UserInput userInput);
	MenuManager* GetMenuManager();
	ScenesManager* GetScenesManager();

private:
	bool m_hasInput;
	MenuManager* m_menuManager;
	ScenesManager* m_sceneManager;
};
