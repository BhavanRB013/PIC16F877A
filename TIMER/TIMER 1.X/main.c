
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

void T1delay(void);

void main(void) {
    //port configuration
    TRISB = 0X00;
    //TIMER 1 ON
    T1CON = 0X01;
    
    while(1){
        PORTB = 0XFF;
        T1delay();
        PORTB = 0X00;
        T1delay();
    }
    return;
}

void T1delay(void){
    int i;
    for(i=0;i<42;i++){
        TMR1H=TMR1L=0;
        while(!(TMR1IF));
        TMR1IF=0;
    }
}

/*
 FOUT = FCLK/(4*PRESCALAR*(65536-TMR1)*COUNT) WHERE TOUT = 1/FOUT
 
Here, My fclk = 11.0592MHz (You can put your board?s fclk)

Prescaler = 1 (It is based on T1CKPS1 ? T1CKPS0 bits in T1CON Register)

TMR1 = 0. (My TMR1?s value will be 0)

Desire Delay (Tout = 1 second) So Fout = 1  (Tout = 1/Fout)

Apply these values to the above formula.

Count = 11059200 / (4*1*65536*1)

Count = 42.1875 (approximately 42).*/
