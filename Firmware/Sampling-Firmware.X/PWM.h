#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
    
#define SERVO1_INDEX 1
#define SERVO1_DC PWM1S1P1
#define SERVO1_DC_H PWM1S1P1H
#define SERVO1_DC_L PWM1S1P1L
    
#define SERVO2_INDEX 2
#define SERVO2_DC PWM1S1P2
#define SERVO2_DC_H PWM1S1P2H
#define SERVO2_DC_L PWM1S1P2L
    
#define SERVO3_INDEX 3
#define SERVO3_DC PWM2S1P1
#define SERVO3_DC_H PWM2S1P1H
#define SERVO3_DC_L PWM2S1P1L
    
#define SERVO4_INDEX 4
#define SERVO4_DC PWM2S1P2
#define SERVO4_DC_H PWM2S1P2H
#define SERVO4_DC_L PWM2S1P2L
    
#define SERVO5_INDEX 5
#define SERVO5_DC PWM3S1P1
#define SERVO5_DC_H PWM3S1P1H
#define SERVO5_DC_L PWM3S1P1L
    
#define SERVO6_INDEX 6
#define SERVO6_DC PWM3S1P2
#define SERVO6_DC_H PWM3S1P2H
#define SERVO6_DC_L PWM3S1P2L

#define PWM_DEFAULT_FRQ_VALUE 620
#define PWM_DEFAULT_DC_VALUE 31
    
    //Initializes all PWM Instances
    void PWM_init(void);
    
    //Loads new PWM values - PWM instances are changed simutanously
    //Must be called after PWMx_setPeriod
    void PWM_loadNewParameters(void);
    
    //Sets the duty cycle of a specific PWM
    void PWM_setDutyCycle(uint16_t dc, uint8_t servo);
    
    //Gets the duty cycle (H and L) of a specific PWM
    uint8_t PWM_getDC_H(uint8_t servo); 
    uint8_t PWM_getDC_L(uint8_t servo);
    
    //Sets the period of PWM outputs
    void PWM1_setPeriod(uint16_t val);
    void PWM2_setPeriod(uint16_t val);
    void PWM3_setPeriod(uint16_t val);
    
    //Gets the frequency of PWM outputs
    uint8_t PWM1_getFrequency_H(void);
    uint8_t PWM1_getFrequency_L(void);
    
    uint8_t PWM2_getFrequency_H(void);
    uint8_t PWM2_getFrequency_L(void);
    
    uint8_t PWM3_getFrequency_H(void);
    uint8_t PWM3_getFrequency_L(void);

        
#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

