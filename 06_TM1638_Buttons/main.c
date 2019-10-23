/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
¨Ï Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com
Project : 
Version : 
Date    : 2019-09-26
Author  : 
Company : 
Comments: 
Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <stdint.h>
#include <mega128.h>
#include <delay.h>
#include "TM1638.h"

// Declare your global variables here

void setupATmega128(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0xFF;

// Port E initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTE=0x00;
DDRE=0x00;

// Port F initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTF=0x00;
DDRF=0x00;

// Port G initialization
// Func4=In Func3=In Func2=In Func1=In Func0=In 
// State4=T State3=T State2=T State1=T State0=T 
PORTG=0x00;
DDRG=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
ASSR=0x00;
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// OC1C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: Timer3 Stopped
// Mode: Normal top=0xFFFF
// OC3A output: Discon.
// OC3B output: Discon.
// OC3C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=0x00;
TCCR3B=0x00;
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;
OCR3CH=0x00;
OCR3CL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// INT3: Off
// INT4: Off
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=0x00;
EICRB=0x00;
EIMSK=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

ETIMSK=0x00;

// USART0 initialization
// USART0 disabled
UCSR0B=0x00;

// USART1 initialization
// USART1 disabled
UCSR1B=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;
}

uint8_t clockDigits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int8_t isClockPaused = 0; // 0: normal, 1: pause
int num = 0;
int pausedNum = 0;

void increaseClock()
{
    num++;
    
    // if it is paused, bail
    if (isClockPaused == 1) return;
    
    // increase
    clockDigits[7]++;
     
    // centi-second
    if (clockDigits[7] == 10) { clockDigits[7] = 0; clockDigits[6]++; }
    if (clockDigits[6] == 10) { clockDigits[6] = 0; clockDigits[5]++; }
        
    // second
    if (clockDigits[5] == 10) { clockDigits[5] = 0; clockDigits[4]++; }
    if (clockDigits[4] ==  6) { clockDigits[4] = 0; clockDigits[3]++; }

    // minute
    if (clockDigits[3] == 10) { clockDigits[3] = 0; clockDigits[2]++; }
    if (clockDigits[2] ==  6) { clockDigits[2] = 0; clockDigits[1]++; }
        
    // hour
    if (clockDigits[0] != 2 && clockDigits[1] == 10)
    {
        clockDigits[1] = 0;
        clockDigits[0]++;
    }
    if (clockDigits[0] == 2 && clockDigits[1] == 4)
    {
        clockDigits[1] = 0;
        clockDigits[0] = 0;
    }      
}

void togglePauseClock()
{
    // avoid toggle switch chattering 
    if (num - pausedNum < 30) return;
    
    pausedNum = num;
    isClockPaused = 1 - isClockPaused;
}

void resetClock()
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        clockDigits[i] = 0; 
    }        
}

void displayClock()
{
    int i;
    
    if (isClockPaused && ((num - pausedNum)/30)%2 == 1)
    {
        for(i = 0; i < 8; i++)
        {
            FND(i, char2byte(' ')); 
        }    
    }
    else
    {
        for(i = 0; i < 8; i++)
        {
            FND(i, digit2byte(i%2 == 0 ? clockDigits[i] : clockDigits[i]+10)); 
            //FND(i, digit2byte(clockDigits[i])); 
        } 
    }   
}

void main()
{
    uint8_t i;
    uint8_t buttons;
    
    // setup
    setupATmega128();
    
    // reset TM1638
    reset_TM1638();
    
    while (1)
    {
        // sleep 10ms - 8[FND]*4[ShiftOut/FND]*8[us/ShiftOut]
        delay_us(10000-8*4*8);
        
        // increase clock
        increaseClock();
        
        // display clock
        displayClock();

        // read buttons
        buttons = readButtons();   
       
        // display buttons on LED
        for(i = 0; i < 8; i++)
        {
            LED(i+1, buttons & (1<<i) ? ON : OFF);  
        }
        
        // manipulate clock with buttons
        if (buttons & (1<<7)) resetClock();
        if (buttons & (1<<6)) togglePauseClock();                   
    }
}