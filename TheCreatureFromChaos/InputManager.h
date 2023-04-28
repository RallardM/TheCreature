#pragma once

enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC };

class InputManager {
public:
	

	bool HasInput();
	E_UserInput GetInput();

private:
	bool m_hasInput;
	
};