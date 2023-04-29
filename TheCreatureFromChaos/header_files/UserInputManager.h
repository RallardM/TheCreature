#pragma once



class UserInputManager {
public:
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };

	bool HasInput();
	E_UserInput GetInput();
	
};