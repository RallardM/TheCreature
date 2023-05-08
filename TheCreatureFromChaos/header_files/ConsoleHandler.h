#pragma once
#include "UserInput.h"
//#include <fstream>

class ConsoleHandler {
public:
	ConsoleHandler(UserInput* inputManager);
	void SetConsoleColour(int colour);
	void SetConsolesize();
	void SetCenterConsolePosition();
	void ClearConsole();
	void DisableConsoleCursor();
	void ActivateConsoleCursor();
	void DisableConsoleScrolling();

	//bool GetIsUserPrompted();
	//void SetIsUserPrompted(bool userIsPrompted);

	UserInput* GetUserInput();

private:
	UserInput* m_userInputManager;
	//bool m_isUserPrompted;
};
