#ifndef NCO_H
#define	NCO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Init the NCO Peripheral
    void NCO_init(void);
    
    //Set the callback for the NCO
    void NCO_setCallback(void (*callback)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* NCO_H */

