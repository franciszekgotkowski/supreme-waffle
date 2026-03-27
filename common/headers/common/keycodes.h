#pragma once

typedef enum {
    K_A,	K_B,	K_C,	K_D,
    K_E,	K_F,	K_G,	K_H,
    K_I,	K_J,	K_K,	K_L,
    K_M,	K_N,	K_O,	K_P,
    K_Q,	K_R,	K_S,	K_T,
    K_U,	K_V,	K_W,	K_X,
    K_Y,	K_Z,	K_0,	K_1,
    K_2,	K_3,	K_4,	K_5,
    K_6,	K_7,	K_8,	K_9,
    K_SPACE,	K_ENTER,	K_BACKSPACE,	K_ESC,

    KEYBOARD_KEYS_AMOUNT
} KeyboardKeys ;

typedef enum {
    K_MOD_SHIFT,	K_MOD_CTRL,		K_MOD_ALT,		K_MOD_SUPER,
    K_MOD_CAPS_LOCK, K_MOD_NUM_LOCK,

    KEYBOARD_MODS_AMOUNT
} KeyboardMods ;

typedef enum {
    M_LEFT,
    M_RIGHT,
    M_MIDDLE,
    MB_4, // Often "Back"
    MB_5, // Often "Forward"
    MB_6,
    MB_7,
    MB_8,

    MOUSE_BUTTONS_AMOUNT
} MouseInput ;

