#pragma once

const unsigned short int SCENES_IMAGE_LINES[7] = { 2, 37, 72, 72, 107, 143, 174 };
const unsigned short int SCENES_TEXT_LINES[7] = { 2, 8, 14, 20, 25, 31, 37 };
//const unsigned short int SCENES_MENU_LINES[7] = { 2, 5, 8, 1, 1, 15, 18 };

namespace ScenesControllers {

	enum class E_SceneSequence {
		NO_SCENE = -1,
		INTRO_SCENE = 0,      // Image line 2   ; Text line 2  ; Menu line 2
		MOVING_SCENE = 1,     // Image line 37  ; Text line 8  ; Menu line 5
		KOBOLD_SCENE = 2,     // Image line 72  ; Text line 14 ; Menu line 8
		NAME_SCENE = 3,       // Image line 107 ; Text line 20 ;
		ATTACK_SCENE = 4,     // Image line 107 ; Text line 25 ;
		DEAD_END_SCENE = 5,   // Image line 143 ; Text line 31 ; Menu line 15
		ENNEMY_SCENE = 6      // Image line 174 ; Text line 37 ; Menu line 18
	};

	//MenuText.txt
	enum class E_MenuChoices {
		NO_MENU_LINE = 1,
		TRY_TO_MOVE = 2,        // INTRO_SCENE
		TRY_TO_REMEBER = 3,     // INTRO_SCENE
		LOOK_AROUND = 5,        // MOVING_SCENE
		TRY_TO_REMEBER_TWO = 6, // MOVING_SCENE
		WHO_ARE_YOU = 8,        // KOBOLD_SCENE
	    ATTACK_KOBOLD = 9,      // KOBOLD_SCENE
		GO_BACK = 15,           // DEAD_END_SCENE
		ATTACK_ENEMY = 18,      // ENNEMY_SCENE
		RUNAWAY = 19            // ENNEMY_SCENE
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
