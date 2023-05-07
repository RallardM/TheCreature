#pragma once

namespace ScenesConstants {
	const unsigned short int SCENES_IMAGE_LINES[21] = {
	2,    // INTRO_SCENE 
	37,   // MOVING_SCENE
	72,   // KOBOLD_SCENE      ROOM_ONE_BACK
	72,   // NAME_SCENE
	282,  // ATTACK_KOBOLD_SCENE
	107,  // WEAPONS_SCENE
	142,  // DEAD_END_SCENE    ROOM_TWO_BACK
	177,  // ENNEMY_SCENE  

	212,  // ROOM_ONE_LEFT
	  2,  // ROOM_ONE_FRONT
	247,  // ROOM_ONE_RIGHT 
	282,  // ROOM_ONE_BACK     KOBOLD_SCENE

	317,  // ROOM_TWO_FRONT
	353,  // ROOM_TWO_RIGHT
	388,  // ROOM_TWO_LEFT
	142,  // ROOM_TWO_BACK     DEAD_END_SCENE

	424,  // ROOM_THREE_FRONT 
	460,  // ROOM_THREE_RIGHT
	495,  // ROOM_THREE_LEFT
	531,  // ROOM_THREE_BACK

	177   // ENNEMY_SCENE
	};

	enum class E_SceneSequence : const short int {
		NO_SCENE = -1,
		INTRO_SCENE,          // Image line 2   ; Text line 2  ; Menu line 2
		MOVING_SCENE,         // Image line 37  ; Text line 8  ; Menu line 5
		KOBOLD_SCENE,         // Image line 72  ; Text line 14 ; Menu line 8
		NAME_SCENE,           // Image line 72  ; Text line 20 ; View MenuManager.cpp PrintMenuFromScene()
		ATTACK_KOBOLD_SCENE,  // Image line 282 ; Text line 26 ; View MenuManager.cpp PrintMenuFromScene()
		WEAPONS_SCENE,        // Image line 107 ; Text line 32 ; Menu line 15
		DEAD_END_SCENE,       // Image line 142 ; Text line 38 ; Menu line 18 // TODO return to navigation menu at line 26
		ENNEMY_SCENE,         // Image line 177 ; Text line 44 ; Menu line 21
						      
		ROOM_ONE_LEFT,        // Image line 212 ;              ; Menu line 23
		ROOM_ONE_FRONT,       // Image line   2 ;              ; Menu line 54
		ROOM_ONE_RIGHT,       // Image line 247 ;              ; Menu line 54
		ROOM_ONE_BACK,        // Image line 282 ;              ; Menu line 23
						      
		ROOM_TWO_LEFT,        // Image line 317 ;              ; Menu line 23
		ROOM_TWO_FRONT,       // Image line 353 ;              ; Menu line 54
		ROOM_TWO_RIGHT,       // Image line 388 ;              ; Menu line 54
		ROOM_TWO_BACK,        // Image line 142 ;              ; Menu line 23
						      
		ROOM_THREE_LEFT,      // Image line 424 ;              ; Menu line 23
		ROOM_THREE_FRONT,     // Image line 460 ;              ; Menu line 54
		ROOM_THREE_RIGHT,     // Image line 495 ;              ; Menu line 45
		ROOM_THREE_BACK,      // Image line 531 ;              ; Menu line 23

		COMBAT_SCENE,         // Image line 177 ;              ; Menu line 90
	};
}