#include  <msp430f5438a.h>  
#include "ht1621.h"   
const char  distab[]={0xEB,0x60,0xC7,0xE5,0x6C,0xad,0xaf,0xe0,0xef,0xec,     //0,1,2,3,4,5,6,7,8,9
                      0X00,0xEE,0X2F,0X8B,0X67,0X8F,0X8E,0XAB,0X6E,0X0A,     //mie,a,b,c,d,e,f,G,H,I
                      0X61,0X4E,0X0B,0X4e,0X26,0X27,0x6E,0xDC,0x00,0xad,    //j,k,l,m,n,o,P,Q,R,S
                      0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    //-,
                      0x4
                      };


void SendBit_1621(uchar data,uchar cnt) //data �ĸ�cnt λд��HT1621����λ��ǰ
{
uchar i;
for(i =0; i <cnt; i ++)
{
if((data&0x80)==0) LCD_DATA0;
else LCD_DATA1;
LCD_WR0;
LCD_WR1;
data<<=1;
}
}
void SendDataBit_1621(uchar data,uchar cnt) //data �ĵ�cnt λд��HT1621����λ��ǰ
{
uchar i;
for(i =0; i <cnt; i ++)
{
if((data&0x01)==0) LCD_DATA0;
else LCD_DATA1;
LCD_WR0;
LCD_WR1;
data>>=1;
}
}

void SendCmd(uchar command)
{
LCD_CS0;
SendBit_1621(0x80,3); //д���־��"100"
SendBit_1621(command,9); //д��9 λ����,����ǰ8 λΪcommand ����,���1 λ����
LCD_CS1;
}
void Write_1621(uchar addr,uchar data)
{
LCD_CS0;
SendBit_1621(0xa0,3); //д���־��"101"
SendBit_1621(addr<<2,6); //д��6 λaddr
SendDataBit_1621(data,4); //д��data �ĵ�4 λ
LCD_CS1;
}
void WriteAll_1621(uchar addr,uchar *p,uchar cnt)
{
uchar i;
LCD_CS0;;
SendBit_1621(0xa0,3); //д���־��"101"
SendBit_1621(addr<<2,6); //д��6 λaddr
for(i =0; i <cnt; i ++,p++) //����д������
{
SendDataBit_1621(*p,8);
}
LCD_CS1;
}
void LCD_INIT()
{uchar i;
uchar a[32];
for(i=0;i<32;i++)
{a[i]=0x00;}

SendCmd(BIAS); //����ƫѹ��ռ�ձ�
SendCmd(SYSEN); //��ϵͳ����
SendCmd(LCDON); //��LCD ƫѹ������

WriteAll_1621(0,a,6); //����ʼ��ַΪ0 ������д��5 ���ֽ�����
//for(i=4;i<10;i++)
//{a[i-4]=distab[8];}
a[0]=distab[7];
a[1]=distab[2];
a[2]=distab[11];
a[3]=distab[40];
a[4]=distab[2];
a[5]=distab[11];

WriteAll_1621(0,a,6); //����ʼ��ַΪ0 ������д��5 ���ֽ�����

//a[0]=0xf;a[2]=0x0f;
//WriteAll_1621(0,a,10); //����ʼ��ַΪ0 ������д��5 ���ֽ�����

//aΪд�����ݵ���ʼ��ַ��5 Ϊд����ֽ���
//SendCmd(LCDOFF); //�ر�LCD ��ʾ
}

void display(unsigned char *ptr)
{
 unsigned char a[6];
unsigned char i,j;

for(i=0;i<6;i++)
{j=*ptr;
  a[i]=distab[j];
  ptr++;
}
WriteAll_1621(0,a,6); //����ʼ��ַΪ0 ������д��5 ���ֽ�����

}
void show(unsigned char *ptr)
{
 unsigned char a[6];
unsigned char i,j;

for(i=0;i<6;i++)
{j=*ptr;
  a[i]=distab[j];
  ptr++;
}
if(a[1]==0xeb)
  {a[1]=0x00;
  if(a[2]==0xeb){
        a[2]=0x00;
        if(a[3]==0xeb){
        a[3]=0x00;
          if(a[4]==0xeb)
            a[4]=0x00;
        }
      }


  }
WriteAll_1621(0,a,6); //����ʼ��ַΪ0 ������д��5 ���ֽ�����

}
