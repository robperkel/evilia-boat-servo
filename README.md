# Dr. Evilia's Boat Control HAT
This custom HAT is used to better implement control of the servos and motors used on her sampling boat. We found there wasn't a good "off-the-shelf" board available that fit the desired specifications. This project is designed around a small, 8-bit microcontroller that provides a far more intelligent and flexible design interface. 

This repository contains the documentation, hardware files, and firmware used for this project. The boat runs on a Raspberry Pi 4, Model B.  

## Base Software

This bare metal I<sup>2</sup>C driver was used as a code base: https://github.com/microchip-pic-avr-examples/pic18f56q71-bare-metal-i2c-mplab 

**Per the license agreement in this code, this code can ONLY be used with Microchip products.**

## Design Objectives

1. Support 6x 3-pin servo motors
2. ON/OFF control of a large pump
3. LED outputs for various indicators
4. I<sup>2</sup>C Interface

## Electrical Requirements

1. 3.3V logic interface
2. 12V, 500mA motor control (ON/OFF)

### Pinout

| Function | Pin Number | I/O Pin
| -------- | ---------- | --------
| Servo 1 | 
| Servo 2 |
| Servo 3 |
| Servo 4 |
| Servo 5 |
| Servo 6 |
| Motor | 
| LED0 |
| LED1 |
| LED2 |
| LED3 |
| ICSPDAT |
| ICSPCLK |
| MCLR | 

### "Output" Register Mapping

| Bit Position | Function 
| ------------ | --------
| 7 | Motor
| 6 | X
| 5 | X
| 4 | LED4
| 3 | LED3
| 2 | LED2
| 1 | LED1
| 0 | LED0

Note: "X" values are unused.

## I<sup>2</sup>C Communication

### I<sup>2</sup>C Parameters

- Frequency: 100 kHz  
- 7-bit Address: TBD

### Structure

I<sup>2</sup>C communication uses the following structure:

I<sup>2</sup>C ADDR &rarr; Reg. ADDR &rarr; Data 0 &rarr; Data 1 &rarr; ... &rarr; Data N

The "register address" (Reg. ADDR) selects which setting to change. After this, each successive byte is loaded in sequential order. The register address is incremented after each byte.

### Register Map

| Address | Register Name | Description
| ------- | ------------- | -----------
| 0x00    | DC1H | Duty Cycle of PWM1, High Byte
| 0x01    | DC1L | Duty Cycle of PWM1, Low Byte
| 0x02    | DC2H | Duty Cycle of PWM2, High Byte
| 0x03    | DC2L | Duty Cycle of PWM2, Low Byte
| 0x04    | DC3H | Duty Cycle of PWM3, High Byte
| 0x05    | DC3L | Duty Cycle of PWM3, Low Byte
| 0x06    | DC4H | Duty Cycle of PWM4, High Byte
| 0x07    | DC4L | Duty Cycle of PWM4, Low Byte
| 0x08    | DC5H | Duty Cycle of PWM5, High Byte
| 0x09    | DC5L | Duty Cycle of PWM5, Low Byte
| 0x0A    | DC6H | Duty Cycle of PWM6, High Byte
| 0x0B    | DC6L | Duty Cycle of PWM6, Low Byte
| 0x0C    | Output | Sets the output register (overwrites current value)
| 0x10    | Output Set | Sets the output bits (does NOT clear)
| 0x12    | Output Clear | Clears the output bits (does NOT set)
| 0x14    | Output Toggle | Toggles the output bits (does NOT clear)
| 0x20    | FRQ1H | Frequency of PWM1/2, High Byte
| 0x21    | FRQ1L | Frequency of PWM1/2, Low Byte
| 0x22    | FRQ2H | Frequency of PWM3/4, High Byte
| 0x23    | FRQ2L | Frequency of PWM3/4, Low Byte
| 0x24    | FRQ3H | Frequency of PWM5/6, High Byte
| 0x25    | FRQ3L | Frequency of PWM5/6, Low Byte

#### Notes

1. Each PWM is used to control each servo. 
2. PWM is only updated on the low byte.
3. See "OUTPUT Register Mapping" for bitmapping of this byte.
4. The PWM frequencies are kept at a different offset to reduce the chance of accidently modifying these values. 

## Usage from Raspberry Pi

To ease integration in the system, a custom Python library was developed to simplify setup. 