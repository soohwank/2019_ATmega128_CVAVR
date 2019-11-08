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

unsigned char digit2byte(unsigned short n)
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
    }
    return 0;
}

unsigned char char2byte(char c)
{
    switch(c)
    {
    case ' ':           return 0x00; 
    
    case '!':           return 0x86;
    case '"':           return 0x22;
    case '#':           return 0x7E;
    case '$':           return 0x6D;
    case '%':           return 0xD2;
    case '&':           return 0x46;
    case '\'':          return 0x20;
    case '(':           return 0x29;
    case ')':           return 0x0B;
    case '*':           return 0x21;
    case '+':           return 0x70;
    case ',':           return 0x10;
    case '-':           return 0x40;
    case '.':           return 0x80;
    case '/':           return 0x52;

    case ':':           return 0x09;
    case ';':           return 0x0D;
    case '<':           return 0x61;
    case '=':           return 0x48;
    case '>':           return 0x43;
    case '?':           return 0xD3;
    case '@':           return 0x5F;

    case '[':           return 0x39;
    case '\\':          return 0x64;
    case ']':           return 0x0F;
    case '^':           return 0x23;
    case '_':           return 0x08;
    case '`':           return 0x02;
    case '{':           return 0x46;
    case '|':           return 0x30;
    case '}':           return 0x70;
    case '~':           return 0x01;
            
    case '0':           return 0x3F;
    case '1':           return 0x06;
    case '2':           return 0x5B;
    case '3':           return 0x4F;
    case '4':           return 0x66;
    case '5':           return 0x6D;
    case '6':           return 0x7D;
    case '7':           return 0x07;
    case '8':           return 0x7F;
    case '9':           return 0x6F;
       
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
    case 'k': case 'K': return 0x75; // not clear
    case 'l': case 'L': return 0x38;    
    case 'm':           return 0x14; // not clear
    case 'M':           return 0x15; // not clear
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
    case 'v':           return 0x1C; // not clear
    case 'V':           return 0x3E; // not clear     
    case 'w':           return 0x14; // not clear 
    case 'W':           return 0x2A; // not clear     
    case 'x': case 'X': return 0x76; // not clear    
    case 'y': case 'Y': return 0x6E;
    case 'z': case 'Z': return 0x5B; // not clear
    default:            return 0x00;
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

void FND(unsigned char index, unsigned char data)
{
    // address of display register
    unsigned char address_command;
    
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