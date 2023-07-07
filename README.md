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
- [Register Map](#register-map)
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

- Block Diagrams: [Draw.io](https://app.diagrams.net/)
- Schematic and PCB Generation: [KiCad 7](https://www.kicad.org/)
- PCB Vendor: [OSH Park](https://oshpark.com/)
    - If ordering from a different vendor, I recommend choosing a surface finish such as ENIG to provide some corrosion resistance in the high humidity environment.

## Bill of Materials (BOM)

Order PCBs directly from the [OSH Park Project Page](https://oshpark.com/shared_projects/hY3GzXty)  
Digikey Shopping List: [https://www.digikey.com/en/mylists/list/YOLHZE0EBO](https://www.digikey.com/en/mylists/list/YOLHZE0EBO)   
- See `Control Board.xlsx` for the BOM
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
| Servo 1 | 10 (RB7)
| Servo 2 | 9 (RC7)
| Servo 3 | 8 (RC6)
| Servo 4 | 7 (RC3)
| Servo 5 | 6 (RC4)
| Servo 6 | 5 (RC5)
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

## Register Map

| Address | Register Name | Description
| ------- | ------------- | -----------
| 0x00    | STATUS | Status of the microcontroller
| 0x01    | OUTPUT | Sets the output register (overwrites current value)
| 0x02    | SAMPLE | Selects the input to sample 
| 0x03    | ADCH | ADC Measurement, High Byte
| 0x04    | ADCL | ADC Measurement, Low Byte
| 0x06    | PUMP_TIME | Sets the on time of the PUMP_EN
| 0x07    | LED_TIME  | Sets the on time of the EXT_LED
| 0x0A    | RESET | Resets the microcontroller and returns  all settings to defaults
| 0x10    | DC1H | Duty Cycle of PWM1, High Byte
| 0x11    | DC1L | Duty Cycle of PWM1, Low Byte
| 0x12    | DC2H | Duty Cycle of PWM2, High Byte
| 0x13    | DC2L | Duty Cycle of PWM2, Low Byte
| 0x14    | DC3H | Duty Cycle of PWM3, High Byte
| 0x15    | DC3L | Duty Cycle of PWM3, Low Byte
| 0x16    | DC4H | Duty Cycle of PWM4, High Byte
| 0x17    | DC4L | Duty Cycle of PWM4, Low Byte
| 0x18    | DC5H | Duty Cycle of PWM5, High Byte
| 0x19    | DC5L | Duty Cycle of PWM5, Low Byte
| 0x1A    | DC6H | Duty Cycle of PWM6, High Byte
| 0x1B    | DC6L | Duty Cycle of PWM6, Low Byte
| 0x20    | FRQ1H | Frequency of PWM1/2, High Byte
| 0x21    | FRQ1L | Frequency of PWM1/2, Low Byte
| 0x22    | FRQ2H | Frequency of PWM3/4, High Byte
| 0x23    | FRQ2L | Frequency of PWM3/4, Low Byte
| 0x24    | FRQ3H | Frequency of PWM5/6, High Byte
| 0x25    | FRQ3L | Frequency of PWM5/6, Low Byte
| 0x33    | Analog Configure 1 | Configures the ADC for Analog Input 1
| 0x34    | Gain Configure 1 | Sets the OPAMP gain for Analog Input 1
| 0x35    | Analog Configure 2 | Configures the ADC for Analog Input 2
| 0x36    | Gain Configure 2 | Sets the OPAMP gain for Analog Input 2

### Notes

1. Each PWM is used to control each servo. 
2. PWM is only updated on the low byte.
3. See "OUTPUT Register Mapping" for bitmapping of this byte.
4. Certain registers are kept at different offsets to reduce the chance of accidently modifying these values. 
5. PWM frequency is shared between paired outputs.

### STATUS Register Mapping

| Bit Position(s) | Function 
| ------------ | --------
| 7:3 | X
| 2 | EXT_LED State
| 1 | PUMP_EN State
| 0 | Sample Ready

Note: Bit 0 is cleared automatically when any part of the ADC value is read.

### OUTPUT Register Mapping

| Bit Position(s) | Function 
| ------------ | --------
| 7 | Pump
| 6:3 | X
| 2 | External LED
| 1 | Debug LED1
| 0 | Debug LED0

Note: "X" values are reserved.

### SAMPLE Register

| Value | Sampled Input 
| ----- | --------
| 0x00  | *Unused*
| 0x01  | Analog Input 1
| 0x02  | Analog Input 2

### PUMP_TIME Register

| Bit Position(s) | Function 
| ------------ | --------
| 7:0 | Maximum time (in seconds) for the pump to be on for

* If `PUMP_TIME` is set to 0, then there is no timeout for the pump. 
* Initializes to 120s on Power on Reset (PoR).

### LED_TIME Register

| Bit Position(s) | Function 
| ------------ | --------
| 7:0 | Maximum time (in seconds) for the external LED to be on for

* If `LED_TIME` is set to 0, then there is no timeout for the LED. 
* Initializes to 0 (disabled) on Power on Reset (PoR).  

### RESET Register

| Value | Function 
| ----- | --------
| 0x5A  | RESET the microcontroller

Note: All other values loaded into this register are ignored.

### Analog Configure Register Mapping

| Bit Position | Function 
| ------------ | --------
| 7:6 | Voltage Reference Select
| 5:4 | X
| 3:0 | Averaging Configuration

#### Bit Description

Voltage Reference Select
- 0b00 = VDD (5V)
- 0b01 = FVR 1.024V
- 0b10 = FVR 2.048V
- 0b11 = FVR 4.096V

FVR - Fixed Voltage Reference; Internal to the microcontroller. See datasheet for performance, accuracy, etc...

Averaging Configuration
- 0b0000 = 1 Sample (No Averaging)
- 0b0001 = 2 Samples
- 0b0010 = 4 Samples
- 0b0011 = 8 Samples
- 0b0100 = 16 Samples

Note: Undefined values will be treated as 0b0000 (1 sample).

### Gain Configure Register Mapping

| Bit Position | Function 
| ------------ | --------
| 7:3 | X
| 3:0 | Gain Configuration

Note: "X" values are reserved.

#### Bit Description

Gain Configuration
- 0b1xxx = 1 (Unity Gain)
- 0b0000 = 16/15
- 0b0001 = 8/7
- 0b0010 = 4/3
- 0b0011 = 2
- 0b0100 = 8/3
- 0b0101 = 4
- 0b0110 = 8
- 0b0111 = 16

For gain changes, some time is required for the output to stabilize. But, I<sup>2</sup>C is relatively slow, so there shouldn't be any timing issues with starting a conversion immediately following a gain change (assuming 100 kHz speed). 

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