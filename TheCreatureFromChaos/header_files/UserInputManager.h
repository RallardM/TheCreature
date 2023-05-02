#ifndef USERINPUTMANAGER_H
#define USERINPUTMANAGER_H

class MenuManager;

class UserInputManager {
public:
	UserInputManager(MenuManager* menuManager);
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };
	bool HasInput();
	void SetHasInput(bool hasInput);
	E_UserInput GetInput();
	void SetAction(UserInputManager::E_UserInput userInput);
	MenuManager* GetMenuManager();

private:
	bool m_hasInput;
	MenuManager* m_menuManager;
};

#endif // USERINPUTMANAGER_H