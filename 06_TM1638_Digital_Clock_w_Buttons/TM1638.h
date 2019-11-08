#ifndef _TM1638_H_
#define _TM1638_H_

#include <stdint.h>
#include <io.h>
#include <iobits.h>

#define PORT PORTD
#define DDR  DDRD
#define PIN  PIND

#define STB PORTD.0
#define CLK PORTD.1
#define DIO PORTD.2

#define DIO_BIT __BM(PORTD2)

#define ON      1
#define OFF     0

void reset_TM1638();
void FND(uint8_t index, uint8_t data);
void LED(uint8_t index, uint8_t on_off);
uint8_t digit2byte(uint8_t n);
uint8_t char2byte(char c);
uint8_t readButtons();

#endif // _TM1638_H_