#ifndef Underglow_h
#define Underglow_h

enum RGBColor
{
    RED,
    GREEN,
    BLUE
};

class Underglow
{
public:
    static void setup();
    static void loop();
    static void set(int red, int green, int blue);
    static void add(int red, int green, int blue);
};

#endif