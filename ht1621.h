//#include  <msp430f249.h>

//按键

#define SDWN  (P1IN&BIT1)
#define SUP   (P1IN&BIT2)
#define ENTER   (P1IN&BIT3)


#define uchar unsigned char
#define BIAS 0x28
#define SYSEN 0x01
#define LCDOFF 0x02
#define LCDON 0x03
#define LCD_DATA1 P1OUT|=0X10 //
#define LCD_WR1 P1OUT|=0X20//
#define LCD_RD1  P1OUT|=0X40//
#define LCD_CS1 P1OUT|=0X80//
#define LCD_DATA0 P1OUT&=~0X10 //
#define LCD_WR0 P1OUT&=~0X20//
#define LCD_RD0  P1OUT&=~0X40//
#define LCD_CS0 P1OUT&=~0X80//
void SendBit_1621(uchar data,uchar cnt); //data 的高cnt 位写入HT1621，高位在前
void SendDataBit_1621(uchar data,uchar cnt); //data 的低cnt 位写入HT1621，低位在前
void SendCmd(uchar command);
void Write_1621(uchar addr,uchar data);
void WriteAll_1621(uchar addr,uchar *p,uchar cnt);
void LCD_INIT();
void show(unsigned char *ptr);
void display(unsigned char *ptr);
