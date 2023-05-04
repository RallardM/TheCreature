#pragma once
//#include <fstream>

class ConsoleHandler {
public:
	void SetConsoleColour(int colour);
	void SetConsolesize();
	void SetCenterConsolePosition();
	void ClearConsole();
	void DisableConsoleCursor();
	void ActivateConsoleCursor();
	void DisableConsoleScrolling();

	//bool GetIsUserPrompted();
	//void SetIsUserPrompted(bool userIsPrompted);

private:
	//bool m_isUserPrompted;
};
