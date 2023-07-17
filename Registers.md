# Software Registers

This file contains the software-defined registers, bitfields and allowed values.

## Register Map

| Address | Register Name | Description
| ------- | ------------- | -----------
| 0x00    | [STATUS](#status-register-mapping) | Status of the microcontroller
| 0x01    | [OUTPUT](#output-register-mapping) | Sets the output register (overwrites current value)
| 0x02    | [SAMPLE](#sample-register) | Selects the input to sample 
| 0x04    | [ADCH](#adchadcl-register) | ADC Measurement, High Byte
| 0x05    | [ADCL](#adchadcl-register) | ADC Measurement, Low Byte
| 0x06    | [PUMP_TIME](#pump_time-register) | Sets the on time of the PUMP_EN
| 0x07    | [LED_TIME](#led_time-register)  | Sets the on time of the EXT_LED
| 0x0A    | [RESET](#reset-register) | Resets the microcontroller and returns  all settings to defaults
| 0x10    | [DC1H](#dcxhdcxl-registers) | Duty Cycle of PWM1, High Byte
| 0x11    | [DC1L](#dcxhdcxl-registers) | Duty Cycle of PWM1, Low Byte
| 0x12    | [DC2H](#dcxhdcxl-registers) | Duty Cycle of PWM2, High Byte
| 0x13    | [DC2L](#dcxhdcxl-registers) | Duty Cycle of PWM2, Low Byte
| 0x14    | [DC3H](#dcxhdcxl-registers) | Duty Cycle of PWM3, High Byte
| 0x15    | [DC3L](#dcxhdcxl-registers) | Duty Cycle of PWM3, Low Byte
| 0x16    | [DC4H](#dcxhdcxl-registers) | Duty Cycle of PWM4, High Byte
| 0x17    | [DC4L](#dcxhdcxl-registers) | Duty Cycle of PWM4, Low Byte
| 0x18    | [DC5H](#dcxhdcxl-registers) | Duty Cycle of PWM5, High Byte
| 0x19    | [DC5L](#dcxhdcxl-registers) | Duty Cycle of PWM5, Low Byte
| 0x1A    | [DC6H](#dcxhdcxl-registers) | Duty Cycle of PWM6, High Byte
| 0x1B    | [DC6L](#dcxhdcxl-registers) | Duty Cycle of PWM6, Low Byte
| 0x20    | [FRQ1H](#frqxhfrqxl-registers) | Frequency of PWM1/2, High Byte
| 0x21    | [FRQ1L](#frqxhfrqxl-registers) | Frequency of PWM1/2, Low Byte
| 0x22    | [FRQ2H](#frqxhfrqxl-registers) | Frequency of PWM3/4, High Byte
| 0x23    | [FRQ2L](#frqxhfrqxl-registers) | Frequency of PWM3/4, Low Byte
| 0x24    | [FRQ3H](#frqxhfrqxl-registers) | Frequency of PWM5/6, High Byte
| 0x25    | [FRQ3L](#frqxhfrqxl-registers) | Frequency of PWM5/6, Low Byte
| 0x30    | [Analog Configure](#analog-configure-register) | Configures the ADC for Analog Input 1
| 0x31    | [Gain Configure](#gain-configure-register) | Sets the OPAMP gain for Analog Input 1
| 0x50    | Firmware Update | Begins a firmware update operation
| 0x51    | Firmware Unlock 1 | See note 6
| 0x52    | Firmware Unlock 2 | See note 6
| 0x60    | Firmware Version ID | Firmware version identifier


### Notes

1. Each PWM is used to control each servo. 
2. PWM frequency and duty cycle is only updated on the low byte.
3. See "OUTPUT Register Mapping" for bitmapping of this byte.
4. Certain registers are kept at different offsets to reduce the chance of accidently modifying these values. 
5. PWM frequency is shared between paired outputs.
6. `Firmware Unlock 1` and `Firmware Unlock 2` are only accessible from a sequential write on `Firmware Update`. Other access attempts will be rejected.

**Note: Firmware update and version ID are currently not implemented.**

### STATUS Register Mapping

| Bit Position(s) | Function 
| ------------ | --------
| 7 | Pump State
| 6:3 | X
| 2 | EXT_LED State
| 1 | Error
| 0 | Sample Ready

### Notes
1. Sample Ready is cleared automatically when any part of the ADC value is read.  
2. The Error bit is set when an illegal command or operation occurs; Automatically cleared on read.
3. Pump/EXT_LED/PUMP_EN are clones of the `OUTPUT` register values.

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

### ADCH/ADCL Register

This value (up-to 16-bits) is the last conversion result from the ADC. Natively, the ADC is 12 bits. But, oversampling can be used for more resolution.

The ADCH value is the high byte, while the ADCL value is the low byte.

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

### DCxH/DCxL Registers

This register holds the 16-bit value used by the PWM hardware to set the duty cycle. The DCxH value is the high byte, while the DCxL value is the low byte.

### FRQxH/FRQxL Registers

This register holds the 16-bit value used by the PWM hardware to set the period (frequency) of the waveform. The FRQxH value is the high byte, while the FRQxL value is the low byte.

### Analog Configure Register

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

### Gain Configure Register

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
