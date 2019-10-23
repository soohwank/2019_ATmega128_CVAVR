/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2019-10-22
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

#include <mega128.h>
#include <stdint.h>
#include <delay.h>
#include <io.h>
#include <iobits.h>
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
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

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

// Port F initialization: ADV
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTF=0x00;
DDRF=0x00; // input

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


void init_ADC()
{
    // [1] ADC Multiplexer Selection Register, ADMUX
    // ADMUX = REFS1, REFS2, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0
    // (Bit 7:6) REFS1:2 (Voltage Reference Selection) = 01: AVCC with external capacitor at AREF pin
    // (Bit 5) ADLAR (ADC Left Adjust Result) = 0: right adjust the result
    // (Bit 4:0) MUX4, MUX3, MUX2, MUX1, MUX0 = 00000: ADC0 for single ended input
    //ADMUX = 0x40; // 0b01000000
    //ADMUX = (1<<REFS0); 
    SETBIT(ADMUX, REFS0); 
    
    // [2] ADC Control and Status Register A - ADCSRA
    // ADCSRA = ADEN, ADSC, ADFR, ADIF, ADIE, ADPS2, ADPS1, ADPS0
    // (Bit 7) ADEN (ADC enable) = 1: enable
    // (Bit 6) ADSC (ADC Start Conversion) = 0: stop
    // (Bit 5) ADFR (ADC Free Running Select) = 0: Single Conversion Mode
    // (Bit 4) ADIF (ADC Interrupt Flag) = 0: no AD conversion completed
    // (Bit 3) ADIE (ADC Interrupt Enable) = 0: disabled
    // (Bit 2:0) ADPS2:0 (ADC Prescaler Select Bits) = 100: Division Factor = 32
    //ADCSRA = 0x84; // 0b10000100
    //ADCSRA = (1<<ADEN)|(1<<ADPS2); 
    SETBIT(ADCSRA, ADEN);
    SETBIT(ADCSRA, ADPS2);
}

int read_ADC()
{   
    // ADC Start Conversion
    ADCSR |= (1<<ADSC);
    
    // wait until the AD conversion is completed   
    //while(ADCSRA & (1<<ADIF) == 0x00);
    while(!TSTBIT(ADCSRA, ADIF));
    
    // read the value (16 bits)
    return ADCW; 
}

void main()
{
    // temporary variables
    int i;
    unsigned int ADC_value;
    int LED_ON_count;
     
    // setup
    setupATmega128();
       
    // reset TM1638
    reset_TM1638();
    
    // init ADC
    init_ADC();
    
    FND(0, char2byte('A'));      
    FND(1, char2byte('D'));      
    FND(2, char2byte('C'));      
    FND(3, char2byte(' '));      
    FND(4, char2byte('T'));      
    FND(5, char2byte('E'));      
    FND(6, char2byte('S'));      
    FND(7, char2byte('T')); 
    delay_ms(1000);  
        
    while (1)
    {
        // read ADC
        ADC_value = read_ADC();
        
        // LED: 1 LED = 1024/8 = 128 
        LED_ON_count = ADC_value == 0 ? 0 : ADC_value/128 + 1;       
        for (i = 0; i < 8; i++)
        {
            if (i < LED_ON_count) LED(8-i, ON);
            else                  LED(8-i, OFF);
        } 
        
        // FND
        for (i = 7; i >= 0; i--)
        {
            FND(i, digit2byte(ADC_value % 10));             
            ADC_value = ADC_value / 10;
        } 
             
        delay_ms(1);  
    }
}
