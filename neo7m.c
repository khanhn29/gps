/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 17/10/2016
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>

// Alphanumeric LCD functions
#include <alcd.h>
// Declare your global variables here

#include <delay.h>
unsigned char u_data, ktra=0;
unsigned char demkd,demvd;

// USART0 Receiver interrupt service routine


interrupt [USART0_RXC] void usart0_rx_isr(void)
{
    u_data=UDR0;

    //Filtering $GPRMC, read nmea GPRMC for more details
    if((u_data=='$'))
    {
        ktra=1;    //$ 
        demkd=1;
        demvd=1;
    }   
    if (ktra==1)
    {
        if(u_data=='G')
        {
            ktra=2;     //G 
        }
    }
    if(ktra==2)
    {   
        if(u_data=='P')
        {
            ktra=3;    //P
        }
    } 
    if(ktra==3)
    {
        if(u_data=='R')
            ktra=4;    //R
    } 
    if(ktra==4)
    {   
        if(u_data=='M')
            ktra=5;    //M 
    } 
    if(ktra==5)
    {   
        if(u_data=='C')
            ktra=6;    //C
    }
    if(ktra==6)
    {
        if(u_data=='A')
        ktra=7;
    } 

    if(ktra==10)
    {
        if (u_data!=',')
        {
            //lcd_putchar(u_data);        //in vi do 
            UDR1=u_data;
            lcd_putchar(u_data);
            demkd++;
            if (demkd==4) {lcd_putchar('"');}
        }
        else
        {
            ktra=11;  //dau phay nam truoc east hoac west
            UDR1='\r';
        }
    }  
    if(ktra==9)
    {
        if(u_data==',')
        {
            ktra=10;      //dau phay nam truoc kinh do Longitude 
            lcd_gotoxy(0,1);
            lcd_puts("kd");
            lcd_gotoxy(3,1);
        }
    }
    if(ktra==8)
    {
        if (u_data!=',')
        {
            //lcd_putchar(u_data);        //in vi do
            UDR1=u_data;
            lcd_putchar(u_data);

            demvd++;
            if (demvd==3)
                lcd_putchar('"');
        }
        else{
            ktra=9;  //dau phay nam truoc North hoac South
            UDR1=',';
        }
    }
    if(ktra==7)
    {
        if(u_data==',')
        {
            ktra=8;   //dau phay nam truoc vi do latitude 
            lcd_gotoxy(0,0);
            lcd_puts("vd");
            lcd_gotoxy(3,0);
        }
    }
}

// Standard Input/Output functions
#include <stdio.h>

void main(void)
{
    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTA Bit 0
    // RD - PORTA Bit 1
    // EN - PORTA Bit 2
    // D4 - PORTA Bit 4
    // D5 - PORTA Bit 5
    // D6 - PORTA Bit 6
    // D7 - PORTA Bit 7
    // Characters/line: 16
    UCSR0B=0b10011000;       // RXCIE=1, RXEN=1, TXEN=1 Ngat RX, cho phep RX va TX
    UCSR0C=0x86;             //8bit uart, 1bit stop, no parity
    UBRR0L=71;               //baud 9600bps

    UCSR1B=0b10011000;       // RXCIE=1, RXEN=1, TXEN=1 Ngat RX, cho phep RX va TX
    UCSR1C=0x86;             //8bit uart, 1bit stop, no parity
    UBRR1L=71;               //baud 9600bps
    lcd_init(16); //LCD16x2 init
    lcd_gotoxy(0,0);
    lcd_puts("DANG DO");//Gui chuoi len LCD
    delay_ms(100);
    lcd_gotoxy(0,0);
    lcd_puts("DANG DO.");
    delay_ms(100);
    lcd_gotoxy(0,0);
    lcd_puts("DANG DO..");
    delay_ms(100);
    lcd_gotoxy(0,0);
    lcd_puts("DANG DO...");
    delay_ms(100);
    lcd_clear();
  
    #asm("sei")  //Ngat cuc bo

    while (1);
}
