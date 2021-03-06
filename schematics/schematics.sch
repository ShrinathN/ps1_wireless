EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L MCU_Microchip_ATmega:ATmega8A-PU U1
U 1 1 5E43A932
P 4450 3300
F 0 "U1" H 4950 5000 50  0000 C CNN
F 1 "ATmega8A-PU" H 5050 4800 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4450 3300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Microchip%208bit%20mcu%20AVR%20ATmega8A%20data%20sheet%2040001974A.pdf" H 4450 3300 50  0001 C CNN
	1    4450 3300
	1    0    0    -1  
$EndComp
Text Label 4550 4700 3    50   ~ 0
GND
Text Label 4450 4700 3    50   ~ 0
GND
$Comp
L Device:R R1
U 1 1 5E43E5CA
P 3850 2050
F 0 "R1" H 3600 2150 50  0000 L CNN
F 1 "220k" H 3600 2050 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3780 2050 50  0001 C CNN
F 3 "~" H 3850 2050 50  0001 C CNN
	1    3850 2050
	1    0    0    -1  
$EndComp
Text Label 3850 1900 1    50   ~ 0
BATTERY_IN
$Comp
L Connector:Conn_01x07_Female J2
U 1 1 5E43FDC9
P 7150 3700
F 0 "J2" H 7178 3726 50  0000 L CNN
F 1 "PSX_CONNECTOR" H 7178 3635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 7150 3700 50  0001 C CNN
F 3 "~" H 7150 3700 50  0001 C CNN
	1    7150 3700
	1    0    0    -1  
$EndComp
Text Label 6950 3400 2    50   ~ 0
PSX_DATA
Text Label 5050 3400 0    50   ~ 0
PSX_DATA
Text Label 6950 3500 2    50   ~ 0
PSX_ACK
Text Label 5050 3300 0    50   ~ 0
PSX_ACK
Text Label 6950 3600 2    50   ~ 0
PSX_CMD
Text Label 5050 3200 0    50   ~ 0
PSX_CMD
Text Label 6950 3700 2    50   ~ 0
PSX_CLK
Text Label 5050 3100 0    50   ~ 0
PSX_CLK
Text Label 6950 4000 2    50   ~ 0
PSX_ATT
Text Label 5050 3000 0    50   ~ 0
PSX_ATT
$Comp
L RF:NRF24L01_Breakout U3
U 1 1 5E443B20
P 8750 2700
F 0 "U3" H 9130 2746 50  0000 L CNN
F 1 "NRF24L01_BREAKOUT" H 9130 2655 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 8900 3300 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 8750 2600 50  0001 C CNN
	1    8750 2700
	1    0    0    -1  
$EndComp
Text Label 6950 3900 2    50   ~ 0
BATTERY_IN
Text Label 6950 3800 2    50   ~ 0
GND
Text Label 4450 1900 1    50   ~ 0
BATTERY_IN
Text Label 8750 3300 0    50   ~ 0
GND
Text Label 5050 2500 0    50   ~ 0
NRF_MOSI
Text Label 8250 2400 2    50   ~ 0
NRF_MOSI
Text Label 5050 2600 0    50   ~ 0
NRF_MISO
Text Label 8250 2500 2    50   ~ 0
NRF_MISO
Text Label 5050 2700 0    50   ~ 0
NRF_SCK
Text Label 8250 2600 2    50   ~ 0
NRF_SCK
Text Label 8250 2700 2    50   ~ 0
NRF_CS
Text Label 5050 2400 0    50   ~ 0
NRF_CS
Text Label 8250 2900 2    50   ~ 0
NRF_CE
Text Label 5050 2300 0    50   ~ 0
NRF_CE
Text Label 8250 3000 2    50   ~ 0
NRF_IRQ
Text Label 5050 3800 0    50   ~ 0
NRF_IRQ
$Comp
L Regulator_Linear:AMS1117-3.3 U2
U 1 1 5E44E284
P 8200 1000
F 0 "U2" H 8200 1242 50  0000 C CNN
F 1 "AMS1117-3.3" H 8200 1151 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8200 1200 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 8300 750 50  0001 C CNN
	1    8200 1000
	1    0    0    -1  
$EndComp
Text Label 7900 1000 3    50   ~ 0
BATTERY_IN
Text Label 8400 1850 3    50   ~ 0
GND
Text Label 8500 1000 0    50   ~ 0
3V3
Text Label 8750 2100 0    50   ~ 0
3V3
Text Label 4550 1900 1    50   ~ 0
BATTERY_IN
Text Label 3850 2200 2    50   ~ 0
AVR_RST
Text Label 8200 1300 3    50   ~ 0
GND
Text Label 5050 3600 0    50   ~ 0
AVR_RX
Text Label 5050 3700 0    50   ~ 0
AVR_TX
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5E43D109
P 5850 4300
F 0 "J1" H 5930 4292 50  0000 L CNN
F 1 "POWER" H 5930 4201 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 5850 4300 50  0001 C CNN
F 3 "~" H 5850 4300 50  0001 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp
Text Label 5650 4400 3    50   ~ 0
GND
Text Label 5650 4300 2    50   ~ 0
BATTERY_IN
$EndSCHEMATC
