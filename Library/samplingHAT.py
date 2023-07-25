'''
This is a python library that controls the Evilia Boat Sampling Hat (Rev A).
License / Documentation is available at https://github.com/robperkel/evilia-boat-servo
'''

import smbus
import time
from enum import Enum


class SamplingHatA_Registers(object):
    STATUS = 0x00
    OUTPUT = 0x01
    SAMPLE  = 0x02

    #ADC Results
    ADC_H = 0x04
    ADC_L = 0x05

    #Pump / EXT_LED Timeouts
    PUMP_TIME = 0x06
    LED_TIME = 0x07

    #Reset MCU
    RESET = 0x0A

    #Duty Cycles
    DC1H = 0x10
    DC1L = 0x11
    DC2H = 0x12
    DC2L = 0x13
    DC3H = 0x14
    DC3L = 0x15
    DC4H = 0x16
    DC4L = 0x17
    DC5H = 0x18
    DC5L = 0x19
    DC6H = 0x1A
    DC6L = 0x1B

    #Frequency Control
    FRQ1H = 0x20
    FRQ1L = 0x21
    FRQ2H = 0x22
    FRQ2L = 0x23
    FRQ3H = 0x24
    FRQ3L = 0x25

    #Analog Configuration
    ANALOG_CONFIG = 0x30
    GAIN_CONFIG = 0x31
    DAC2_OUTPUT = 0x32


class SamplingHatA:
    def __init__(self, busID, addr):
        self.bus = smbus.SMBus(busID)
        self.addr = addr
        self.max = 1250
        self.min = 250

    def setMaxServoValue(self, max):
        self.max = max
    
    def setMinServoValue(self, min):
        self.min = min

    def readRegister(self, reg):
        resp = self.bus.read_i2c_block_data(self.addr, reg, 1)
        print(list(resp))

    def writeRegister(self, reg, data):
        self.bus.write_byte_data(self.addr, reg, data)

    def writeRegisters(self, reg, blockData):
        self.bus.write_i2c_block_data(self.addr, reg, blockData)

    def setPumpTimeout(self, timeout):
        self.writeRegister(SamplingHatA_Registers.PUMP_TIME, timeout)

    def setLEDTimeout(self, timeout):
        self.writeRegister(SamplingHatA_Registers.LED_TIME, timeout)

    def startPump(self):
        self.writeRegister(SamplingHatA_Registers.OUTPUT, 0xFF)

    def setServoPosition(self, index, value):
        regAddr = SamplingHatA_Registers.DC1H + ((index - 1) * 2)
        data = [0, 0]
        if (value > 255):
            value = value >> 8
            data[1] = 0xFF
        else:
            data[1] = value
            value = 0
        data[0] = value
        self.writeRegisters(regAddr, data)
    
    def openServo(self, index):
        self.setServoPosition(index, self.min)

    def closeServo(self, index):
        self.setServoPosition(index, self.max)

    def closeAllServos(self):
        self.setServoPosition(1, self.max)
        self.setServoPosition(2, self.max)
        self.setServoPosition(3, self.max)
        self.setServoPosition(4, self.max)
        self.setServoPosition(5, self.max)
        self.setServoPosition(6, self.max)


obj = SamplingHatA(1, 0x43)
obj.setMaxServoValue(900)
obj.setPumpTimeout(12)
obj.readRegister(SamplingHatA_Registers.PUMP_TIME)
obj.setPumpTimeout(5)
obj.setLEDTimeout(5)
#obj.startPump()

obj.closeAllServos()
