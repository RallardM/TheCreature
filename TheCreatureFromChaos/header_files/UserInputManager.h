#ifndef USERINPUTMANAGER_HPP
#define USERINPUTMANAGER_HPP

//#include "main.h"

#include "MenuManager.h"

//class MenuManager;

class UserInputManager {
public:
	UserInputManager(MenuManager* menuManager);
	//UserInputManager(MainClass* mainClassAccess);
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(UserInputManager::E_UserInput userInput);

private:
	//static bool prevInputDetected;
	bool m_hasInput;
	MenuManager* m_menuManager;
	//MainClass* m_mainClassAccess;
};

#endif // USERINPUTMANAGER_HPP