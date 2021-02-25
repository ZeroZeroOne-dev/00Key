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

#include "WS2812Serial.h"

bool WS2812Serial::begin()
{
#if defined(__IMXRT1062__) // Teensy 3.x
	uint32_t hwtrigger;
#else	
	uint32_t divisor, portconfig, hwtrigger;
	KINETISK_UART_t *uart;
#endif
	switch (pin) {
#if defined(KINETISK) // Teensy 3.x
	  case 1: // Serial1
	  case 5:
	#if defined(__MK64FX512__) || defined(__MK66FX1M0__)
	  case 26:
	#endif
		uart = &KINETISK_UART0;
		divisor = BAUD2DIV(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART0_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART0;
		break;

	  case 10: // Serial2
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
	  case 31:
	#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
	  case 58:
	#endif
		uart = &KINETISK_UART1;
		divisor = BAUD2DIV2(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART1_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART1;
		break;

	  case 8: // Serial3
		uart = &KINETISK_UART2;
		divisor = BAUD2DIV3(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART2_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART2;
		break;

	#if defined(__MK64FX512__) || defined(__MK66FX1M0__)
	  case 32: // Serial4
	  case 62:
		uart = &KINETISK_UART3;
		divisor = BAUD2DIV3(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART3_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART3;
		break;

	  case 33: // Serial5
		uart = &KINETISK_UART4;
		divisor = BAUD2DIV3(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART4_RXTX;
		SIM_SCGC1 |= SIM_SCGC1_UART4;
		break;
	#endif
	#if defined(__MK64FX512__)
	  case 48: // Serial6
		uart = &KINETISK_UART5;
		divisor = BAUD2DIV3(4000000);
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART5_RXTX;
		SIM_SCGC1 |= SIM_SCGC1_UART5;
		break;
	#endif

#elif defined(KINETISL)	// Teensy LC
	  case 1: // Serial1
	  case 5:
	  	// NOT SURE HOW THIS WORKS ON LC????? 
		uart = &KINETISK_UART0;
		divisor = 1;
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
		hwtrigger = DMAMUX_SOURCE_UART0_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART0;
		break;
	  case 4:
		uart = &KINETISK_UART0;
		divisor = 1;
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(2);
		hwtrigger = DMAMUX_SOURCE_UART0_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART0;
		break;
	  case 24:
		uart = &KINETISK_UART0;
		divisor = 1;
		portconfig = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(4);
		hwtrigger = DMAMUX_SOURCE_UART0_TX;
		SIM_SCGC4 |= SIM_SCGC4_UART0;
		break;

#elif defined(__IMXRT1062__)
	  case 1: // Serial1
#if defined(ARDUINO_TEENSY41)
	  case 53:
#endif
		uart = &IMXRT_LPUART6; 
		CCM_CCGR3 |= CCM_CCGR3_LPUART6(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART6_TX; 
		break;
	  case 8: // Serial2
		uart = &IMXRT_LPUART4; 
		CCM_CCGR1 |= CCM_CCGR1_LPUART4(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART4_TX; 
		break;
	  case 14: // Serial3
		uart = &IMXRT_LPUART2; 
		CCM_CCGR0 |= CCM_CCGR0_LPUART2(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART2_TX; 
		break;
	  case 17: // Serial4
		uart = &IMXRT_LPUART3; 
		CCM_CCGR0 |= CCM_CCGR0_LPUART3(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART3_TX; 
		break;
	  case 20: // Serial5
#if defined(ARDUINO_TEENSY40)
	  case 39: // Serial5 alt
#elif defined(ARDUINO_TEENSY41)
	  case 47:
#endif
		uart = &IMXRT_LPUART8; 
		CCM_CCGR6 |= CCM_CCGR6_LPUART8(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART8_TX; 
		break;
	  case 24: // Serial6
		uart = &IMXRT_LPUART1; 
		CCM_CCGR5 |= CCM_CCGR5_LPUART1(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART1_TX; 
		break;
	  case 29: // Serial7
		uart = &IMXRT_LPUART7; 
		CCM_CCGR5 |= CCM_CCGR5_LPUART7(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART7_TX; 
		break;
#if defined(ARDUINO_TEENSY41)
	  case 35:
		uart = &IMXRT_LPUART5; 
		CCM_CCGR3 |= CCM_CCGR3_LPUART5(CCM_CCGR_ON);
		hwtrigger = DMAMUX_SOURCE_LPUART5_TX; 
		break;
#endif		
#endif
	  default:
		return false; // pin not supported
	}
	if (!dma) {
		dma = new DMAChannel;
		if (!dma) return false; // unable to allocate DMA channel
	}
#if defined(__IMXRT1062__)
	// Convert Baud
	// Computed values for 4mhz  
	uart->CTRL = 0;	// clear everything
	uart->BAUD = LPUART_BAUD_OSR(5) | LPUART_BAUD_SBR(1) | LPUART_BAUD_TDMAE;  // set baud configure for transfer DMA
	uart->PINCFG = 0;
	uint16_t tx_fifo_size = (((uart->FIFO >> 4) & 0x7) << 2);
	uint8_t tx_water = (tx_fifo_size < 16) ? tx_fifo_size >> 1 : 7;
//	uart->WATER = LPUART_WATER_TXWATER(1);	// guessing here? 
//	uart->FIFO = 0;	// disable the fifo.
	uart->WATER = LPUART_WATER_TXWATER(tx_water);
	uart->FIFO |= LPUART_FIFO_TXFE;

	uart->CTRL = (LPUART_CTRL_TE /*| LPUART_CTRL_TIE */ | LPUART_CTRL_TXINV); // enable transmitter and invert
	// We need to configure the TX pin now.
	*(portControlRegister(pin)) =  IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
	uint32_t pinmuxval = 2; // most of them use mux ALT2
#if defined(ARDUINO_TEENSY41)
	if (pin == 35) pinmuxval = 1;
#endif
	*(portConfigRegister(pin)) = pinmuxval;

	dma->destination((volatile uint8_t&)uart->DATA);
	//Serial.printf("HWTrigger: %x\n", hwtrigger);
#else
#if defined(KINETISK)
	if (divisor < 32) divisor = 32;
	uart->BDH = (divisor >> 13) & 0x1F;
	uart->BDL = (divisor >> 5) & 0xFF;
	uart->C4 = divisor & 0x1F;
#elif defined(KINETISL)
	uart->BDH = (divisor >> 8) & 0x1F;
	uart->BDL = divisor & 0xFF;
	uart->C4 = 11;
#endif
	uart->C1 = 0;
	uart->C2 = UART_C2_TE | UART_C2_TIE;
	uart->C3 = UART_C3_TXINV;
	uart->C5 = UART_C5_TDMAS;
#if defined(KINETISK)
	uart->PFIFO = 0; // TODO: is this ok for Serial3-6?
#endif
	*(portConfigRegister(pin)) = portconfig;
	dma->destination(uart->D);
#endif 

	dma->triggerAtHardwareEvent(hwtrigger);
	memset(drawBuffer, 0, numled * 3);
	return true;
}

void WS2812Serial::show()
{
	uint32_t microseconds_per_led, bytes_per_led;

	// wait if prior DMA still in progress
#if defined(KINETISK)
	while ((DMA_ERQ & (1 << dma->channel))) {
		yield();
	}
#elif defined(KINETISL)
	while ((dma->CFG->DCR & DMA_DCR_ERQ)) {
		yield();
	}
#elif defined(__IMXRT1062__)
	//Serial.println("Show called");
	while ((DMA_ERQ & (1 << dma->channel))) {
		yield();
	}
	//Serial.println("After Yield");
#endif
	// copy drawing buffer to frame buffer
	if (config < 6) {
		// RGB
		const uint8_t *p = drawBuffer;
		const uint8_t *end = p + (numled * 3);
		uint8_t *fb = frameBuffer;
		while (p < end) {
			uint8_t b = *p++;
			uint8_t g = *p++;
			uint8_t r = *p++;
			uint32_t mult = brightness + 1;
			b = (b * mult) >> 8;
			g = (g * mult) >> 8;
			r = (r * mult) >> 8;
			uint32_t n=0;
			switch (config) {
			  case WS2812_RGB: n = (r << 16) | (g << 8) | b; break;
			  case WS2812_RBG: n = (r << 16) | (b << 8) | g; break;
			  case WS2812_GRB: n = (g << 16) | (r << 8) | b; break;
			  case WS2812_GBR: n = (g << 16) | (b << 8) | r; break;
			  case WS2812_BRG: n = (b << 16) | (r << 8) | g; break;
			  case WS2812_BGR: n = (b << 16) | (g << 8) | r; break;
			}
			const uint8_t *stop = fb + 12;
			do {
				uint8_t x = 0x08;
				if (!(n & 0x00800000)) x |= 0x07;
				if (!(n & 0x00400000)) x |= 0xE0;
				n <<= 2;
				*fb++ = x;
			} while (fb < stop);
		}
		microseconds_per_led = 30;
		bytes_per_led = 12;
	} else {
		// RGBW
		const uint8_t *p = drawBuffer;
		const uint8_t *end = p + (numled * 4);
		uint8_t *fb = frameBuffer;
		while (p < end) {
			uint8_t b = *p++;
			uint8_t g = *p++;
			uint8_t r = *p++;
			uint8_t w = *p++;
			uint32_t mult = brightness + 1;
			b = (b * mult) >> 8;
			g = (g * mult) >> 8;
			r = (r * mult) >> 8;
			w = (w * mult) >> 8;
			uint32_t n=0;
			switch (config) {
			  case WS2812_RGBW: n = (r << 24) | (g << 16) | (b << 8) | w; break;
			  case WS2812_RBGW: n = (r << 24) | (b << 16) | (g << 8) | w; break;
			  case WS2812_GRBW: n = (g << 24) | (r << 16) | (b << 8) | w; break;
			  case WS2812_GBRW: n = (g << 24) | (b << 16) | (r << 8) | w; break;
			  case WS2812_BRGW: n = (b << 24) | (r << 16) | (g << 8) | w; break;
			  case WS2812_BGRW: n = (b << 24) | (b << 16) | (r << 8) | w; break;
			  case WS2812_WRGB: n = (w << 24) | (r << 16) | (g << 8) | b; break;
			  case WS2812_WRBG: n = (w << 24) | (r << 16) | (b << 8) | g; break;
			  case WS2812_WGRB: n = (w << 24) | (g << 16) | (r << 8) | b; break;
			  case WS2812_WGBR: n = (w << 24) | (g << 16) | (b << 8) | r; break;
			  case WS2812_WBRG: n = (w << 24) | (b << 16) | (r << 8) | g; break;
			  case WS2812_WBGR: n = (w << 24) | (b << 16) | (g << 8) | r; break;
			  case WS2812_RWGB: n = (r << 24) | (w << 16) | (g << 8) | b; break;
			  case WS2812_RWBG: n = (r << 24) | (w << 16) | (b << 8) | g; break;
			  case WS2812_GWRB: n = (g << 24) | (w << 16) | (r << 8) | b; break;
			  case WS2812_GWBR: n = (g << 24) | (w << 16) | (b << 8) | r; break;
			  case WS2812_BWRG: n = (b << 24) | (w << 16) | (r << 8) | g; break;
			  case WS2812_BWGR: n = (b << 24) | (w << 16) | (g << 8) | r; break;
			  case WS2812_RGWB: n = (r << 24) | (g << 16) | (w << 8) | b; break;
			  case WS2812_RBWG: n = (r << 24) | (b << 16) | (w << 8) | g; break;
			  case WS2812_GRWB: n = (g << 24) | (r << 16) | (w << 8) | b; break;
			  case WS2812_GBWR: n = (g << 24) | (b << 16) | (w << 8) | r; break;
			  case WS2812_BRWG: n = (b << 24) | (r << 16) | (w << 8) | g; break;
			  case WS2812_BGWR: n = (b << 24) | (g << 16) | (w << 8) | r; break;
			}
			const uint8_t *stop = fb + 16;
			do {
				uint8_t x = 0x08;
				if (!(n & 0x80000000)) x |= 0x07;
				if (!(n & 0x40000000)) x |= 0xE0;
				n <<= 2;
				*fb++ = x;
			} while (fb < stop);
		}
		microseconds_per_led = 40;
		bytes_per_led = 16;
	}
	// wait 300us WS2812 reset time
	uint32_t min_elapsed = (numled * microseconds_per_led) + 300;
	if (min_elapsed < 2500) min_elapsed = 2500;
	uint32_t m;
	while (1) {
		m = micros();
		if ((m - prior_micros) > min_elapsed) break;
		yield();
	}
	prior_micros = m;
	// start DMA transfer to update LEDs  :-)
#if defined(KINETISK)
	dma->sourceBuffer(frameBuffer, numled * bytes_per_led);
	dma->transferSize(1);
	dma->transferCount(numled * bytes_per_led);
	dma->disableOnCompletion();
	dma->enable();
#elif defined(KINETISL)
	dma->CFG->SAR = frameBuffer;
	dma->CFG->DSR_BCR = 0x01000000;
	dma->CFG->DSR_BCR = numled * bytes_per_led;
	dma->CFG->DCR = DMA_DCR_ERQ | DMA_DCR_CS | DMA_DCR_SSIZE(1) |
		DMA_DCR_SINC | DMA_DCR_DSIZE(1) | DMA_DCR_D_REQ;
#elif defined(__IMXRT1062__)
	// See if we need to muck with DMA cache...
	if ((uint32_t)frameBuffer >= 0x20200000u)  arm_dcache_flush(frameBuffer, numled * bytes_per_led);
	
	dma->sourceBuffer(frameBuffer, numled * bytes_per_led);
//	dma->transferSize(1);
	dma->transferCount(numled * bytes_per_led);
	dma->disableOnCompletion();

/*	Serial.printf("%x %x:", (uint32_t)dma, (uint32_t)dma->TCD);

	Serial.printf("SA:%x SO:%d AT:%x NB:%x SL:%d DA:%x DO: %d CI:%x DL:%x CS:%x BI:%x\n", (uint32_t)dma->TCD->SADDR,
	dma->TCD->SOFF, dma->TCD->ATTR, dma->TCD->NBYTES, dma->TCD->SLAST, (uint32_t)dma->TCD->DADDR, 
	dma->TCD->DOFF, dma->TCD->CITER, dma->TCD->DLASTSGA, dma->TCD->CSR, dma->TCD->BITER);
*/
	uart->STAT = 0;	// try clearing out the status
	dma->enable();

#endif
}

