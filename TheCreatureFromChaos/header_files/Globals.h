#pragma once

const unsigned short int G_FOUR_MENU_CHOICES = 4;
const unsigned short int G_TWO_MENU_CHOICES = 2;

enum class E_SceneSequence {
	//  NarrationManager.cpp m_sceneMenuLines{ 1, 6 }
	NO_SCENE = -1,
	INTRO_SCENE = 0, // line 1 
	MOVING_SCENE = 2, // line 6
};

enum class E_MenuChoices {
	NO_MENU_LINE = 1,
	TRY_TO_MOVE = 3,
	DO_NOTHING = 4
};



enum class E_UserInput { 
	LEFT, 
	RIGHT, 
	UP, 
	DOWN, 
	ENTER, 
	ESC, 
	EMPTY };