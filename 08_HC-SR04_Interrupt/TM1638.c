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

uint8_t digit2byte(uint8_t n)
{
    switch(n)
    {
        case 0: return 0x3F; // 0
        case 1: return 0x06; // 1
        case 2: return 0x5B; // 2
        case 3: return 0x4F; // 3
        case 4: return 0x66; // 4
        case 5: return 0x6D; // 5
        case 6: return 0x7D; // 6
        case 7: return 0x07; // 7
        case 8: return 0x7F; // 8
        case 9: return 0x6F; // 9   
        
        case 10: return 0xBF; // 0.
        case 11: return 0x86; // 1.
        case 12: return 0xDB; // 2.
        case 13: return 0xCF; // 3.
        case 14: return 0xE6; // 4.
        case 15: return 0xED; // 5.
        case 16: return 0xFD; // 6.
        case 17: return 0x87; // 7.
        case 18: return 0xFF; // 8.
        case 19: return 0xEF; // 9.        
    }
    return 0;
}

uint8_t char2byte(char c)
{
    switch(c)
    {
    case ' ':           return 0x00;
    case 'a': case 'A': return 0x77;
    case 'b': case 'B': return 0x7C;
    case 'c':           return 0x58;
    case 'C':           return 0x39;
    case 'd': case 'D': return 0x5E;
    case 'e': case 'E': return 0x79;
    case 'f': case 'F': return 0x71;
    case 'g': case 'G': return 0x3D;
    case 'h':           return 0x74;
    case 'H':           return 0x76;
    case 'i': case 'I': return 0x30;
    case 'j': case 'J': return 0x1E;    
    case 'k': case 'K': return 0x00; // nO    
    case 'l': case 'L': return 0x38;    
    case 'm': case 'M': return 0x00; // nO  
    case 'n': case 'N': return 0x54;
    case 'o':           return 0x5C;
    case 'O':           return 0x3F;
    case 'p': case 'P': return 0x73;
    case 'q': case 'Q': return 0x67;
    case 'r': case 'R': return 0x50;
    case 's': case 'S': return 0x6D;
    case 't': case 'T': return 0x78;
    case 'u':           return 0x1C;
    case 'U':           return 0x3E;
    case 'v': case 'V': return 0x00; // nO     
    case 'w': case 'W': return 0x00; // nO    
    case 'x': case 'X': return 0x00; // nO  
    case 'y': case 'Y': return 0x6E;
    case 'z': case 'Z': return 0x00; // nO
    }
}

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

void sendCommand(uint8_t command)
{
    STB = LOW;
    shiftOut(command);
    STB = HIGH;
}

void sendCommandAndData(uint8_t command, uint8_t data)
{
    STB = LOW;
    shiftOut(command);
    shiftOut(data);
    STB = HIGH;
}

void sendCommandAndAllZeroData(uint8_t command)
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

uint8_t shiftIn()
{
    // return variable
    uint8_t data = 0;
    
    // temporary variables
    uint8_t i, b;
    
    // change DIO pin to input and enable pull-up
    DDR &= ~DIO_BIT;
    PORT |= DIO_BIT; // DIO = HIGH;
    
    // for each bit from the least significant bit (rightmost),
    for (i = 0, b = 1; i < 8; i++, b <<= 1)
    {              
        // clock low
        CLK = LOW; 
              
        // delay
        delay_us(1);
        
        // read
        if (PIN & DIO_BIT) data |= b;   
                
        // clock high
        CLK = HIGH;             
    }
    
    // disable pull-up and reset DIO pin
    DDR |= DIO_BIT;
    PORT &= ~DIO_BIT; // DIO = LOW; 
    
    return data;
}

uint8_t readButtons()
{
    uint8_t i; 
    uint8_t buttons = 0;   
      
    STB = LOW;
    shiftOut(DATA_COMMAND_READ_KEYS);
    delay_us(2);

    for(i = 0; i < 4; i++)
    {
       buttons |= shiftIn() << i;
    }   

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

void FND(uint8_t index, uint8_t data)
{
    // address of display register
    uint8_t address_command;
    
    // index in [0, 7]
    index = index > 7 ? 7 : index;  
        
    // Mode: fixed address
    
    // [1] Set data command
    sendCommand(DATA_COMMAND_FIXED_ADDRESS_MODE);
    
    // [2] Set address command and data
    address_command = ADDRESS_COMMAND_00 + 2*index;
    sendCommandAndData(address_command, data);
    
    // [3] Set display control command
    sendCommand(DISPLAY_COMMAND_DISPLAY_ON);    
}

void LED(uint8_t index, uint8_t on_off)
{
    // address of display register
    uint8_t address_command;
   
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