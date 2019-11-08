#include "HC-SR04.h"

void setupHC_SR04()
{
    // set the trigger pin as output
    SETBIT(ULTRALSONIC_DDR, ULTRALSONIC_TRIGGER_PIN);
    
    // set the echo pin as input
    CLRBIT(ULTRALSONIC_DDR, ULTRALSONIC_ECHO_PIN);
}

void func()
{
    // [0] clear the trigger pin
    CLRBIT(ULTRALSONIC_PORT, ULTRALSONIC_TRIGGER_PIN);
    delay_us(1);

    // [1] set the trigger high for 10us
    SETBIT(ULTRALSONIC_PORT, ULTRALSONIC_TRIGGER_PIN);   
    delay_us(10);
    CLRBIT(ULTRALSONIC_PORT, ULTRALSONIC_TRIGGER_PIN);
    
      
}