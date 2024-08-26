
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

unsigned char c;

void main(void) {
    TRISC = 0X0F;
    TRISD = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    
    while(1){
        c = PORTC;
        switch(c){
            case 0X01:
                PORTD = 0X08;
                break;
            case 0X02:
                PORTD = 0X00;
                break;
            case 0X04:
                PORTD = 0X28;
                break;
            case 0X08:
                PORTD = 0X20;
                break;
            default:
                PORTD = 0X00;
               
        }
    }
    return;
}
