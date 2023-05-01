#pragma once
#include "main.h"
//#include "ScenesMenuManager.h"
//#include "ScenesMenuManager.h"

//class ScenesMenuManager;

class UserInputManager {
public:
	//UserInputManager(MainClass* mainClassAccess);
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(UserInputManager::E_UserInput userInput);

private:
	static bool prevInputDetected;
	bool m_hasInput;
	//MainClass* m_mainClassAccess;
};