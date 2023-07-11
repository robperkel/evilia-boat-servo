#ifndef TESTS_H
#define	TESTS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Runs all self-tests
    void selfTest_runAll(void);
    
    //Sets the PWM to 10%/20%/30%/40%/50%/60%
    void selfTest_configurePWM(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TESTS_H */

