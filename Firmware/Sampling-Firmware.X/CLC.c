#include "CLC.h"

#include <xc.h>
#include <pic18f15q41.h>

static void (*risingEdgeISR)(void) = 0;
static void (*fallingEdgeISR)(void) = 0;

//Init the CLCs
void CLCs_init(void)
{
    //CLC1
    //Logic Function - Latch Input on Rising Edge of CLKREF
    {
        //Select CLC1
        CLCSELECT = 0;
        
        //Select 2-input D flip-flop reset
        CLCnCON = 0x00;
        CLCnCONbits.MODE = 0b101;
        
        //No inverting
        CLCnPOL = 0x00;
        
        //Select CLCIN0PPS
        CLCnSEL0 = 0b00000000;
        
        //Select CLKREF
        CLCnSEL2 = 0b00001101;
        
        //Input 3 (CLKREF) -> D CLK
        CLCnGLS0 = 0x00;
        CLCnGLS0bits.G1D3T = 1;
        
        //Input 1 (CLCIN) -> D Input
        CLCnGLS1 = 0x00;
        CLCnGLS1bits.G2D1T = 1;
        
        //No inputs for other gates
        CLCnGLS2 = 0x00;
        CLCnGLS3 = 0x00;
        
        CLCnCONbits.EN = 1;
    }
    
    //CLC2
    //Logic Function - Latch the following on the rising edge of CLKREF
    //Q = ~(~CLC1_OUT | ~CLCIN0PPS)
    {
        //Select CLC2
        CLCSELECT = 1;
        
        //Select 2-input D flip-flop reset
        //Enable Rising/Falling Interrupts
        CLCnCON = 0x00;
        CLCnCONbits.MODE = 0b101;
        CLCnCONbits.INTP = 1;
        CLCnCONbits.INTN = 1;
        
        //Invert Gate 2 
        //Q = (~CLC1_OUT | ~CLCIN0PPS)
        CLCnPOL = 0x00;
        CLCnPOLbits.G2POL = 1;
        
        //Select CLCIN0PPS
        CLCnSEL0 = 0b00000000;
        
        //Select CLC1
        CLCnSEL1 = 0b00100010;
        
        //Select CLKREF
        CLCnSEL2 = 0b00001101;
        
        //Gate 1
        //Input 3 (CLKREF) -> D CLK
        CLCnGLS0 = 0x00;
        CLCnGLS0bits.G1D3T = 1;
        
        //Gate 2 ~(~CLCIN | ~CLC1)
        //Input 1 (~CLCIN), Input 2 (~CLC1)
        CLCnGLS1 = 0x00;
        CLCnGLS1bits.G2D1N = 1;
        CLCnGLS1bits.G2D2N = 1;
        
        //No inputs for other gates
        CLCnGLS2 = 0x00;
        CLCnGLS3 = 0x00;
        
        CLCnCONbits.EN = 1;
    }
    
    //Clear Interrupt Flag
    PIR5bits.CLC2IF = 0;
    
    //Enable Interrupts
    PIE5bits.CLC2IE = 1;
}

//Returns the output of CLC2
bool CLC2_getOutputValue(void)
{
    return CLCDATAbits.CLC2OUT;
}

//Set the callback function for a rising edge
void CLC2_setRisingEdgeISR(void (*callback)(void))
{
    risingEdgeISR = callback;
}

//Set the callback function for a falling edge
void CLC2_setFallingEdgeISR(void (*callback)(void))
{
    fallingEdgeISR = callback;
}

void __interrupt(irq(IRQ_CLC2)) CLC_onEdge(void)
{
    if (CLC2_getOutputValue())
    {
        //Rising Edge
        if (risingEdgeISR)
        {
            risingEdgeISR();
        }
    }
    else
    {
        //Falling Edge
        if (fallingEdgeISR)
        {
            fallingEdgeISR();
        }

    }
    
    //Clear Flag
    PIR5bits.CLC2IF = 0;
}
