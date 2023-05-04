#pragma once

const unsigned short int SCENES_IMAGE_LINES[19] = { 
	2, 37, 72, 247, 247, 389, 420, 
	2, 107, 142, 177, 
	282, 317, 353, 389, 
	455, 490, 526, 562 };
const unsigned short int SCENES_TEXT_LINES[8] = { 2, 8, 14, 20, 26, 32, 38, 44 };
//const unsigned short int SCENES_MENU_LINES[7] = { 2, 5, 8, 1, 1, 15, 18 };

namespace ScenesControllers {

	enum class E_SceneSequence {
		NO_SCENE           =  -1,
		INTRO_SCENE        =   0,   // Image line 2   ; Text line 2  ; Menu line 2
		MOVING_SCENE       =   1,   // Image line 37  ; Text line 8  ; Menu line 5
		KOBOLD_SCENE       =   2,   // Image line 72  ; Text line 14 ; Menu line 8
		NAME_SCENE         =   3,   // Image line 247 ; Text line 20 ; View MenuManager.cpp PrintMenuFromScene()
		ATTACK_SCENE       =   4,   // Image line 247 ; Text line 26 ; View MenuManager.cpp PrintMenuFromScene()
		WEAPONS_SCENE      =   5,   // Image line 212 ; Text line 32 ; Menu line 15
		DEAD_END_SCENE     =   6,   // Image line 389 ; Text line 38 ; Menu line 18 // TODO return to navigation menu at lin 26
		ENNEMY_SCENE       =   7,   // Image line 420 ; Text line 44 ; Menu line 21
		
		ROOM_ONE_FRONT     =   8,   // Image line 2   ;              ; Menu line 23
		ROOM_ONE_RIGHT     =   9,   // Image line 107 ;              ; Menu line 54
		ROOM_ONE_LEFT      =  10,   // Image line 142 ;              ; Menu line 54
		ROOM_ONE_BACK      =  11,   // Image line 177 ;              ; Menu line 23
													                 
		ROOM_TWO_FRONT     =  12,   // Image line 282 ;              ; Menu line 23
		ROOM_TWO_RIGHT     =  13,   // Image line 317 ;              ; Menu line 54
		ROOM_TWO_LEFT      =  14,   // Image line 353 ;              ; Menu line 54
		ROOM_TWO_BACK      =  15,   // Image line 389 ;              ; Menu line 23
													                 
		ROOM_THREE_FRONT   =  16,   // Image line 455 ;              ; Menu line 23
		ROOM_THREE_RIGHT   =  17,   // Image line 490 ;              ; Menu line 54
		ROOM_THREE_LEFT    =  18,   // Image line 526 ;              ; Menu line 45
		ROOM_THREE_BACK    =  19    // Image line 562 ;              ; Menu line 23
	};

	//MenuText.txt
	enum class E_MenuChoices {
		ENTER_NAME         =   0,   // NAME_SCENE
		NO_MENU_LINE       =   1,
		TRY_TO_MOVE        =   2,   // INTRO_SCENE
		TRY_TO_REMEBER     =   3,   // INTRO_SCENE

		LOOK_AROUND        =   5,   // MOVING_SCENE
		TRY_TO_REMEBER_TWO =   6,   // MOVING_SCENE

		WHO_ARE_YOU        =   8,   // KOBOLD_SCENE
	    ATTACK_KOBOLD      =   9,   // KOBOLD_SCENE

		GO_BACK            =  15,   // DEAD_END_SCENE

		ATTACK_ENEMY       =  18,   // ENNEMY_SCENE
		RUN_AWAY           =  19,   // ENNEMY_SCENE

		NAVIGATION_PLAIN   =  22,
		NAVIGATION_FOWARD  =  28,
		NAVIGATION_BACK    =  34,
		NAVIGATION_LEFT    =  40,
		NAVIGATION_RIGHT   =  46
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
