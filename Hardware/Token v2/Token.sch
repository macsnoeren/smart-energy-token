EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ELC - Team RED Token Infrastructure"
Date "2021-03-23"
Rev "2.0"
Comp "Avans Hogeschool"
Comment1 "Expertise Centrum Technische Innovatie"
Comment2 "Lectoraat Smart Energy"
Comment3 "Maurice Snoeren"
Comment4 ""
$EndDescr
$Comp
L power:+3.3V #PWR05
U 1 1 5EB467C3
P 6300 2750
F 0 "#PWR05" H 6300 2600 50  0001 C CNN
F 1 "+3.3V" H 6315 2923 50  0000 C CNN
F 2 "" H 6300 2750 50  0001 C CNN
F 3 "" H 6300 2750 50  0001 C CNN
	1    6300 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5EB46DAA
P 6300 3600
F 0 "#PWR06" H 6300 3350 50  0001 C CNN
F 1 "GND" H 6305 3427 50  0000 C CNN
F 2 "" H 6300 3600 50  0001 C CNN
F 3 "" H 6300 3600 50  0001 C CNN
	1    6300 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3300 6300 3300
Wire Wire Line
	6300 3000 6200 3000
$Comp
L Device:C C1
U 1 1 5EB59CE1
P 1350 2850
F 0 "C1" H 1465 2896 50  0000 L CNN
F 1 "10nF" H 1465 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1388 2700 50  0001 C CNN
F 3 "~" H 1350 2850 50  0001 C CNN
	1    1350 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5EB5A1CC
P 1800 2850
F 0 "C2" H 1915 2896 50  0000 L CNN
F 1 "10uF" H 1915 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 1838 2700 50  0001 C CNN
F 3 "~" H 1800 2850 50  0001 C CNN
	1    1800 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5EB5A4D2
P 1450 3000
F 0 "#PWR07" H 1450 2750 50  0001 C CNN
F 1 "GND" H 1455 2827 50  0000 C CNN
F 2 "" H 1450 3000 50  0001 C CNN
F 3 "" H 1450 3000 50  0001 C CNN
	1    1450 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3000 1450 3000
Wire Wire Line
	1800 3000 1450 3000
Connection ~ 1450 3000
Wire Wire Line
	1800 2700 1600 2700
$Comp
L power:+3.3V #PWR08
U 1 1 5EB5B6E3
P 1600 2600
F 0 "#PWR08" H 1600 2450 50  0001 C CNN
F 1 "+3.3V" H 1615 2773 50  0000 C CNN
F 2 "" H 1600 2600 50  0001 C CNN
F 3 "" H 1600 2600 50  0001 C CNN
	1    1600 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2600 1600 2700
Connection ~ 1600 2700
Wire Wire Line
	1600 2700 1350 2700
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J4
U 1 1 5EB66DC4
P 3200 2650
F 0 "J4" H 3250 2967 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 3250 2876 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x04_P2.54mm_Vertical" H 3200 2650 50  0001 C CNN
F 3 "~" H 3200 2650 50  0001 C CNN
	1    3200 2650
	1    0    0    -1  
$EndComp
Text GLabel 2950 2550 0    50   Input ~ 0
IRQ
Text GLabel 2950 2650 0    50   Input ~ 0
MOSI
Text GLabel 2950 2750 0    50   Input ~ 0
CSN
Text GLabel 2950 2850 0    50   Input ~ 0
VCC
Text GLabel 3550 2750 2    50   Input ~ 0
CE
Text GLabel 3550 2850 2    50   Input ~ 0
GND
Wire Wire Line
	2950 2550 3000 2550
Wire Wire Line
	2950 2650 3000 2650
Wire Wire Line
	2950 2750 3000 2750
Wire Wire Line
	2950 2850 3000 2850
Wire Wire Line
	3500 2750 3550 2750
Wire Wire Line
	3500 2850 3550 2850
$Comp
L power:GND #PWR010
U 1 1 5EB6B830
P 3500 2950
F 0 "#PWR010" H 3500 2700 50  0001 C CNN
F 1 "GND" H 3505 2777 50  0000 C CNN
F 2 "" H 3500 2950 50  0001 C CNN
F 3 "" H 3500 2950 50  0001 C CNN
	1    3500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2950 3500 2850
Connection ~ 3500 2850
$Comp
L power:+3.3V #PWR09
U 1 1 5EB6C290
P 2550 2950
F 0 "#PWR09" H 2550 2800 50  0001 C CNN
F 1 "+3.3V" H 2565 3123 50  0000 C CNN
F 2 "" H 2550 2950 50  0001 C CNN
F 3 "" H 2550 2950 50  0001 C CNN
	1    2550 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2950 3000 2950
Wire Wire Line
	3000 2950 3000 2850
Connection ~ 3000 2850
Wire Wire Line
	3500 2550 3550 2550
Wire Wire Line
	3500 2650 3550 2650
Text Notes 5850 3450 1    50   ~ 0
OTHER TOKEN
Wire Wire Line
	6300 2750 6300 3000
Wire Wire Line
	6300 3300 6300 3600
Text Notes 2950 2300 0    50   ~ 0
Module: nRF24L01
Text Notes 1500 7400 0    50   ~ 0
https://npk-stn.ru/2019/07/19/simple_programming_attiny414_via_updi/?lang=en
$Comp
L MCU_Microchip_ATtiny:ATtiny202-SS U1
U 1 1 605A875E
P 1750 4350
F 0 "U1" H 1221 4396 50  0000 R CNN
F 1 "ATtiny202-SS" H 1221 4305 50  0000 R CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1750 4350 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny202-402-AVR-MCU-with-Core-Independent-Peripherals_and-picoPower-40001969A.pdf" H 1750 4350 50  0001 C CNN
	1    1750 4350
	1    0    0    -1  
$EndComp
Text GLabel 2500 3850 2    50   Input ~ 0
UPDI
Wire Wire Line
	2350 4050 2450 4050
Text GLabel 2550 4000 2    50   Input ~ 0
MOSI
Text GLabel 3300 4250 2    50   Input ~ 0
MISO
Text GLabel 2700 4450 2    50   Input ~ 0
SCK
Text GLabel 2600 4150 2    50   Input ~ 0
DATA_BOTTOM
Text GLabel 2450 4750 2    50   Input ~ 0
DATA_TOP_CLK
Text GLabel 2950 4350 2    50   Input ~ 0
DATA_BOTTOM_CLK
Wire Wire Line
	2550 4150 2550 4000
Wire Wire Line
	2350 4150 2550 4150
Text GLabel 2550 4600 2    50   Input ~ 0
DATA_TOP
Wire Wire Line
	2350 4550 2450 4550
Wire Wire Line
	2600 4150 2550 4150
Connection ~ 2550 4150
Wire Wire Line
	2350 4450 2550 4450
Wire Wire Line
	2550 4450 2550 4600
Wire Wire Line
	2450 4550 2450 4750
Wire Wire Line
	2700 4350 2700 4450
Wire Wire Line
	2350 4350 2700 4350
Wire Wire Line
	2950 4350 2700 4350
Connection ~ 2700 4350
$Comp
L Device:R_Small R2
U 1 1 605C3635
P 3250 3950
F 0 "R2" H 3150 4000 50  0000 C CNN
F 1 "100k" H 3100 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 3250 3950 50  0001 C CNN
F 3 "~" H 3250 3950 50  0001 C CNN
	1    3250 3950
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 605C63C4
P 1750 3650
F 0 "#PWR01" H 1750 3500 50  0001 C CNN
F 1 "+3.3V" H 1765 3823 50  0000 C CNN
F 2 "" H 1750 3650 50  0001 C CNN
F 3 "" H 1750 3650 50  0001 C CNN
	1    1750 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3650 1750 3700
$Comp
L power:GND #PWR02
U 1 1 605C885B
P 1750 5050
F 0 "#PWR02" H 1750 4800 50  0001 C CNN
F 1 "GND" H 1755 4877 50  0000 C CNN
F 2 "" H 1750 5050 50  0001 C CNN
F 3 "" H 1750 5050 50  0001 C CNN
	1    1750 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 4950 1750 5000
Wire Wire Line
	3250 3850 3250 3700
Wire Wire Line
	3250 3700 1750 3700
Connection ~ 1750 3700
Wire Wire Line
	1750 3700 1750 3750
Wire Wire Line
	2350 4250 3250 4250
Wire Wire Line
	3250 4050 3250 4250
Connection ~ 3250 4250
Wire Wire Line
	3250 4250 3300 4250
Text Notes 3300 3800 0    50   ~ 0
Resistor placed\nfor token not\nbuilding
Text Notes 3700 4200 0    50   ~ 0
Building uses MOSI, MISO and SCK for RF.
Text Notes 3700 4300 0    50   ~ 0
Token uses MOSI and SCK to communicatie to bottom (building or token).
$Comp
L Device:R_Small R1
U 1 1 605D300C
P 2550 3500
F 0 "R1" V 2354 3500 50  0000 C CNN
F 1 "220" V 2445 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 2550 3500 50  0001 C CNN
F 3 "~" H 2550 3500 50  0001 C CNN
	1    2550 3500
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1
U 1 1 605D332F
P 2850 3500
F 0 "D1" H 2843 3245 50  0000 C CNN
F 1 "LED" H 2843 3336 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric_Pad1.22x1.90mm_HandSolder" H 2850 3500 50  0001 C CNN
F 3 "~" H 2850 3500 50  0001 C CNN
	1    2850 3500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 605D41CE
P 3000 3550
F 0 "#PWR011" H 3000 3300 50  0001 C CNN
F 1 "GND" H 3100 3550 50  0000 C CNN
F 2 "" H 3000 3550 50  0001 C CNN
F 3 "" H 3000 3550 50  0001 C CNN
	1    3000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3500 3000 3550
Wire Wire Line
	2700 3500 2650 3500
Wire Wire Line
	2450 4050 2450 3850
Wire Wire Line
	2500 3850 2450 3850
Connection ~ 2450 3850
Wire Wire Line
	2450 3850 2450 3750
Text Notes 2000 2150 0    50   ~ 0
https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
Text GLabel 2500 3750 2    50   Input ~ 0
CE
Wire Wire Line
	2500 3750 2450 3750
Connection ~ 2450 3750
Wire Wire Line
	2450 3750 2450 3500
Text GLabel 1650 5000 0    50   Input ~ 0
CSN
Wire Wire Line
	1650 5000 1750 5000
Connection ~ 1750 5000
Wire Wire Line
	1750 5000 1750 5050
Text GLabel 6400 3200 2    50   Input ~ 0
DATA_TOP
Text GLabel 6400 3100 2    50   Input ~ 0
DATA_TOP_CLK
Wire Wire Line
	6200 3100 6400 3100
Wire Wire Line
	6200 3200 6400 3200
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 605FE1C2
P 6000 3200
F 0 "J2" H 5900 3450 50  0000 C CNN
F 1 "Conn_01x04_Female" V 6100 3150 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 6000 3200 50  0001 C CNN
F 3 "~" H 6000 3200 50  0001 C CNN
	1    6000 3200
	-1   0    0    1   
$EndComp
Text GLabel 3550 2550 2    50   Input ~ 0
MISO
Text GLabel 3550 2650 2    50   Input ~ 0
SCK
$EndSCHEMATC
