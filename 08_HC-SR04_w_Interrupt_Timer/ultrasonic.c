#include "ultrasonic.h"

void setupHC_SR04()
{
    // set pin mode
    SETBIT(ULTRASONIC_TRIGGER_DDR, ULTRASONIC_TRIGGER_PIN); // output
    CLRBIT(ULTRASONIC_ECHO_DDR,    ULTRASONIC_ECHO_PIN);    // input
    
    // External Interrupt Mask Register (EIMSK)
    // Bits 7..0 - INT7-INT0: External Interrupt Request 7-0 Enable
    SETBIT(EIMSK, ULTRASONIC_ECHO_PIN);   
    
    // External Interrupt Control Resiger B (EICRB)
    // Bits 7..0 - ISC71, ISC70 - ISC41, ISC40
    
    ULTRASONIC_PORT |= DIO_BIT; // DIO = HIGH;
}