#ifndef DAC_H
#define	DAC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Init DAC2
    void DAC2_init(void);
    
    //Set the output of DAC2
    void DAC2_setValue(uint8_t val);
    
    //Get the value of DAC2
    uint8_t DAC2_getValue(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DAC_H */

