#include <map>
#include "Globals.h"
#include "Actions.h"
#include "KeyMap.h"
#include "Backlight.h"
#include "OLED.h"

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

// clang-format off

const std::map<int, action> Actions::actionMap = {
    {KEY_00KEY_MOVELAYER, moveLayer},
    {KEY_00KEY_BLUP, backlightUp},
    {KEY_00KEY_BLDOWN, backlightDown},
    {KEY_CAPS_LOCK, toggleCaps}
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