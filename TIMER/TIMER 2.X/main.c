
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

void T2delay(void);

void main(void) {
    //port configuration
    TRISB = 0X00;
    //SETTING POSTSCALE AND PRESCALE
    T2CON = 0X78;
    while(1){
        PORTB = 0XFF;
        T2delay();
        PORTB = 0X00;
        T2delay();
    }
    return;
}

void T2delay(void){
    unsigned int i;
    for(i=0;i<675;i++){
        T2CON |= 1<<2;
        while(!(TMR2IF));
        TMR2IF=0;
    }
}

/*
 FOUT=FCLK/(4*PRESCALAR*(PR2-TMR2)*POSTSCALAR*COUNT) WHERE TOUT = 1/FOUT
 Here, My fclk = 11.0592MHz (You can put your board?s fclk)

Prescaler = 1 (It is based on T2CKPS1:T2CKPS0 bits in T2CON)

Postscaler = 16 (It is based on TOUTPS3:TOUTPS0 bits in T2CON)

TMR2 = 0. (My TMR2?s value will be 0)

PR2 = 255 (My PR2?s value will be 255)

Desire Delay (Tout = 1 second) So Fout = 1  (Tout = 1/Fout)

Apply these values to the above formula.

Count = 11059200 / (4*1*(256-0)*16*1)

Count = 675.*/
