#pragma once
//#include <fstream>

class ConsoleHandler {
public:
	ConsoleHandler();
	void SetConsoleColour(int colour);
	void SetConsolesize();
	void SetCenterConsolePosition();
	void ClearConsole();
	void DisableConsoleCursor();
	void ActivateConsoleCursor();
	void DisableConsoleScrolling();

	//bool GetIsUserPrompted();
	//void SetIsUserPrompted(bool userIsPrompted);

	bool GetIsGameRunning();
	void SetIsGameRunning(bool isGameRunning);

private:
	//bool m_isUserPrompted;
	bool m_isGameRunning;
};
