#pragma once
#include <iostream>

#ifndef _DEBUG
#define DEBUG_MSG(x)
#else
void DEBUG_MSG(const char* message);
#endif