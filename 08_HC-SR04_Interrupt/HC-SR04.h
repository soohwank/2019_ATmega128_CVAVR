#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#include <stdint.h>
#include <io.h>
#include <iobits.h>

#define ULTRALSONIC_PORT            PORTD
#define ULTRALSONIC_DDR             DDRD
#define ULTRALSONIC_PIN             PIND

#define ULTRALSONIC_TRIGGER_PIN     PORTD6
#define ULTRALSONIC_ECHO_PIN        PORTD7

void setupHC_SR04();
int getDistance

#endif // _HC_SR04_H_