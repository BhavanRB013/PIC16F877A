
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

void init(void);//initialize cmds for right shift
void init1(void);//initialize cmds for left shift
void lcd_command(unsigned char);//used to send cmds to the lcd
void lcd_data(unsigned char);//used to send the data to the lcd

unsigned char arr[]={"BHAVAN"};//array named arr to store value
unsigned char i,j;

void main() {
    TRISC=0X00;//setting PORTC as output mode
    TRISD=0X00;//setting PORTD as output mode
    init();//calling the init() dunction
    for(i=0;i<11;i++){
        lcd_data(arr[i]);//send the array value one by one to lcd_data function
    }
    init1();
    for(j=0;j<11;j++){
        lcd_data(arr[j]);//send the array value one by one to lcd_data function
    }
    while(1);
}

void init(void){

    lcd_command(0X30);//function set command
    __delay_ms(100);
    lcd_command(0X3F);//function set command
    __delay_ms(100);
    lcd_command(0X30);//function set command
    __delay_ms(100);
    lcd_command(0X38);//setting 5x7 in lcd
    __delay_ms(100);
    lcd_command(0X0C);//display on cursor off
    __delay_ms(100);

    lcd_command(0X06);//shift cursor to right
    __delay_ms(100);
    lcd_command(0x83);//Taking the first row and first column of lcd
}

void init1(void){
    
    lcd_command(0X30);//function set command
    __delay_ms(100);
    lcd_command(0X3F);//function set command
    __delay_ms(100);
    lcd_command(0X30);//function set command
    __delay_ms(100);
    lcd_command(0X38);//setting 5x7 in lcd
    __delay_ms(100);
    lcd_command(0X0C);//display on cursor off
    __delay_ms(100);

    lcd_command(0X04);//shift cursor to left
    __delay_ms(100);
    lcd_command(0xCC);//Taking the first row and first column of lcd
}

void lcd_data(unsigned char value){
    PORTC|=0X08;//0000 1000 PORTC RC3 in high
    PORTD=value;//PORTD sending value to lcd
    PORTC|=0x01;//0000 0001 PORTC R0 to high
    PORTC&= ~0x01;//0000 0001 PORTC R0 to low
    __delay_ms(100);
}

void lcd_command(unsigned char value){
    PORTC&= ~0X08;//0000 1000 PORTC RC3 in low
    PORTD=value;//PORTD sending value to lcd
    PORTC|=0x01;//0000 0001 PORTC R0 to high
    PORTC&= ~0x01;//0000 0001 PORTC R0 to low
    __delay_ms(100);
}

