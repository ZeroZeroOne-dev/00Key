#include "Globals.h"
#include "Actions.h"
#include "KeyMap.h"
#include <map>

bool moveLayer()
{
    KeyMap::moveLayer();
    return false;
}

// clang-format off

const std::map<int, action> Actions::actionMap = {
    {KEY_00KEY_MOVELAYER, moveLayer}
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