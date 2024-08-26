
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
char pwmhigh10,pwmlow10,pwmhigh50,pwmlow50,pwmhigh80,pwmlow80;

void main(void) {
    init();
    while(1)
    {
        pwmchange();
    }
    return;
}

void init(void)
{
    TRISC = 0xFB;
    CCP1CON = 0X0C;
    T2CON = 0X06;
    //PR2 = FOSC/4*FPWM*TIM2_PRESCALAR_VALUE -1
    //6000000/(4*1000*16)-1 = 94 = 0X5E
    PR2 = 0X5E;
    /*FOR 10%: 10/100 = 0.1
     DUTYCYCLE TIME = 0.1/PWM_FREQ = 0.1/1000 = 0.0001
     CCPR1:CCP1CON<5:4> = 0.0001*6000000/16 = 38 = 0X26 = 0010 0110
     LOAD CCPR1 = 0000 1001  CCP1CON<5:4> = 10*/
    pwmhigh10 = 0X09;
    pwmlow10 = 0X20;
    pwmhigh50 = 0X2F;
    pwmlow50 = 0X00;
    pwmhigh80 = 0X4B;
    pwmlow80 = 0X00;
}

void pwmchange(void)
{
    CCPR1L= pwmhigh10;
    CCP1CON = (CCP1CON&0XCF)|pwmlow10;
    __delay_ms(3000);
    CCPR1L = pwmhigh50;
    CCP1CON = (CCP1CON&0XCF)|pwmlow50;
    __delay_ms(3000);
    CCPR1L = pwmlow80;
    CCP1CON = (CCP1CON&0XCF)|pwmlow80;
    __delay_ms(3000);
}