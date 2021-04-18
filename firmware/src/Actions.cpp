#include <map>
#include "Globals.h"
#include "Actions.h"
#include "KeyMap.h"
#include "Backlight.h"
#include "OLED.h"
#include "Underglow.h"
#include "Effects/StaticEffect.h"

#pragma region backlight

bool backlightUp(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        Backlight::up();
    }

    return false;
}

bool backlightDown(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        Backlight::down();
    }

    return false;
}

#pragma endregion

#pragma region underglow

int rgbSetStart = 0;
int rDelta = 0;
int gDelta = 0;
int bDelta = 0;
int timeDelta = 1000;

void startRgbChange(int r, int g, int b)
{
    rgbSetStart = millis();
    StaticEffect::add(r, g, b);
    timeDelta = 1000;
    rDelta = r;
    gDelta = g;
    bDelta = b;
}

void stopRgbChange()
{
    rDelta = 0;
    gDelta = 0;
    bDelta = 0;
}

bool redDown(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(-1, 0, 0);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

bool redUp(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(1, 0, 0);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

bool greenDown(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(0, -1, 0);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

bool greenUp(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(0, 1, 0);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

bool blueDown(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(0, 0, -1);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

bool blueUp(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
    {
        startRgbChange(0, 0, 1);
    }
    else
    {
        stopRgbChange();
    }

    return false;
}

void rgbLoop()
{
    if ((rDelta != 0 || gDelta != 0 || bDelta != 0) && (millis() - rgbSetStart > timeDelta))
    {
        StaticEffect::add(rDelta, gDelta, bDelta);
        rgbSetStart = millis();
        if (timeDelta == 1000)
        {
            timeDelta = 20;
        }
    }
}

bool nextEffect(KeyDirection direction){
    if(direction == KeyDirection::DOWN)
    {
        Underglow::nextEffect();
    }

    return false;
}

#pragma endregion

bool toggleCaps(KeyDirection direction)
{
    if (direction == KeyDirection::DOWN)
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

// clang-format off

const std::map<int, action> Actions::actionMap = {
    {KEY_00KEY_MOVELAYER, moveLayer},
    {KEY_00KEY_BLUP, backlightUp},
    {KEY_00KEY_BLDOWN, backlightDown},
    {KEY_CAPS_LOCK, toggleCaps},
    {KEY_00KEY_RED_DOWN, redDown},
    {KEY_00KEY_RED_UP, redUp},
    {KEY_00KEY_GREEN_DOWN, greenDown},
    {KEY_00KEY_GREEN_UP, greenUp},
    {KEY_00KEY_BLUE_DOWN, blueDown},
    {KEY_00KEY_BLUE_UP, blueUp},
    {KEY_00KEY_NEXT_EFFECT, nextEffect}
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

void Actions::loop()
{
    rgbLoop();
}