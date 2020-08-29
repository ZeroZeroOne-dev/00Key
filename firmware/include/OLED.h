#ifndef OLED_h
#define OLED_h

class OLED
{
public:
    static void setup();
    static void setLayer(int layer);
    static void setBacklight(String level);
};

#endif