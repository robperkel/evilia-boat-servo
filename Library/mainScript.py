#Main Script for the boat

import board
import busio
import adafruit_mcp9600
import time
import digitalio
import gpsd
import datetime
import os
import fcntl
from samplingHAT import SamplingHatA, SamplingHatA_Registers

class SaltyFlamingo:
    def __init__(self):
        self.logFilePath = '/home/evilia/boat.log'

        self.ledScript  = digitalio.DigitalInOut(board.D22)
        self.ledScript.direction = digitalio.Direction.OUTPUT
        self.ledScript.value = False

        self.rcGood = digitalio.DigitalInOut(board.D17)
        self.rcGood.direction = digitalio.Direction.INPUT

        self.rcOut = digitalio.DigitalInOut(board.D18)
        self.rcOut.direction = digitalio.Direction.INPUT

        if (self.rcGood):
            self.lastSwitchState = self.rcOut.value
        else:
            self.lastSwitchState = False

        self.sampleState = False
        self.sampleCount = 0

        try:
            self.i2c = busio.I2C(board.SCL, board.SDA, frequency=100000)
            self.mcp = adafruit_mcp9600.MCP9600(self.i2c)
            self.sampleHAT = SamplingHatA(1, 0x43)
            self.sampleHAT.setMaxServoValue(1025) #Max Servo Position
            self.sampleHAT.setPumpTimeout(60) #Max time in seconds to run pump for
            self.sampleHAT.setLEDTimeout(60)
            self.sampleHAT.closeAllServos()
        except:
            while (True):
                #If something went wrong, blink
                self.ledScript.value = True
                time.sleep(1)
                self.ledScript.value = False
                time.sleep(1)

        self.logStartup()

        #If no issues in init, turn on DBG0
        self.sampleHAT.turnOn_DBG0()

    def isTriggerActive(self): 
        if not (self.rcGood):
            return False

        #Retrigger on rising/falling edge
        if (not self.lastSwitchState) and (self.rcOut.value):
            self.lastSwitchState = True
            return True
        elif (self.lastSwitchState) and (not self.rcOut.value):
            self.lastSwitchState = False
            return True
        
        return False
    
    def startSampling(self):
        #In the middle of sampling - ignore input
        if (self.sampleState):
            return

        #Check to see if we are done collecting
        if (self.sampleCount < 4):
            self.sampleHAT.turnOn_EXT_LED()
            self.sampleHAT.openServo(self.sampleCount + 1)
            self.sampleHAT.setServoPosition(5, 750)
            time.sleep(3)
            self.logStartOfSampling()
            self.sampleHAT.startPump()
            self.sampleState = True
            self.sampleCount += 1
            
    
    def isSampling(self):
        return self.sampleState

    def samplingStateMachine(self):
        if (self.sampleState) and (not self.sampleHAT.getPumpState()):
            self.sampleHAT.closeAllServos()
            self.logEndOfSampling()
            self.sampleState = False
    
    def isPumpOn(self):
        return True
            
    def logStartup(self):
        lat = '???'
        long = '???'
        alt = '???'

        try:
            #Get the last GPS data
            packet = gpsd.get_current()

            #Get Parameters
            lat = str(packet.lat)
            long = str(packet.lon)

            #If we have a 3D fix, get Altitude
            if (packet.mode >= 3):
                alt = str(packet.alt)
        except:
            pass

        flags = 'a'
        if not (os.path.isfile(self.logFilePath)):
            flags = 'w'

        with open(self.logFilePath, flags) as logFile:
            logFile.write(f'{str(datetime.datetime.now())}: Boat started up at {lat}, {long}, {alt}m.\n')
            logFile.flush()
            os.fsync(logFile.fileno())


    def logStartOfSampling(self):
        lat = '???'
        long = '???'
        alt = '???'

        try:
            #Get the last GPS data
            packet = gpsd.get_current()

            #Get Parameters
            lat = str(packet.lat)
            long = str(packet.lon)

            #If we have a 3D fix, get Altitude
            if (packet.mode >= 3):
                alt = str(packet.alt)
        except:
            pass

        flags = 'a'
        if not (os.path.isfile(self.logFilePath)):
            flags = 'w'

        with open(self.logFilePath, flags) as logFile:
            logFile.write(f'{str(datetime.datetime.now())}: Collecting Sample #{self.sampleCount + 1} at {lat}, {long}, {alt}m. Water Temperature: {str(self.getWaterTemperature())}C\n')
            logFile.flush()
            os.fsync(logFile.fileno())

    def logEndOfSampling(self):
        lat = '???'
        long = '???'
        alt = '???'
        gpsOK = False

        try:
            #Get the last GPS data
            packet = gpsd.get_current()

            #Get Parameters
            lat = str(packet.lat)
            long = str(packet.lon)

            #If we have a 3D fix, get Altitude
            if (packet.mode >= 3):
                alt = str(packet.alt)
        except:
            pass

        flags = 'a'
        if not (os.path.isfile(self.logFilePath)):
            flags = 'w'

        with open(self.logFilePath, flags) as logFile:
            logFile.write(f'{str(datetime.datetime.now())}: Finished Collecting Sample at {lat}, {long}, {alt}m. Water Temperature: {str(self.getWaterTemperature())}C\n')
            logFile.flush()
            os.fsync(logFile.fileno())


    def getWaterTemperature(self):
        return self.mcp.temperature

def logGPSData(boat):
    gpsFilePath = '/home/evilia/gps.log'
    lat = '???'
    long = '???'
    alt = '???'
    vel = '???'

    try:
        #Get the last GPS data
        packet = gpsd.get_current()

        #Get Parameters
        lat = str(packet.lat)
        long = str(packet.lon)
        vel = str(packet.hspeed)

        #If we have a 3D fix, get Altitude
        if (packet.mode >= 3):
            alt = str(packet.alt)
    except:
        pass

    flags = 'a'
    if not (os.path.isfile(gpsFilePath)):
        flags = 'w'

    with open(gpsFilePath, flags) as gpsFile:
        if (flags == 'w'):
            gpsFile.write('Time, Latitude, Longitude, Altitude (m), Ground Speed (m/s), Water Temperature (C)\n')

        gpsFile.write(f'{str(datetime.datetime.now())},{lat},{long},{alt},{vel},{str(boat.getWaterTemperature())}\n')
        gpsFile.flush()
        os.fsync(gpsFile.fileno())

def mainLoop():

    #Prevent multiple versions of the script from running at once!
    #Modified from https://stackoverflow.com/questions/380870/make-sure-only-a-single-instance-of-a-program-is-running
    fPath = '/home/evilia/scriptTemp.lock'
    lockFile = os.open(fPath, os.O_WRONLY | os.O_CREAT)

    try:
        fcntl.lockf(lockFile, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except:
        print('Error: Script is already running!')
        exit()

    #Get a connection to the GPS
    gpsd.connect()

    #Init the Boat Systems
    boat = SaltyFlamingo()
    gpsCounter = 0

    while (True):
        if boat.isTriggerActive():
            boat.startSampling()

        boat.samplingStateMachine()

        #Every 30s, log GPS data
        if (gpsCounter == 30):
            logGPSData(boat)
            gpsCounter = 1
        else:
            gpsCounter += 1

        time.sleep(1)

#Run main loop
mainLoop()