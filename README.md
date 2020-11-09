# 001Key

Custom 75% Keyboard.

## Hardware

- Teensy 4.1 development board
- SSD1306 0.96 Inch OLED Display
- MX & Alps switch support
- Backlight (single color)

## Firmware

Custom firmware, has OLED, backlight and layer support.

Currently  no key debounce programmed in yet.

This is my first c++ project, im used to C# development, so all this stuff about header files and pointers are kinda new to me, expect some weird programming choices.

On that note; feel free to open an issue or a pull request if you think something is wrong. 😉


## OLED display

Displays current layer, backlight intensity and capslock status.

## Prototype

- 2 x 2 key matrix
- 2 backlight LED
- OLED display

![prototype](./images/2.jpeg)

## PCB

- Designed in kicad
- Used freerouting for traces

![pcbrender](./images/3.png)

![pcb](./images/4.jpeg)

## PLATE

- Designed in FreeCAD
- Spaced from PCB with (10mm) standoffs
- STL files included for 3D printing in 2 parts

![platerender](./images/8.png)

## FINISHED PRODUCT

![00Key](./images/build/DSCF2616.JPG)