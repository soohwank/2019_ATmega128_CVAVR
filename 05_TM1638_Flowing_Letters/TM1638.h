#ifndef _TM1638_H_
#define _TM1638_H_

#define STB PORTD.0
#define CLK PORTD.1
#define DIO PORTD.2
//#define STB PORTB.0
//#define CLK PORTB.1
//#define DIO PORTB.2

#define ON      1
#define OFF     0

void reset_TM1638();
void FND(unsigned char index, unsigned char data);
void LED(unsigned char index, unsigned char on_off);
unsigned char char2byte(char c);

#endif // _TM1638_H_