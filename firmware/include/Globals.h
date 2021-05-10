#ifndef Globals_h
#define Globals_h

#define COL_COUNT 16
#define ROW_COUNT 6
#define SCAN_DELAY 5
#define PIN_CHANGE_DELAY 500

#define KEY_NOKEY 0
#define KEY_00KEY_MOVELAYER 1000
#define KEY_00KEY_BLUP 1001
#define KEY_00KEY_BLDOWN 1002

#define KEY_00KEY_RED_UP 1003
#define KEY_00KEY_RED_DOWN 1004
#define KEY_00KEY_GREEN_UP 1005
#define KEY_00KEY_GREEN_DOWN 1006
#define KEY_00KEY_BLUE_UP 1007
#define KEY_00KEY_BLUE_DOWN 1008
#define KEY_00KEY_NEXT_EFFECT 1009


enum class KeyDirection {
    DOWN,
    UP
};

#endif