#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
    
#define SERVO1_DC PWM1S1P1
#define SERVO1_DC_H PWM1S1P1H
#define SERVO1_DC_L PWM1S1P1L
    
#define SERVO2_DC PWM1S1P2
#define SERVO2_DC_H PWM1S1P2H
#define SERVO2_DC_L PWM1S1P2L
    
#define SERVO3_DC PWM2S1P1
#define SERVO3_DC_H PWM2S1P1H
#define SERVO3_DC_L PWM2S1P1L
    
#define SERVO4_DC PWM2S1P2
#define SERVO4_DC_H PWM2S1P2H
#define SERVO4_DC_L PWM2S1P2L
    
#define SERVO5_DC PWM3S1P1
#define SERVO5_DC_H PWM3S1P1H
#define SERVO5_DC_L PWM3S1P1L
    
#define SERVO6_DC PWM3S1P2
#define SERVO6_DC_H PWM3S1P2H
#define SERVO6_DC_L PWM3S1P2L

    
    //Initializes all PWM Instances
    void PWM_init(void);
    
    //Loads new PWM values - PWM instances are changed simutanously
    //Must be called after PWMx_setPeriod
    void PWM_loadNewPeriods(void);
    
    //Sets the period of PWM outputs
    void PWM1_setPeriod(uint16_t val);
    void PWM2_setPeriod(uint16_t val);
    void PWM3_setPeriod(uint16_t val);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

