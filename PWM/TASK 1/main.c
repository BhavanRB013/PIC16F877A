
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

void init(void);
void pwmchange(void);

char pwmlow20,pwmhigh20,pwmlow60,pwmhigh60,pwmhigh90,pwmlow90;

void main(void) {
    init();
    while(1)
    {
        pwmchange();
    }
    return;
}

void init()
{
    TRISC = 0XFB;
    CCP1CON = 0X0C;
    T2CON = 0X07;
    PR2 = 0X5E;
    pwmhigh20 = 0X1D;
    pwmlow20 = 0X10;
    pwmhigh60 = 0X38;
    pwmlow60 = 0X10;
    pwmhigh90 = 0X54;
    pwmlow90 = 0X20;
}

void pwmchange()
{
    CCPR1L = pwmhigh20;
    CCP1CON = (CCP1CON&0XCF)|pwmlow20;
    __delay_ms(3000);
    CCPR1L = pwmhigh60;
    CCP1CON = (CCP1CON&0XCF)|pwmlow60;
    __delay_ms(3000);
    CCPR1L = pwmhigh90;
    CCP1CON = (CCP1CON&0XCF)|pwmlow90;
    __delay_ms(3000);
}
