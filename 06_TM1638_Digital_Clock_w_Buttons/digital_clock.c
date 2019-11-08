#include "digital_clock.h"
#include "TM1638.h"

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