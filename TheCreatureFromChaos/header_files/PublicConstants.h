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

namespace PublicConstants {
                                                                                
	enum class E_UserInput : const unsigned short int {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ENTER,
		ONE,
		TWO,
		FLEE,
		POTION,
		HELP,
		ESC,
		EMPTY
	};

	struct S_Weapon
	{
		S_Weapon() = default;
		S_Weapon(std::string _weaponName, unsigned short int _weaponMinDamage, unsigned short int _weaponMaxDamage)
		{
			weaponName = _weaponName;
			weaponMinDamage = _weaponMinDamage;
			weaponMaxDamage = _weaponMaxDamage;
		}
		std::string weaponName = "";
		unsigned short int weaponMinDamage = 0;
		unsigned short int weaponMaxDamage = 0;
	};

}
