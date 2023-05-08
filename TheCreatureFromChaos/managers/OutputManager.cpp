#include "OutputManager.h"

OutputManager::OutputManager() :
	m_narration(nullptr),
	m_menu(nullptr)
{
}

OutputManager::~OutputManager()
{
}

Narration* OutputManager::GetNarration()
{
	return m_narration;
}

void OutputManager::SetNarration(Narration* narration)
{
	m_narration = narration;
}

Menu* OutputManager::GetMenu()
{
	return m_menu;
}

void OutputManager::SetMenu(Menu* menu)
{
	m_menu = menu;
}
