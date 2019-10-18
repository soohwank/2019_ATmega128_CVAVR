#include <stdint.h>

#include <mega128.h>
#include <delay.h>
#include "TM1638.h"

#define HIGH    1
#define LOW     0

#define DATA_COMMAND_AUTO_ADDRESS_INCREMENT_MODE    0x40
#define DATA_COMMAND_FIXED_ADDRESS_MODE             0X44
#define DATA_COMMAND_READ_KEYS                      0x42

#define ADDRESS_COMMAND_00  0xC0
                                      
#define DISPLAY_COMMAND_DISPLAY_OFF 0x80
#define DISPLAY_COMMAND_DISPLAY_ON  0x8F

unsigned char DIGIT_2_SEVEN_SEGMENT_DISPLAY[20] = {
   0x3F, // 0
   0x06, // 1
   0x5B, // 2
   0x4F, // 3
   0x66, // 4
   0x6D, // 5
   0x7D, // 6
   0x07, // 7
   0x7F, // 8
   0x6F, // 9
   
   0xBF, // 0.
   0x86, // 1.
   0xDB, // 2.
   0xCF, // 3.
   0xE6, // 4.
   0xED, // 5.
   0xFD, // 6.
   0x87, // 7.
   0xFF, // 8.
   0xEF  // 9.
};

// Shifts out a byte of data one bit at a time.
// Starts from the least (rightmost) significant bit.
// Each bit is written in turn to a data pin (DIO),
// after which a clock pin (CLK) is pulsed (taken high, then low)
// to indicate that the bit is available.
void shiftOut(unsigned char value)
{
    // temporary variables
    int i;
    bit outputBit;
    
    // for each bit from the least significant bit (rightmost),
    for (i = 0; i < 8; i++)
    {
        // mask out the bit
        outputBit = value & (1 << i);
        
        // set it to the data pin (DIO)
        DIO = outputBit;
        
        // clock low
        CLK = LOW;   
        
        // delay
        delay_us(1);
        
        // clock high
        CLK = HIGH;
    }
}

unsigned char shiftIn()
{
    // return variable
    unsigned char data = 0;
    
    // temporary variables
    int i;
    
    // change DIO pin to input and enable pull-up
    DDR &= ~DIO_BIT;
    PORT |= DIO_BIT; // DIO = HIGH;
    
    // for each bit from the least significant bit (rightmost),
    for (i = 0; i < 8; i++)
    {              
        // clock low
        CLK = LOW; 
              
        // delay
        delay_us(1);
        
        // read
        if (PIN & DIO_BIT) data |= 1 << i;   
                
        // clock high
        CLK = HIGH;             
    }
    
    // disable pull-up and reset DIO pin
    DDR |= DIO_BIT;
    PORT &= ~DIO_BIT; // DIO = LOW; 
    
    return data;
}

void sendCommand(unsigned char command)
{
    STB = LOW;
    shiftOut(command);
    STB = HIGH;
}

void sendCommandAndData(unsigned char command, unsigned char data)
{
    STB = LOW;
    shiftOut(command);
    shiftOut(data);
    STB = HIGH;
}

void sendCommandAndAllZeroData(unsigned char command)
{
    int i;
    STB = LOW;
    shiftOut(command);
    for(i = 0; i < 16; i++)
    {
        shiftOut(0x00);
    }  
    STB = HIGH;
}

unsigned char readButtons()
{
    unsigned char buttons1 = 0;
    unsigned char buttons2 = 0;
    unsigned char buttons3 = 0;
    unsigned char buttons4 = 0;
    //unsigned char buttons = 0;
    uint8_t buttons = 0;

    unsigned char temp;
    unsigned char K1_1 = 0b00100000;
    unsigned char K2_1 = 0b01000000;
    unsigned char K3_1 = 0b10000000;
    unsigned char K1_2 = 0b00000010;
    unsigned char K2_2 = 0b00000100;
    unsigned char K3_2 = 0b00001000;
    
    unsigned char K_1 = 0b11100000;
    unsigned char K_2 = 0b00001110;
    
    int i; 
      
    STB = LOW;
    shiftOut(DATA_COMMAND_READ_KEYS);
    delay_us(2);

    //for(i = 0; i < 4; i++)
    //{
    //   temp = shiftIn() << i;
    //   buttons |= temp;
    //}   
    
//    temp = shiftIn();  // KS1, KS5
//    if (temp) buttons |= 1 << 0; 
//    if (temp) buttons |= 1 << 4; 
//
//    temp = shiftIn();  // KS2, KS6  
//    if (temp) buttons |= 1 << 1; 
//    if (temp) buttons |= 1 << 5; 
//
//    temp = shiftIn();  // KS3, KS7  
//    if (temp) buttons |= 1 << 2; 
//    if (temp) buttons |= 1 << 6; 
//    
//    temp = shiftIn();  // KS4, KS8  
//    if (temp) buttons |= 1 << 3; 
//    if (temp) buttons |= 1 << 7; 

    // change DIO pin to input and enable pull-up
    //DDR &= ~DIO_BIT;
    //PORT |= DIO_BIT; // DIO = HIGH;

    temp = shiftIn();  // KS1, KS5
    if (temp) buttons1 = 0b10001000; 

    temp = shiftIn();  // KS2, KS6  
    if (temp) buttons2 = 0b01000100; 

    temp = shiftIn();  // KS3, KS7  
    if (temp) buttons3 = 0b00100010; 
    
    temp = shiftIn();  // KS4, KS8  
    if (temp) buttons4 = 0b00010001; 

    //DDR |= DIO_BIT;
    //PORT &= ~DIO_BIT; // DIO = LOW; 

    return 0b10001000 | 0b01000100;
    
    //return buttons1 | buttons2 | buttons3 | buttons4;
    return buttons1;

    return buttons;
    //return temp;
    
    // KS1, KS2
    temp = shiftIn();
    //buttons |= (temp & K1_1) ? 1 << 0 : 0;  
    //buttons |= (temp & K1_2) ? 1 << 1 : 0;
    if (temp & K1_1) buttons |= 1 << 0; 
    if (temp & K1_2) buttons |= 1 << 1; 

    // KS3, KS4
    temp = shiftIn();
    //buttons |= (temp & K1_1) ? 1 << 2 : 0;  
    //buttons |= (temp & K1_2) ? 1 << 3 : 0;  
    if (temp & K1_1) buttons |= 1 << 2; 
    if (temp & K1_2) buttons |= 1 << 3; 

    // KS5, KS6
    temp = shiftIn();
    //buttons |= (temp & K1_1) ? 1 << 4 : 0;  
    //buttons |= (temp & K1_2) ? 1 << 5 : 0;  
    if (temp & K1_1) buttons |= 1 << 4; 
    if (temp & K1_2) buttons |= 1 << 5; 

    // KS7, KS8
    temp = shiftIn();
    //buttons |= (temp & K1_1) ? 1 << 6 : 0;  
    //buttons |= (temp & K1_2) ? 1 << 7 : 0;  
    if (temp & K1_1) buttons |= 1 << 6; 
    if (temp & K1_2) buttons |= 1 << 7; 
    
    STB = HIGH;  
    
    buttons = 0xFF;
    
    return buttons;
}

void reset_TM1638()
{   
    // Mode: auto address increment by 1
    
    // [1] Set data command
    sendCommand(DATA_COMMAND_AUTO_ADDRESS_INCREMENT_MODE);
    
    // [2] Set address command and data
    sendCommandAndAllZeroData(ADDRESS_COMMAND_00);
    
    // [3] Set display control command
    sendCommand(DISPLAY_COMMAND_DISPLAY_ON);
}

void FND(unsigned char index, unsigned char digit)
{
    // address of display register
    unsigned char address_command;
    
    // index in [0, 7]
    index = index > 7 ? 7 : index;  
    
    // digit in [0, 19]
    digit = digit > 19 ? 19 : digit;
    
    // Mode: fixed address
    
    // [1] Set data command
    sendCommand(DATA_COMMAND_FIXED_ADDRESS_MODE);
    
    // [2] Set address command and data
    address_command = ADDRESS_COMMAND_00 + 2*index;
    sendCommandAndData(address_command, DIGIT_2_SEVEN_SEGMENT_DISPLAY[digit]);
    
    // [3] Set display control command
    sendCommand(DISPLAY_COMMAND_DISPLAY_ON);    
}

void LED(unsigned char index, unsigned char on_off)
{
    // address of display register
    unsigned char address_command;
   
    // index in [1, 8]
    index = index < 1 ? 1 : index;  
    index = index > 8 ? 8 : index;  
      
    // Mode: fixed address
    
    // [1] Set data command
    sendCommand(DATA_COMMAND_FIXED_ADDRESS_MODE);
    
    // [2] Set address command and data
    address_command = ADDRESS_COMMAND_00 + 2*(index-1) + 1;
    sendCommandAndData(address_command, on_off);
    
    // [3] Set display control command
    sendCommand(DISPLAY_COMMAND_DISPLAY_ON);
}

