EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L teensy:Teensy4.1 U1
U 1 1 5F67FF94
P 2400 3400
F 0 "U1" H 2400 5965 50  0000 C CNN
F 1 "Teensy4.1" H 2400 5874 50  0000 C CNN
F 2 "teensy:Teensy41" H 2000 3800 50  0001 C CNN
F 3 "" H 2000 3800 50  0001 C CNN
	1    2400 3400
	1    0    0    -1  
$EndComp
Text GLabel 3500 1550 2    50   Input ~ 0
col0
Text GLabel 3500 1650 2    50   Input ~ 0
col1
Text GLabel 3500 1750 2    50   Input ~ 0
col2
Text GLabel 3500 1850 2    50   Input ~ 0
col3
Text GLabel 3500 1950 2    50   Input ~ 0
col4
Text GLabel 3500 2050 2    50   Input ~ 0
col5
Text GLabel 3500 2150 2    50   Input ~ 0
col6
Text GLabel 3500 2250 2    50   Input ~ 0
col7
Text GLabel 3500 2350 2    50   Input ~ 0
col8
Text GLabel 3500 2450 2    50   Input ~ 0
col9
Text GLabel 3500 2750 2    50   Input ~ 0
col10
Text GLabel 3500 2850 2    50   Input ~ 0
col11
Text GLabel 3500 2950 2    50   Input ~ 0
col12
Text GLabel 3500 3050 2    50   Input ~ 0
col13
Text GLabel 3500 3150 2    50   Input ~ 0
col14
Text GLabel 3500 3250 2    50   Input ~ 0
col15
Text GLabel 1300 1350 0    50   Input ~ 0
row0
Text GLabel 1300 1450 0    50   Input ~ 0
row1
Text GLabel 1300 1550 0    50   Input ~ 0
row2
Text GLabel 1300 1650 0    50   Input ~ 0
row3
Text GLabel 1300 1750 0    50   Input ~ 0
row4
Text GLabel 1300 1850 0    50   Input ~ 0
row5
Text GLabel 1300 2750 0    50   Input ~ 0
OLEDSCL
Text GLabel 1300 2850 0    50   Input ~ 0
OLEDSDA
Text GLabel 1300 3150 0    50   Input ~ 0
LEDPWM
Text GLabel 4500 1050 0    50   Input ~ 0
col0
Text GLabel 4500 1150 0    50   Input ~ 0
col1
Text GLabel 4500 1250 0    50   Input ~ 0
col2
Text GLabel 4500 1350 0    50   Input ~ 0
col3
Text GLabel 4500 1450 0    50   Input ~ 0
col4
Text GLabel 4500 1550 0    50   Input ~ 0
col5
Text GLabel 4500 1650 0    50   Input ~ 0
col6
Text GLabel 4500 1750 0    50   Input ~ 0
col7
Text GLabel 4500 1850 0    50   Input ~ 0
col8
Text GLabel 4500 1950 0    50   Input ~ 0
col9
Text GLabel 4500 2050 0    50   Input ~ 0
col10
Text GLabel 4500 2150 0    50   Input ~ 0
col11
Text GLabel 4500 2250 0    50   Input ~ 0
col12
Text GLabel 4500 2350 0    50   Input ~ 0
col13
Text GLabel 4500 2450 0    50   Input ~ 0
col14
Text GLabel 4500 2550 0    50   Input ~ 0
col15
Text GLabel 5200 1050 2    50   Input ~ 0
row0
Text GLabel 5200 1150 2    50   Input ~ 0
row1
Text GLabel 5200 1250 2    50   Input ~ 0
row2
Text GLabel 5200 1350 2    50   Input ~ 0
row3
Text GLabel 5200 1450 2    50   Input ~ 0
row4
Text GLabel 5200 1550 2    50   Input ~ 0
row5
$Comp
L Transistor_FET:IRLZ44N Q1
U 1 1 5F730CB8
P 4700 3450
F 0 "Q1" H 4904 3496 50  0000 L CNN
F 1 "IRLZ44N" H 4904 3405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4950 3375 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irlz44n.pdf" H 4700 3450 50  0001 L CNN
	1    4700 3450
	1    0    0    -1  
$EndComp
Text GLabel 4350 3450 0    50   Input ~ 0
LEDPWM
Text GLabel 3500 1350 2    50   Input ~ 0
GND
Text GLabel 4800 3950 3    50   Input ~ 0
GND
Text GLabel 4800 3250 1    50   Input ~ 0
LEDGND
Text GLabel 3500 1250 2    50   Input ~ 0
5V
Text GLabel 3500 1450 2    50   Input ~ 0
3.3V
$Sheet
S 4500 1000 700  1650
U 5F68B66F
F0 "keys" 50
F1 "switches.sch" 50
F2 "col0" I L 4500 1050 50 
F3 "col1" I L 4500 1150 50 
F4 "col2" I L 4500 1250 50 
F5 "col3" I L 4500 1350 50 
F6 "col4" I L 4500 1450 50 
F7 "col5" I L 4500 1550 50 
F8 "col6" I L 4500 1650 50 
F9 "col7" I L 4500 1750 50 
F10 "col8" I L 4500 1850 50 
F11 "col9" I L 4500 1950 50 
F12 "col10" I L 4500 2050 50 
F13 "col11" I L 4500 2150 50 
F14 "col12" I L 4500 2250 50 
F15 "col13" I L 4500 2350 50 
F16 "col14" I L 4500 2450 50 
F17 "col15" I L 4500 2550 50 
F18 "row0" I R 5200 1050 50 
F19 "row1" I R 5200 1150 50 
F20 "row2" I R 5200 1250 50 
F21 "row3" I R 5200 1350 50 
F22 "row4" I R 5200 1450 50 
F23 "row5" I R 5200 1550 50 
F24 "LEDGND" I R 5200 2550 50 
F25 "5V" I R 5200 2450 50 
$EndSheet
Text GLabel 5200 2450 2    50   Input ~ 0
5V
Text GLabel 5200 2550 2    50   Input ~ 0
LEDGND
Text GLabel 5100 4650 2    50   Input ~ 0
GND
Text GLabel 5100 4750 2    50   Input ~ 0
3.3V
Text GLabel 5100 4850 2    50   Input ~ 0
OLEDSCL
Text GLabel 5100 4950 2    50   Input ~ 0
OLEDSDA
Wire Wire Line
	4350 3450 4450 3450
$Comp
L Device:R R_Q1_GATE_1
U 1 1 5F82DF3F
P 4450 3700
F 0 "R_Q1_GATE_1" H 4380 3746 50  0000 R CNN
F 1 "10K" H 4380 3655 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4380 3700 50  0001 C CNN
F 3 "~" H 4450 3700 50  0001 C CNN
	1    4450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3450 4450 3550
Connection ~ 4450 3450
Wire Wire Line
	4450 3450 4500 3450
Wire Wire Line
	4800 3650 4800 3850
Wire Wire Line
	4450 3850 4800 3850
Connection ~ 4800 3850
Wire Wire Line
	4800 3850 4800 3950
$Comp
L oled:SSD1306 OLED1
U 1 1 5F70EDBF
P 4750 4800
F 0 "OLED1" V 4335 4858 50  0000 C CNN
F 1 "SSD1306" V 4426 4858 50  0000 C CNN
F 2 "oled:128x64OLED" H 4750 5050 50  0001 C CNN
F 3 "" H 4750 5050 50  0001 C CNN
	1    4750 4800
	0    1    1    0   
$EndComp
$EndSCHEMATC
