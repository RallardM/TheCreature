#pragma once
#include <fstream>

class Utils {
public:
	std::string GetTextBetweenLines(std::ifstream& file, unsigned int x, unsigned int y);
	void SetConsoleColour(int colour);
	void SetConsolesize();
	void SetCenterConsolePosition();
	static std::string CenterText(const std::string& text);
};
