#include <mega128.h>        // TCCR0
#include <mega128_bits.h>   // CS02
#include <iobits.h>         // __BM

#include "timer.h"
#include "digital_clock.h"

int count = 0;

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
    count++;
    if (count == 5) // 10ms
    {
        increaseClock();
        count = 0;
    }
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0 = 256-100;
    count++;
    if (count == 100) // 100Hz = 10ms
    {
        increaseClock();
        count = 0;
    }
}

void init_timer_w_compare()
{
    // Timer/Counter Control Register 0 - TCCR0
    // Bit 7 - FOC0: Force Output Compare = 0 (no output PWM)
    // Bit 6,3 - WGM01:0: Waveform Generation Mode = 00 (normal)
    // Bit 5:4 - COM01:0: Compare Match Output Mode = 00 (OC0 disconnected)
    // Bit 2:0 - CS02:0: Clock Select = 100 (prescaler = 64: 8MHz/64 = 125kHz)   
    //TCCR0 = 0b00000100;
    //TCCR0 = 1 << CS02;
    //TCCR0 = __BM(CS02);
    SETBIT(TCCR0, CS02);
    
    // Timer/Counter Register 0 - TCNT0
    TCNT0 = 0x00;
    
    // Output Compare Register 0 - OCR0 = 249
    // (8MHz / 64)/(1+249) = 0.5kHz = 2ms 
    OCR0 = 249;
    
    // Timer/Counter Interrupt Mask Register - TIMSK
    // Bit 1 - OCIE0: Timer/Counter 0 Output Compare Match Interrupt Enable = 1
    // Bit 0 - TOIE0: Timer/Counter 0 Overflow Interrupt Enable = 0   
    //TIMSK = 0x02;
    //TIMSK = __BM(OCIE0);
    SETBIT(TIMSK, OCIE0);
    
    #asm("sei")
}

void init_timer_with_overflow()
{
    // Timer/Counter Control Register 0 - TCCR0
    // Bit 7 - FOC0: Force Output Compare = 0 (no output PWM)
    // Bit 6,3 - WGM01:0: Waveform Generation Mode = 00 (normal)
    // Bit 5:4 - COM01:0: Compare Match Output Mode = 00 (OC0 disconnected)
    // Bit 2:0 - CS02:0: Clock Select = 010 (prescaler = 8: 8MHz/8 = 1MHz)   
    //TCCR0 = 0b00000010;
    //TCCR0 = 1 << CS01;
    //TCCR0 = __BM(CS01);
    //SETBIT(TCCR0, CS01);
    TCCR0 = 0x02;
    
    // Timer/Counter Register 0 - TCNT0  
    // (8MHz/8)/100 = 10kHz) 
    TCNT0 = 256-100;
    
    // Output Compare Register 0 - OCR0 = 0
    OCR0 = 0x00; 
    
    // Timer/Counter Interrupt Mask Register - TIMSK
    // Bit 1 - OCIE0: Timer/Counter 0 Output Compare Match Interrupt Enable = 1
    // Bit 0 - TOIE0: Timer/Counter 0 Overflow Interrupt Enable = 0   
    //TIMSK = 0x01;
    //TIMSK = __BM(TOIE0);
    //SETBIT(TIMSK, TOIE0);
    TIMSK = 0x01;
    
    #asm("sei")
}