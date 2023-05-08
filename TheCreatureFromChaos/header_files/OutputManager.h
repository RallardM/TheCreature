#pragma once

#include "Narration.h"
#include "Menu.h"

class OutputManager
{
public:
	OutputManager(Narration* narration, Menu* menu);
	~OutputManager();

	Narration* GetNarration();
	Menu* GetMenu();

private:
	Narration* m_narration;
	Menu* m_menu;
};