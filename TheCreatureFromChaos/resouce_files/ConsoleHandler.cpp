#include "ConsoleHandler.h"
#include <windows.h>

ConsoleHandler::ConsoleHandler(UserInput* inputManager) :
    m_userInputManager(inputManager)
{
}

void ConsoleHandler::SetConsoleColour(int colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void ConsoleHandler::SetConsolesize()
{
    const unsigned short int CONSOLE_WIDTH = 697;
    const unsigned short int CONSOLE_HEIGHT = 712;
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

void ConsoleHandler::SetCenterConsolePosition()
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

void ConsoleHandler::ClearConsole()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    COORD topLeft = { 0, 0 };

    // Get the size of the console buffer
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);
    DWORD consoleSize = screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;

    // Fill the console buffer with spaces
    DWORD charsWritten;
    FillConsoleOutputCharacter(console, ' ', consoleSize, topLeft, &charsWritten);

    // Move the cursor to the top left corner of the console
    SetConsoleCursorPosition(console, topLeft);
}

void ConsoleHandler::DisableConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ConsoleHandler::ActivateConsoleCursor()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = TRUE; // Set cursor visibility to true
    cursor_info.dwSize = 100; // Set cursor size to 100
    SetConsoleCursorInfo(console, &cursor_info);
}

void ConsoleHandler::DisableConsoleScrolling()
{
    // Get the current console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // Set the screen buffer size to the window size
    COORD size = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);

    // Disable vertical scrolling of the console window
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

UserInput* ConsoleHandler::GetUserInput()
{
    return m_userInputManager;
}

//bool ConsoleHandler::GetIsUserPrompted()
//{
//	return m_isUserPrompted;
//}
//
//void ConsoleHandler::SetIsUserPrompted(bool isUserPrompted)
//{
//    m_isUserPrompted = isUserPrompted;
//}
