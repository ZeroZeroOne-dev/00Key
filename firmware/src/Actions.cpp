#include <map>
#include "Globals.h"
#include "Actions.h"
#include "KeyMap.h"
#include "Backlight.h"

// clang-format off

const std::map<int, action> Actions::actionMap = {
    {KEY_00KEY_MOVELAYER, KeyMap::moveLayer},
    {KEY_00KEY_BLUP, Backlight::up},
    {KEY_00KEY_BLDOWN, Backlight::down},
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