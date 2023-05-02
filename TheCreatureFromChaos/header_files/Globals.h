#pragma once

extern const unsigned short int G_FOUR_MENU_CHOICES;
extern const unsigned short int G_TWO_MENU_CHOICES;

extern unsigned short int G_SCENES_IMAGE_LINES[2];
extern unsigned short int G_SCENES_TEXT_LINES[2];
extern unsigned short int G_SCENES_MENU_LINES[2];

enum class E_SceneSequence {
    NO_SCENE = -1,
    INTRO_SCENE = 0, // Image line 1 ; Text line 1
    MOVING_SCENE = 1, // Image line 35 ; Text line 6
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
    EMPTY
};
