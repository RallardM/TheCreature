#pragma once
#include <iostream>

#ifndef _DEBUG
#define DEBUG_MSG(x)
#else
void DEBUG_MSG(const char* message);
#endif

int getColorCode(char color) 
{
    switch (toupper(color)) 
    {
    case 'R':
        return 31; // red
    case 'G':
        return 32; // green
    case 'B':
        return 34; // blue
    case 'Y':
        return 33; // yellow
    case 'P':
        return 35; // purple
    case 'C':
        return 36; // cyan
    case 'O':
        return 38; // orange
    default:
        return 37; // white
    }
}

#ifdef _DEBUG
void DEBUG_MSG(const char* message) 
{
    bool isDebugMessageActivated = false;
    if (isDebugMessageActivated == false)
    {
		return;
	}

    char color = '\0';
    const char* text = message;
    if (message[0] == '#' && isalpha(message[1])) 
    {
        color = message[1];
        text = message + 2;
    }
    std::cerr << "\033[1;" << getColorCode(color) << "m" << text << "\033[0m" << std::endl;
}
#endif
