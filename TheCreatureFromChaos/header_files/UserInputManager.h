#pragma once

enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC };

class UserInputManager {
public:
	
	bool HasInput();
	E_UserInput GetInput();

private:

	
};