#include <map>
#include "Globals.h"
#include "Actions.h"
#include "KeyMap.h"
#include "Backlight.h"
#include "OLED.h"
#include "Underglow.h"

bool toggleCaps(KeyDirection direction)
{
    if (direction == DOWN)
    {
        OLED::toggleCaps();
    }

    return true;
}

bool moveLayer(KeyDirection direction)
{
    KeyMap::moveLayer();
    return false;
}

#pragma region backlight

bool backlightUp(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Backlight::up();
    }

    return false;
}

bool backlightDown(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Backlight::down();
    }

    return false;
}

#pragma endregion

#pragma region underglow

bool redDown(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(-1, 0, 0);
    }

    return false;
}

bool redUp(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(1, 0, 0);
    }

    return false;
}

bool greenDown(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(0, -1, 0);
    }

    return false;
}

bool greenUp(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(0, 1, 0);
    }

    return false;
}

bool blueDown(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(0, 0, -1);
    }

    return false;
}

bool blueUp(KeyDirection direction)
{
    if (direction == DOWN)
    {
        Underglow::add(0, 0, 1);
    }

    return false;
}

#pragma endregion

// clang-format off

const std::map<int, action> Actions::actionMap = {
    {KEY_00KEY_MOVELAYER, moveLayer},
    {KEY_00KEY_BLUP, backlightUp},
    {KEY_00KEY_BLDOWN, backlightDown},
    {KEY_CAPS_LOCK, toggleCaps},
    {KEY_RED_DOWN, redDown},
    {KEY_RED_UP, redUp},
    {KEY_GREEN_DOWN, greenDown},
    {KEY_GREEN_UP, greenUp},
    {KEY_BLUE_DOWN, blueDown},
    {KEY_BLUE_DOWN, blueUp}
};

// clang-format on

action Actions::getAction(int key)
{
    if (Actions::actionMap.count(key))
    {
        return Actions::actionMap.find(key)->second;
    }

    return NULL;
};