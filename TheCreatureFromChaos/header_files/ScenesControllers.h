#pragma once

const unsigned short int SCENES_IMAGE_LINES[2] = { 1, 34 };
const unsigned short int SCENES_TEXT_LINES[2] = { 1, 6 };
const unsigned short int SCENES_MENU_LINES[2] = { 1, 6 };

const unsigned short int FOUR_MENU_CHOICES = 4;
const unsigned short int TWO_MENU_CHOICES = 2;

namespace ScenesControllers {

	enum class E_SceneSequence {
		NO_SCENE = -1,
		INTRO_SCENE = 0, // Image line 1 ; Text line 1
		MOVING_SCENE = 1, // Image line 35 ; Text line 6
		DO_NOTHING_SCENE = 2, // 
	};

	//MenuText.txt
	enum class E_MenuChoices {
		NO_MENU_LINE = 1,
		TRY_TO_MOVE = 3, // INTRO_SCENE
		DO_NOTHING = 4 // INTRO_SCENE
	};

	enum class E_UserInput {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ENTER,
		ESC,
		EMPTY
	};
}
