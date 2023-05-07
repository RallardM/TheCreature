#pragma once
#include <string>

const unsigned short int SCENES_TEXT_LINES[8] = { 2, 8, 14, 20, 26, 32, 38, 44 };

const unsigned short int NEXT_MENU_ELEMENT        =  1;
const unsigned short int CURRENT_MENU_ELEMENT     =  1;
const unsigned short int NEXT_TWO_MENU_ELEMENTS   =  2;
const unsigned short int NEXT_THREE_MENU_ELEMENTS =  3;
const unsigned short int NEXT_FOUR_MENU_ELEMENTS  =  4;
const unsigned short int NB_LINES_NEXT_NAVIG_UI   =  8;
												    
const unsigned short int NAVIGATION_MENU_HEIGHT   =  7;
												    
const unsigned short int ONE_CHOICE_MENU          =  1;
const unsigned short int TWO_CHOICES_MENU         =  2;
												    
const unsigned short int TWO_WAYS_RIGHT           =  3;
const unsigned short int TWO_WAYS_LEFT            =  4;
const unsigned short int FOUR_WAYS_FRONT          =  5;
const unsigned short int FOUR_WAYS_BACK           =  6;
const unsigned short int COMBAT_MENU              =  7;

const unsigned short int LEFT_TO_FRONT            =  1;
const unsigned short int LEFT_TO_BACK             =  3;
const short int          FRONT_TO_LEFT            = -1;
const unsigned short int FRONT_TO_RIGHT           =  1;
const unsigned short int FRONT_TO_BACK            =  2;
const short int          RIGHT_TO_FRONT           = -1;
const unsigned short int RIGHT_TO_BACK            =  1;
const short int          BACK_TO_LEFT             = -3;
const short int          BACK_TO_FRONT            = -2;
const short int          BACK_TO_RIGHT            = -1;

const unsigned short int SCENE_NUMBER_OF_MENU_CHOICES[21] = {
	TWO_CHOICES_MENU,     // INTRO_SCENE
	TWO_CHOICES_MENU,     // MOVING_SCENE
	TWO_CHOICES_MENU,     // KOBOLD_SCENE
	ONE_CHOICE_MENU,      // NAME_SCENE
	ONE_CHOICE_MENU,      // ATTACK_SCENE
	ONE_CHOICE_MENU,      // WEAPONS_SCENE
	ONE_CHOICE_MENU,      // DEAD_END_SCENE
	TWO_CHOICES_MENU,     // ENNEMY_SCENE

	TWO_WAYS_LEFT,        // ROOM_ONE_LEFT
	FOUR_WAYS_FRONT,      // ROOM_ONE_FRONT
	TWO_WAYS_RIGHT,       // ROOM_ONE_RIGHT
	FOUR_WAYS_BACK,       // ROOM_ONE_BACK

	TWO_WAYS_LEFT,        // ROOM_TWO_LEFT
	FOUR_WAYS_FRONT,      // ROOM_TWO_FRONT
	TWO_WAYS_RIGHT,       // ROOM_TWO_RIGHT
	FOUR_WAYS_BACK,       // ROOM_TWO_BACK

	TWO_WAYS_LEFT,        // ROOM_THREE_LEFT
	FOUR_WAYS_FRONT,      // ROOM_THREE_FRONT
	TWO_WAYS_RIGHT,       // ROOM_THREE_RIGHT
	FOUR_WAYS_BACK,       // ROOM_THREE_BACK
	COMBAT_MENU		      // COMBAT_SCENE
};

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

	177	  // COMBAT_SCENE
};

namespace PublicConstants {
	enum class E_SceneSequence : const short int {
		NO_SCENE               =   -1,
		INTRO_SCENE            ,   // Image line 2   ; Text line 2  ; Menu line 2
		MOVING_SCENE           ,   // Image line 37  ; Text line 8  ; Menu line 5
		KOBOLD_SCENE           ,   // Image line 72  ; Text line 14 ; Menu line 8
		NAME_SCENE             ,   // Image line 72  ; Text line 20 ; View MenuManager.cpp PrintMenuFromScene()
		ATTACK_KOBOLD_SCENE    ,   // Image line 282 ; Text line 26 ; View MenuManager.cpp PrintMenuFromScene()
		WEAPONS_SCENE          ,   // Image line 107 ; Text line 32 ; Menu line 15
		DEAD_END_SCENE         ,   // Image line 142 ; Text line 38 ; Menu line 18 // TODO return to navigation menu at line 26
		ENNEMY_SCENE           ,   // Image line 177 ; Text line 44 ; Menu line 21
						       	    
		ROOM_ONE_LEFT          ,   // Image line 212 ;              ; Menu line 23
		ROOM_ONE_FRONT         ,   // Image line   2 ;              ; Menu line 54
		ROOM_ONE_RIGHT         ,   // Image line 247 ;              ; Menu line 54
		ROOM_ONE_BACK          ,   // Image line 282 ;              ; Menu line 23
							      				                 
		ROOM_TWO_LEFT          ,   // Image line 317 ;              ; Menu line 23
		ROOM_TWO_FRONT         ,   // Image line 353 ;              ; Menu line 54
		ROOM_TWO_RIGHT         ,   // Image line 388 ;              ; Menu line 54
		ROOM_TWO_BACK          ,   // Image line 142 ;              ; Menu line 23
							      				                 
		ROOM_THREE_LEFT        ,   // Image line 424 ;              ; Menu line 23
		ROOM_THREE_FRONT       ,   // Image line 460 ;              ; Menu line 54
		ROOM_THREE_RIGHT       ,   // Image line 495 ;              ; Menu line 45
		ROOM_THREE_BACK        ,   // Image line 531 ;              ; Menu line 23
								   
		COMBAT_SCENE           ,   // Image line 177 ;              ; Menu line 90
	};                              
	                                
	//MenuText.txt                  
	enum class E_MenuChoices : const unsigned short int {
		ENTER_NAME             =   0,    // NAME_SCENE

		NO_MENU_LINE           =   1,

		TRY_TO_MOVE            =   2,    // INTRO_SCENE
		TRY_TO_REMEBER         =   3,    // INTRO_SCENE

		LOOK_AROUND            =   5,    // MOVING_SCENE
		TRY_TO_REMEBER_TWO     =   6,    // MOVING_SCENE

		WHO_ARE_YOU            =   8,    // KOBOLD_SCENE
		ATTACK_KOBOLD          =   9,    // KOBOLD_SCENE

		TAKE_WEAPONS           =  15,    // WEAPONS_SCENE
		TAKE_WEAPONS_SELECTED  =  16,    // WEAPONS_SCENE

		GO_BACK                =  18,    // DEAD_END_SCENE
		GO_BACK_SELECTED       =  19,    // DEAD_END_SCENE

		ATTACK_ENEMY           =  21,    // ENNEMY_SCENE
		RUN_AWAY               =  22,    // ENNEMY_SCENE

		NAVIGATION_PLAIN       =  26,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_LEFT        =  34,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_RIGHT       =  42,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_FOWARD      =  50,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK
		NAVIGATION_BACK        =  58,    // Quadridirectional ROOM_*_FRONT, ROOM_*_BACK

		LR_NAVIGATION_PLAIN    =  66,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT
		LR_NAVIGATION_LEFT     =  74,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT
		LR_NAVIGATION_RIGHT    =  82,    // Bidirectional ROOM_*_LEFT, ROOM_*_RIGHT
	
		COMBAT_PLAIN           =  90,
		COMBAT_HELP            =  98,
		COMBAT_POTION          = 106,
		COMBAT_ATTACK          = 114,
		COMBAT_FLEE            = 122
	};
	                                
	enum class E_UserInput : const unsigned short int {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ENTER,
		ONE,
		TWO,
		ESC,
		EMPTY
	};

	struct S_Weapon
	{
		S_Weapon() = default;
		S_Weapon(std::string _weaponName, unsigned short int _minHitPoints, unsigned short int _maxHitPoints)
		{
			weaponName = _weaponName;
			minHitPoints = _minHitPoints;
			maxHitPoints = _maxHitPoints;
		}
		std::string weaponName = "";
		unsigned short int minHitPoints = 0;
		unsigned short int maxHitPoints = 0;
	};

}
