
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

void lcd_data(unsigned char);
void lcd_cmd(unsigned char);
void lcd_output(unsigned int);
void keyscane();
void compare(unsigned int);
void init();
unsigned char arr[30] = {"BATT VOLT"};
unsigned char d3,d2,d1,x,m,n,value;
unsigned int j,i;

void main(){
    init();
    while(1){
        keyscane();
    }
}

void init(){
    TRISC=0X00;
    TRISB=0XF0;
    TRISD=0X00;
    PORTB=0X00;
    OPTION_REG&=0x7F;
    lcd_cmd(0X38);
    __delay_ms(100);
    lcd_cmd(0X38);
    __delay_ms(100);
    lcd_cmd(0X38);
    __delay_ms(100);
    lcd_cmd(0X06);
    __delay_ms(100);
    lcd_cmd(0X0C);
    __delay_ms(100);
    lcd_cmd(0X01);
    __delay_ms(100);
    j=175;
}

void keyscane(){

    value=PORTB&0XF0;
    switch(value){
        case 0XE0:
            lcd_cmd(0X80);
            for(x=0;x<9;x++){
                lcd_data(arr[x]);
            }
            lcd_cmd(0X8A);
            lcd_output(j);
            compare(j);
            break;  
        case 0XD0:
            j++;
            if(j>225){
                j=225;
            }
            lcd_cmd(0X8A);
            lcd_output(j);
            compare(j);
            break;
        case 0XB0:
            j--;
            if(j<155){
                j=155;
            }
            lcd_cmd(0X8A);
            lcd_output(j);
            compare(j);
            break;
        case 0X70:
            j=175;
            lcd_cmd(0X8A);
            lcd_output(j);
            compare(j);
            break;
    }
}

void lcd_output(unsigned int i){
    d3=(unsigned char)(i/100);
    d2=(unsigned char)((i-(d3*100))/10);
    d1=(unsigned char)(i-(d3*100)-(d2*10));
    unsigned char dot = 0X2E;
    
    lcd_cmd(0X8A);
    lcd_data(0X30+d3);
    lcd_cmd(0X8B);
    lcd_data(0X30+d2);
    lcd_cmd(0X8C);
    lcd_data(dot);
    lcd_cmd(0X8D);
    lcd_data(0X30+d1);
    
}

void lcd_data(unsigned char i){
    PORTC|=0x08;
    PORTD=i;
    PORTC|=0X01;
    PORTC&=~0X01;
    __delay_ms(100);
}

void lcd_cmd(unsigned char i){
    PORTC&=~0X08;
    PORTD=i;
    PORTC|=0X01;
    PORTC&=~0X01;
    __delay_ms(100);
}

void compare(unsigned int i){
    lcd_cmd(0XC0);
    if(i>=155 && i<=175){
        unsigned char z[]={"BATT LOW"};
        for(int l=0;l<8;l++){
            lcd_data(z[l]);
        }
    }
    else if(i>=176 && i<=205){
       unsigned char z[]={"BATT NORMAL"};
       for(int l=0;l<11;l++){
           lcd_data(z[l]);
       }
    }else{
       unsigned char z[]={"BATT HIGH"};
       for(int l=0;l<9;l++){
           lcd_data(z[l]);
       }
    }
    
}