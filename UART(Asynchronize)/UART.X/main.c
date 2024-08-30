
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

void UART_INIT(void);
void UART_Txchar(unsigned char);
void UART_Txstring(unsigned char*);
unsigned char UART_Rx(void);

void main(void) {
    TRISC6 = 0;
    TRISC7 = 1;
    UART_INIT();
    UART_Txstring("Enter some letters: ");
    while(1){
        UART_Txchar(UART_Rx());
    }
    return;
}

void UART_INIT(void){
    TXSTA = 0X20;
    RCSTA = 0X90;
    SPBRG = 17;
    TXIF=RCIF=0;
}

void UART_Txstring(unsigned char* s){
    while(*s){
        UART_Txchar(*s++);
    }
}

void UART_Txchar(unsigned char a){
    TXREG = a;
    while(!(TXIF));
    TXIF=0;
}

unsigned char UART_Rx(){
    while(!(RCIF));
    RCIF=0;
    return RCREG;
}
