#include "OutputManager.h"

OutputManager::OutputManager(Narration* narration, Menu* menu) :
	m_narration(narration),
	m_menu(menu)
{
}

OutputManager::~OutputManager()
{
}

Narration* OutputManager::GetNarration()
{
	return m_narration;
}

Menu* OutputManager::GetMenu()
{
	return m_menu;
}
