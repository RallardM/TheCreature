#pragma once

#include "Narration.h"
class Narration;
#include "Menu.h"

class OutputManager
{
public:
	OutputManager();
	~OutputManager();

	Narration* GetNarration();
	void SetNarration(Narration* narration);

	Menu* GetMenu();
	void SetMenu(Menu* menu);

private:
	Narration* m_narration;
	Menu* m_menu;
};