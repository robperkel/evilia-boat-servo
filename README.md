# Dr. Evilia's Boat Sampling HAT
This custom HAT is used to better implement control of the servos and motors used on her sampling boat. We found there wasn't a good "off-the-shelf" board available that fit the desired specifications. This project is designed around a small, 8-bit microcontroller that provides a far more intelligent and flexible design interface. 

This repository contains the documentation, hardware files, and firmware used for this project. The boat runs on a Raspberry Pi 4, Model B.  

## Table of Contents

- [Base Software](#base-software)
- [Tools Needed](#tools-needed)
    - [Other Tools Used](#other-tools-used)
- [Bill of Materials (BOM)](#bill-of-materials-bom)
- [Design Objectives](#design-objectives)
- [Microcontroller Pinout](#microcontroller-pinout)
- [Software Registers](#software-registers)
- [Digital Control](#digital-control)
- [Analog Control](#analog-control)
- [Usage from Raspberry Pi](#usage-from-raspberry-pi)

## Base Software

This bare metal I<sup>2</sup>C driver was used as a code base: https://github.com/microchip-pic-avr-examples/pic18f56q71-bare-metal-i2c-mplab 

**Per the license agreement in this code, the firmware (specifically the I<sup>2</sup>C driver) can ONLY be used with Microchip microcontrollers.** This is not an issue as the physical board is not compatiable with other microcontrollers.

## Tools Needed

- Programming / Development IDE: [MPLAB&reg; X IDE v6.10](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- Compiler: [MPLAB XC8 v2.41](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/downloads-documentation#XC8)  
- Programmer: [MPLAB SNAP](https://www.microchip.com/en-us/development-tool/PG164100) or [PICKIT&trade; 4](https://www.microchip.com/en-us/development-tool/PG164140)

### Other Tools Used

- I<sup>2</sup>C Tester (for development): [MCP2221A Breakout Module (ADM00559)](https://www.microchip.com/en-us/development-tool/ADM00559)
- Block Diagrams: [Draw.io](https://app.diagrams.net/)
- Schematic and PCB Generation: [KiCad 7](https://www.kicad.org/)
- PCB Vendor: [OSH Park](https://oshpark.com/)
    - If ordering from a different vendor, I recommend choosing a surface finish such as ENIG to provide some corrosion resistance in the high humidity environment.
    - Conformally coating the board is also recommended.

## Bill of Materials (BOM)

Order PCBs directly from the [OSH Park Project Page](https://oshpark.com/shared_projects/qA2tLGmg)  
Digikey Shopping List: [https://www.digikey.com/en/mylists/list/YOLHZE0EBO](https://www.digikey.com/en/mylists/list/YOLHZE0EBO)   
- See [Control Board.xlsx](./Control%20Board/Control%20Board.xlsx) for the BOM
    - Red, struck-through items are not in the BOM
- Includes 0 ohm jumpers for I<sup>2</sup>C Address Setting
- Motor drive parts for `EXT_LED1` are not included
- Optional off-board connectors are not in the list

**Important: Shopping list does NOT include a programmer. Programmers can obtained from Digikey (or other electronics vendor).**

## Design Objectives

1. Support 6x 3-pin servo motors
2. ON/OFF control of a large pump
3. LED outputs for various indicators
4. I<sup>2</sup>C Interface
5. 3.3V logic interface with Raspberry Pi
6. 5V, 500mA motor control (ON/OFF)
7. 50 Hz Servo Frequency

## Microcontroller Pinout

Microcontroller: PIC18F1xQ41
(PIC18F14Q41 / PIC18F15Q41 / PIC18F16Q41)

| Function | Pin (PORT / PIN)
| -------- | ----------
| VDD (5V) | 1
| VSS (GND) | 20
| nMCLR | 4
| SDA | 2 (RA5)
| SCL | 3 (RA4)
| ADDR0 | 16 (RC0)
| ADDR1 | 13 (RB4)
| Servo 6 | 10 (RB7)
| Servo 5 | 9 (RC7)
| Servo 4 | 8 (RC6)
| Servo 3 | 7 (RC3)
| Servo 2 | 6 (RC4)
| Servo 1 | 5 (RC5)
| EXT_LED | 11 (RB6)
| PUMP_EN | 15 (RC1)
| AN1 | 17 (RA2)
| AN2 | 12 (RB5)
| DEBUG 0 | 19 (RA0 / ICSPDAT)
| DEBUG 1 | 18 (RA1 / ICSPCLK)
| OPAMP_OUT (reserved) | 14 (RC2)

### Notes
1. nMCLR is not available as an I/O in this configuration.
2. DEBUG 0/1 are LED outputs on the board. Unavailable during debugging.
3. EXT_LED can be converted to a 2nd motor/pump enable.
4. OPAMP_OUT is reserved due to internal OPAMP peripheral requirements.  

## Software Registers

**Please see [Registers.md](./Registers.md) for more information**

## Digital Control

### I<sup>2</sup>C Parameters

- Frequency: 100 kHz  
- 7-bit Address: TBD

### I<sup>2</sup>C Communication

### Writing To

The "register address" (Reg. ADDR) selects which setting to change. After this, each data byte is loaded into the next sequential register. 

(Start) &rarr; I<sup>2</sup>C ADDR (W) &rarr; Reg. ADDR &rarr; Data 0 &rarr; Data 1 &rarr; ... &rarr; Data N &rarr; (Stop)

### Reading From

To read from the device, address the microcontroller (write) and send the starting register address. Then, restart communication and address the microcontroller (read). Each byte is read in order from the registers.

(Start) &rarr; I<sup>2</sup>C ADDR (W) &rarr; Reg. ADDR &rarr; (Restart) &rarr; I<sup>2</sup>C ADDR (R) &rarr; Data 0 &rarr; Data 1 &rarr; ... &rarr; Data N &rarr; (Stop)

### Power on Restart (PoR) Behavior

On PoR, the microcontroller sets all duty cycles to 0%, PWM frequencies to 50 Hz, and turns off the LEDs and motor. 

## Analog Control



## Usage from Raspberry Pi

To ease integration in the system, a custom Python library was developed to simplify setup. 