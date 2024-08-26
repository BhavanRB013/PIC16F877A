
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


unsigned char a;
void main(void) {
    TRISB = 0XF0;
    TRISC = 0X00;
    PORTB = 0X00;
    PORTC = 0X00;
    
    while(1){
        a = PORTB;
        switch(a){
            case 0XE0:
                PORTC = 0X80;
                break;
            case 0XD0:
                PORTC = 0X04;
                break;
            case 0XB0:
                PORTC = 0X00;
                break;
            case 0X70:
                PORTC = 0X84;
                break;
            case 0XF0:
                PORTC = 0X00;
                break;
        }
        
    }
    return;
}
