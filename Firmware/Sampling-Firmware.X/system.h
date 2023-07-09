#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Initializes all HW Peripherals
    //DOES NOT INIT SW FEATURES
    void System_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

