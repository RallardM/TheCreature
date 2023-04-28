#include "Utils.h"
#include <string>
#include <windows.h>
#include <iostream>



// Go to a specific lines in a file and return the text between those lines.
std::string Utils::GetTextBetweenLines(std::ifstream& file, unsigned int x, unsigned int y)
{
    std::string text;
    std::string line;
    unsigned int currentLine = 1;

    // Read each line in the file until we reach the end or the desired line range.
    while (std::getline(file, line) && currentLine <= y)
    {
        // If the current line is within the desired range, add it to the output string.
        if (currentLine >= x)
        {
            text += line + "\n";
        }
        currentLine++;
    }

    // Return the output string.
    return text;
}

void Utils::SetConsoleColour(int colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void Utils::SetConsolesize()
{
    const unsigned short int CONSOLE_WIDTH = 710;
    const unsigned short int CONSOLE_HEIGHT = 700;
    const unsigned short int CONSOLE_BUFFER_WIDTH = 81;
    const unsigned short int CONSOLE_BUFFER_HEIGHT = 25;

    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, NULL, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    COORD bufferSize = { CONSOLE_BUFFER_WIDTH, CONSOLE_BUFFER_HEIGHT };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void Utils::SetCenterConsolePosition()
{
    HWND consoleWindow = GetConsoleWindow();

    // Get the desktop window dimensions
    RECT desktopRect;
    GetWindowRect(GetDesktopWindow(), &desktopRect);
    int desktop_width = desktopRect.right - desktopRect.left;
    int desktop_height = desktopRect.bottom - desktopRect.top;

    // Get the console window dimensions
    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    int console_width = consoleRect.right - consoleRect.left;
    int console_height = consoleRect.bottom - consoleRect.top;

    // Calculate the position of the console window
    int left_margin = (desktop_width - console_width) / 2;
    int top_margin = (desktop_height - console_height) / 2;

    // Set the position of the console window
    SetWindowPos(consoleWindow, NULL, left_margin, top_margin, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}