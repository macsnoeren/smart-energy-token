EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ELC - Team RED Token Infrastructure"
Date "2021-04-09"
Rev "2.1"
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
Text GLabel 3300 5350 2    50   Input ~ 0
UPDI
Text GLabel 3300 5450 2    50   Input ~ 0
MOSI
Text GLabel 3300 5550 2    50   Input ~ 0
MISO
Text GLabel 3300 5650 2    50   Input ~ 0
SCK
Text GLabel 2500 4250 0    50   Input ~ 0
DATA_BOTTOM
Text GLabel 3300 5750 2    50   Input ~ 0
DATA_TOP_CLK
Text GLabel 2500 4150 0    50   Input ~ 0
DATA_BOTTOM_CLK
Text GLabel 3300 5850 2    50   Input ~ 0
DATA_TOP
$Comp
L Device:R_Small R2
U 1 1 605C3635
P 3200 5050
F 0 "R2" H 3100 5100 50  0000 C CNN
F 1 "500k" H 3050 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 3200 5050 50  0001 C CNN
F 3 "~" H 3200 5050 50  0001 C CNN
	1    3200 5050
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 605C63C4
P 2450 4900
F 0 "#PWR01" H 2450 4750 50  0001 C CNN
F 1 "+3.3V" H 2465 5073 50  0000 C CNN
F 2 "" H 2450 4900 50  0001 C CNN
F 3 "" H 2450 4900 50  0001 C CNN
	1    2450 4900
	1    0    0    -1  
$EndComp
Text Notes 3100 4700 0    50   ~ 0
Pull-up resister for low current\nand detection top token pulled off.
Text Notes 1750 4050 0    50   ~ 0
Building uses MOSI, MISO and SCK for RF.
Text Notes 1750 3950 0    50   ~ 0
Token uses MOSI and SCK to communicatie to bottom (building or token).
$Comp
L Device:R_Small R1
U 1 1 605D300C
P 4200 6050
F 0 "R1" V 4004 6050 50  0000 C CNN
F 1 "220" V 4095 6050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4200 6050 50  0001 C CNN
F 3 "~" H 4200 6050 50  0001 C CNN
	1    4200 6050
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 605D332F
P 3900 6050
F 0 "D1" H 3893 5795 50  0000 C CNN
F 1 "LED" H 3893 5886 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric_Pad1.22x1.90mm_HandSolder" H 3900 6050 50  0001 C CNN
F 3 "~" H 3900 6050 50  0001 C CNN
	1    3900 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 6050 4100 6050
Text Notes 2000 2150 0    50   ~ 0
https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
Text GLabel 1700 5650 0    50   Input ~ 0
CE
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
Text GLabel 1700 5550 0    50   Input ~ 0
CSN
$Comp
L power:GND #PWR02
U 1 1 60706721
P 2450 6600
F 0 "#PWR02" H 2450 6350 50  0001 C CNN
F 1 "GND" H 2455 6427 50  0000 C CNN
F 2 "" H 2450 6600 50  0001 C CNN
F 3 "" H 2450 6600 50  0001 C CNN
	1    2450 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5050 2450 4900
Connection ~ 2450 4900
Wire Wire Line
	3050 5450 3300 5450
Wire Wire Line
	3050 5550 3300 5550
Wire Wire Line
	3050 5650 3300 5650
Wire Wire Line
	4300 4900 3200 4900
Wire Notes Line
	3250 4750 3100 4750
Wire Notes Line
	3100 4750 3100 5100
Wire Wire Line
	2450 6450 2450 6600
Text GLabel 2600 4150 2    50   Input ~ 0
SCK
Text GLabel 2600 4250 2    50   Input ~ 0
MOSI
Wire Wire Line
	2500 4150 2600 4150
Wire Wire Line
	2600 4250 2500 4250
Wire Wire Line
	4300 4900 4300 6050
Wire Wire Line
	3750 6050 3050 6050
Text GLabel 1700 5450 0    50   Input ~ 0
IRQ
Wire Wire Line
	3200 4950 3200 4900
Connection ~ 3200 4900
Wire Wire Line
	3200 4900 2450 4900
Wire Wire Line
	3200 5150 3200 5850
Wire Wire Line
	3200 5850 3050 5850
Wire Wire Line
	3300 5750 3050 5750
Wire Wire Line
	3300 5850 3200 5850
Connection ~ 3200 5850
Wire Wire Line
	1700 5450 1850 5450
Wire Wire Line
	1700 5650 1850 5650
NoConn ~ 1850 5350
NoConn ~ 3050 5950
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 60740CD7
P 6050 4200
F 0 "J1" H 6158 4381 50  0000 C CNN
F 1 "Conn_01x02_Male" H 6158 4290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6050 4200 50  0001 C CNN
F 3 "~" H 6050 4200 50  0001 C CNN
	1    6050 4200
	1    0    0    -1  
$EndComp
Text Notes 5850 4450 1    50   ~ 0
Programming
Wire Wire Line
	3050 5350 3300 5350
$Comp
L MCU_Microchip_ATtiny:ATtiny1604-SS U1
U 1 1 60700A84
P 2450 5750
F 0 "U1" H 2150 6450 50  0000 C CNN
F 1 "ATtiny1604-SS" H 2800 6450 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2450 5750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny804_1604-Data-Sheet-40002028A.pdf" H 2450 5750 50  0001 C CNN
	1    2450 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 5550 1700 5550
Text GLabel 6350 4200 2    50   Input ~ 0
UPDI
$Comp
L power:GND #PWR03
U 1 1 607420F5
P 6350 4300
F 0 "#PWR03" H 6350 4050 50  0001 C CNN
F 1 "GND" H 6355 4127 50  0000 C CNN
F 2 "" H 6350 4300 50  0001 C CNN
F 3 "" H 6350 4300 50  0001 C CNN
	1    6350 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4300 6250 4300
Wire Wire Line
	6250 4200 6350 4200
$EndSCHEMATC
