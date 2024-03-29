#include <xc.h>    

#include <stdint.h>
#include <stdbool.h>

#include "i2c_client.h"
#include "interrupts.h"
#include "GPIO_Macros.h"

static bool (*rxCallback)(uint8_t) = 0;
static uint8_t (*txCallback)(void) = 0;
static void (*stopCallback)(void) = 0;
static void (*errorCallback)(void) = 0;


//Initializes the I2C Module in Client Mode
//I/O is configured seperately
void I2C_initClient(uint8_t addr)
{
    I2C1CON0 = 0x00;
    I2C1CON0bits.MODE = 0b000;
    
    //Clear any pending flags
    I2C1CON1 = 0x00;
    
    //Enable STOP Interrupts
    I2C1PIE = 0x00;
    I2C1PIEbits.PC1IE = 1;
    
    //Enable Address Match Interrupts
//    I2C1PIEbits.ADRIE = 1;
    
    //Clock source is Fosc (64 MHz)
    I2C1CLK = 0b00001;
    
    //100kHz from 64 MHz
    I2C1BAUD = 159;
    
    I2C1CNTL = 0xFF;

//    I2C1TXB = 0x00;
    
    //Set Client Address
    I2C1ADR0 = (addr) << 1;
       
    //Enable Bus Timeout, NACK, and Bus Collision Interrupts
    I2C1ERR = 0x00;
    I2C1ERRbits.BTOIE = 1;
    I2C1ERRbits.NACK1IE = 1;
    I2C1ERRbits.BCLIE = 1;
    
    //Clear any Interrupt flags
    PIR7bits.I2C1IF = 0;
    PIR7bits.I2C1RXIF = 0;
    PIR7bits.I2C1TXIF = 0;
    PIR7bits.I2C1EIF = 0;
    
    //Enable Interrupts
    PIE7bits.I2C1IE = 1;
    PIE7bits.I2C1RXIE = 1;
    PIE7bits.I2C1TXIE = 1;
    PIE7bits.I2C1EIE = 1;
    
    //Enable I2C Module
    I2C1CON0bits.EN = 1;
}

//Initialize the bus timeout feature
void I2C_initBTO(bool reset, bool prescale, uint8_t timeout, I2C_BTO_Clock clock)
{
    I2C1BTO = (reset << 7) | (prescale << 6) | (0x3F & timeout);
    I2C1BTOC = clock;
}

//Write Interrupt
void __interrupt(irq(IRQ_I2C1TX)) I2C_writeISR(void)
{    
    if (txCallback != 0)
    {
        I2C1TXB = txCallback();
    }
    else
    {
        I2C1TXB = 0x00;
    }
    
    //Clear flag
    PIR7bits.I2C1TXIF = 0;
}

//Read Interrupt
void __interrupt(irq(IRQ_I2C1RX)) I2C_readISR(void)
{
    volatile uint8_t rx = I2C1RXB;
    
    if (rxCallback != 0)
    {
         bool temp = ~rxCallback(rx);
         I2C1CON1bits.ACKDT = temp;
    }

    
    //Clear flag
    PIR7bits.I2C1RXIF = 0;
}

//General I2C Interrupt Handler
void __interrupt(irq(IRQ_I2C1)) I2C_stopISR(void)
{
    if (I2C1PIRbits.PCIF)
    {
        //Stop Interrupt
        I2C1CNTL = 0xFF;
        
        //Return to ACK
        I2C1CON1bits.ACKDT = 0;
        
        //Clear the buffer to remove stale data from TXB
        I2C1STAT1bits.CLRBF = 1;
        
        if (stopCallback != 0)
        {
            stopCallback();
        }
        
        //Clear STOP Flag
        I2C1PIRbits.PCIF = 0;
    }
    
    //Clear General Flag
    PIR7bits.I2C1IF = 0;
}

//General I2C Interrupt Handler
void __interrupt(irq(IRQ_I2C1E)) I2C_errorISR(void)
{
    DEBUG0_SetHigh();
    
    if (errorCallback)
    {
        errorCallback();
    }
    
    //Clear buffers
    I2C1STAT1bits.CLRBF = 1;
    
    //Clear error flags
    I2C1ERRbits.NACK1IF = 0;
    I2C1ERRbits.BCLIF = 0;
    I2C1ERRbits.BTOIF = 0;
    
    //Clear Error Interrupt flag
    PIR7bits.I2C1EIF = 0;
}

//This function is called on an I2C Write from the Host
void I2C_assignByteWriteHandler(bool (*writeHandler)(uint8_t))
{
    rxCallback = writeHandler;
}

//This function is called when the host 
void I2C_assignByteReadHandler(uint8_t (*readHandler)(void))
{
    txCallback = readHandler;
}

//This function is called when an I2C Stop Event occurs
void I2C_assignStopHandler(void (*stopHandler)(void))
{
    stopCallback = stopHandler;
}

//This function is called when an I2C Error occurs
void I2C_assignErrorHandler(void (*errorHandler)(void))
{
    errorCallback = errorHandler;
}
