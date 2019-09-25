#include <mega128.h>
#include <delay.h>
#include "TM1638.h"

#define HIGH    1
#define LOW     0

#define DATA_COMMAND_AUTO_ADDRESS_INCREMENT_MODE    0x40
#define DATA_COMMAND_FIXED_ADDRESS_MODE             0X44

#define ADDRESS_COMMAND_00  0xC0
                                      
#define DISPLAY_COMMAND_DISPLAY_OFF 0x80
#define DISPLAY_COMMAND_DISPLAY_ON  0x8F

unsigned char DIGIT_2_SEVEN_SEGMENT_DISPLAY[10] = {
   0x3F, // 0
   0x06, // 1
   0x5B, // 2
   0x4F, // 3
   0x66, // 4
   0x6D, // 5
   0x7D, // 6
   0x07, // 7
   0x7F, // 8
   0x6F  // 9
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
        
        // clock high
        CLK = HIGH;   
        
        // delay
        delay_ms(1);
        
        // clock low
        CLK = LOW;
    }
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
    
    // digit in [0, 9]
    digit = digit > 9 ? 9 : digit;
    
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