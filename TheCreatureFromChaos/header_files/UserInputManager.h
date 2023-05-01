#pragma once

class UserInputManager {
public:
	enum class E_UserInput { LEFT, RIGHT, UP, DOWN, ENTER, ESC, EMPTY };

	bool HasInput();

	void SetHasInput(bool hasInput);

	E_UserInput GetInput();

private:
	static bool prevInputDetected;
	bool m_hasInput;
};