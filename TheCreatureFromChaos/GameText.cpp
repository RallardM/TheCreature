#include "GameText.h"
#include <iostream>
#include <Windows.h>
#include <cwchar>

void GameText::Introduction(Utils* utils)
{
	std::ifstream textFile("GameText.txt");
	std::ifstream pictureFile("GameAsciiArt.txt");

	std::string asciiIntroPictureArt = utils->GetTextBetweenLines(pictureFile, 1, 34);
	
	std::string introductionText = utils->GetTextBetweenLines(textFile, 1, 4);

	std::cout << asciiIntroPictureArt;
	std::cout << introductionText << "\n";


}