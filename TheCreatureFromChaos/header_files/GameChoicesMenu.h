#pragma once
#include "UserInputManager.h"



class GameChoicesMenu {
public:
	void Render(E_UserInput userInput);

private:
	unsigned short int m_gameMenuLines[2] = { 1, 4 };

};