
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

//function declaration
void T0delay(void);

void main(void) {
    //port declaration
    TRISB = 0X00;
    //SETTING THE PRESCALAR VALUE
    OPTION_REG = 0X07;
    
    while(1){
        PORTB = 0XFF;
        T0delay();
        PORTB = 0X00;
        T0delay();
    }
    
    return;
}

void T0delay(void){
    uint8_t i;
    for(i=0;i<42;i++){
        while(!(TMR0IF));
        TMR0IF = 0;//T0IF
    }
}

/*
 * FOUT = FCLK/(4*PRESCALAR*(256-1)*COUNT) WHERE TOUT = 1/FOUT
 
Here, My fclk = 11.0592MHz (You can put your board?s fclk)

Prescaler = 256 (It is based on PS0 ? PS2 bits in OPTION_REG)

TMR0 = 0. (My TMR0?s value will be 0)

Desire Delay (Tout = 1 second) So Fout = 1  (Tout = 1/Fout)

Apply these values to the above formula.

Count = 11059200 / (4*256*256*1)

Count = 42.1875 (approximately 42).
 */