/*  WS2812Serial - Non-blocking WS2812 LED Display Library
    https://github.com/PaulStoffregen/WS2812Serial
    Copyright (c) 2017 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef WS2812Serial_h_
#define WS2812Serial_h_

#include <Arduino.h>
#include "DMAChannel.h"

#define WS2812_RGB      0       // The WS2811 datasheet documents this way
#define WS2812_RBG      1
#define WS2812_GRB      2       // Most LED strips are wired this way
#define WS2812_GBR      3
#define WS2812_BRG      4
#define WS2812_BGR      5
#define WS2812_RGBW     6
#define WS2812_RBGW     7
#define WS2812_GRBW     8
#define WS2812_GBRW     9
#define WS2812_BRGW     10
#define WS2812_BGRW     11
#define WS2812_WRGB     12
#define WS2812_WRBG     13
#define WS2812_WGRB     14
#define WS2812_WGBR     15
#define WS2812_WBRG     16
#define WS2812_WBGR     17
#define WS2812_RWGB     18
#define WS2812_RWBG     19
#define WS2812_GWRB     20
#define WS2812_GWBR     21
#define WS2812_BWRG     22
#define WS2812_BWGR     23
#define WS2812_RGWB     24
#define WS2812_RBWG     25
#define WS2812_GRWB     26
#define WS2812_GBWR     27
#define WS2812_BRWG     28
#define WS2812_BGWR     29


class WS2812Serial {
public:
	constexpr WS2812Serial(uint16_t num, void *fb, void *db, uint8_t pin, uint8_t cfg) :
		numled(num), pin(pin), config(cfg),
		frameBuffer((uint8_t *)fb), drawBuffer((uint8_t *)db) {
	}
	bool begin();
	void setPixel(uint32_t num, uint32_t color) {
		if (num >= numled) return;
		if (config < 6) {
			num *= 3;
			drawBuffer[num+0] = color & 255;
			drawBuffer[num+1] = (color >> 8) & 255;
			drawBuffer[num+2] = (color >> 16) & 255;
		} else {
			num *= 4;
			drawBuffer[num+0] = color & 255;
			drawBuffer[num+1] = (color >> 8) & 255;
			drawBuffer[num+2] = (color >> 16) & 255;
			drawBuffer[num+3] = (color >> 24) & 255;
		}
	}
	void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue) {
		setPixel(num, Color(red, green, blue));
	}
	void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
		setPixel(num, Color(red, green, blue, white));
	}
	void clear() {
        	memset(drawBuffer, 0, numled * 3);
	} 	
	void show();
	bool busy();
	uint16_t numPixels() {
		return numled;
	}
	// Functions for compatibility with Adafruit_NeoPixel
	void setPixelColor(uint16_t num, uint32_t color) {
		setPixel(num, color);
	}
	void setPixelColor(uint16_t num, uint8_t red, uint8_t green, uint8_t blue) {
		setPixel(num, red, green, blue);
	}
	void setPixelColor(uint16_t num, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
		setPixel(num, red, green, blue, white);
	}
	void setBrightness(uint8_t n) {
		brightness = n;
	}
	uint8_t getBrightness() {
		return brightness;
	}
	uint32_t Color(uint8_t red, uint8_t green, uint8_t blue) {
		return (red << 16) | (green << 8) | blue;
	}
	uint32_t Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
		return (white << 24) | (red << 16) | (green << 8) | blue;
	}
private:
	const uint16_t numled;
	const uint8_t pin;
	const uint8_t config;
	uint8_t *frameBuffer;
	uint8_t *drawBuffer;
	DMAChannel *dma = nullptr;
	uint32_t prior_micros = 0;
	uint8_t brightness = 255;
	#if defined(__IMXRT1062__) // Teensy 3.x
	IMXRT_LPUART_t *uart = nullptr; 
	#endif
};

#endif
