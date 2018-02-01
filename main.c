#include  <msp430f5438a.h>  
#include <stdlib.h>
#include <string.h>
#include "menu_def.h"
#include "ht1621.h"    

//#define DEBUG






//#pragma location="INFO"
//__no_init static unsigned int Spra[256];


#pragma location="INFO"
__no_init static unsigned int fduanshu;
#pragma location="INFO"
__no_init static unsigned int fma4;
#pragma location="INFO"
__no_init static unsigned int fma20;
#pragma location="INFO"
__no_init static unsigned int fliangcheng;
#pragma location="INFO"
__no_init static unsigned int fyiwei;
#pragma location="INFO"
__no_init static unsigned int flvbo;

#pragma location="INFO"
__no_init static unsigned int fgeduanchangdu[14];
#pragma location="INFO"
__no_init static unsigned int fgeduandianrong[14];
#pragma location="INFO"
__no_init static unsigned int  fgeduanmenkan[14];

#pragma location="INFO"
__no_init static unsigned int   fgeduanse[15];
#pragma location="INFO"
__no_init static unsigned int   fgeduansf[15] ;

static unsigned int  duanshu=6;
static unsigned int  geduanchangdu[14]={3000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
static unsigned int  geduandianrong[14]={20,20,20,20,20,8,8,8,8,8,8,8,8,8};
static unsigned int  geduanmenkan[14]={300,200,200,200,200,15,15,15,15,15,15,15,15,15};
static unsigned int  geduanse[14]={10,10,10,10,10,10,10,10,10,10,10,10,10,10};
static unsigned int  geduansf[14]={1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
static unsigned int  ma4=910;
static unsigned int  ma20=59000;
static unsigned int  liangcheng=3000;
static unsigned int  yiwei=0x00;
static unsigned int  lvbo=100;
static unsigned char sym=0x00;


unsigned char disp_buffer[6];

unsigned char nomove;
unsigned char savesym;
unsigned int *changshuptr;





unsigned int cap[16];
void flash_write(unsigned int* address, unsigned int data);
void flash_erase( unsigned int* address) ;
void hextobcd(unsigned int hexs);
void anjian(void);






void flash_erase(unsigned int* address)             // Erase the addressed flash segment.
{
  unsigned int gie = _BIC_SR(GIE) & GIE;            // Disable interrupts.

  FCTL3 = FWKEY;                            // Unlock the flash.
  FCTL1 = FWKEY | ERASE;                    // Enable flash segment erase.
  *address = 0xff;                             // Erase the flash segment.
  FCTL1 = FWKEY;                            // Disable flash segment erase.
  FCTL3 = FWKEY | LOCK;                     // Lock the flash.
  _BIS_SR(gie);                             // Restore interrupts (to previous state).
}// flash_erase(word* address, data)

void flash_write(unsigned int* address,unsigned int data)  // Write the (integer) data to the addressed flash.
{
  unsigned int gie = _BIC_SR(GIE) & GIE;            // Disable interrupts.
  
  FCTL3 = FWKEY;                            // Unlock the flash.
  FCTL1 = FWKEY | WRT;                      // Enable flash write.
  *address = data;                        // Write the data to the flash.
  FCTL1 = FWKEY;                            // Disable flash write.
  FCTL3 = FWKEY | LOCK;                     // Lock the flash.
  _BIS_SR(gie);                             // Restore interrupts (to previous state).
}// flash_write(word* address, data)





void save(void)
{
  unsigned int i;
 
  flash_erase(&fduanshu);
  flash_erase(&fgeduansf[8]);
  
  flash_write(&fduanshu, duanshu);       // Intialize with ideal Vref value 2500mV
  flash_write(&fma4, ma4); 
  flash_write(&fma20, ma20); 
  flash_write(&fliangcheng, liangcheng); 
  flash_write(&fyiwei, yiwei); 
  flash_write(&flvbo, lvbo);   
  for(i=0;i<15;i++){ flash_write(&fgeduanchangdu[i],geduanchangdu[i]);}
  for(i=0;i<15;i++){ flash_write(&fgeduandianrong[i],geduandianrong[i]);}
  for(i=0;i<15;i++){flash_write( &fgeduanmenkan[i],geduanmenkan[i]);
      }
  
  for(i=0;i<15;i++){ flash_write(&fgeduanse[i],geduanse[i]);}
  for(i=0;i<15;i++){ flash_write(&fgeduansf[i],geduansf[i]);}
  
  yiwei=fyiwei;
  if(yiwei>=0x8000){yiwei&=0x7fff;sym=0xff;}
  else{sym=0;}
}


unsigned int calheight(void)
{
  unsigned long temp;
  unsigned int cp[14];
  unsigned int i;
//  unsigned int youliaoduan=0;
//  unsigned int cshield,clength;
 // unsigned int ma;
  //static unsigned char icnt=0;
  //static unsigned int levels[256];
  unsigned int height;
  
   unsigned int height1,height2;
   unsigned int height3,height4;
   unsigned int height5,height6;
    unsigned int height7,height8; 
//    unsigned int height9,height10;
//   unsigned int height11,height12;
//   unsigned int height13,height14;
  static unsigned int level=0;
  
  for(i=0;i<14;i++)
  {
    cp[i]=cap[i+1];
  }
  //减掉初值 
  for(i=0;i<14;i++)
  {
    if(cp[i]>geduandianrong[i])
    {
     cp[i]-=geduandianrong[i];
    }
    else cp[i]=0;
 //   if (cp[i]>geduanmenkan[i])youliaoduan=i;
  }
 
  //固定电容
   //计算高度1
  temp=cp[0];
  temp*=geduanchangdu[0];
  temp/=geduanmenkan[0];
  height1=temp;
  if(height1>geduanchangdu[0]){
    height1=geduanchangdu[0];
   }
   //计算高度2
  temp=cp[1];
  temp*=geduanchangdu[1];
  temp/=geduanmenkan[1];
  height2=temp;
  if(height2>geduanchangdu[1]){
    height2=geduanchangdu[1];
   }
   //计算高度3
  temp=cp[2];
  temp*=geduanchangdu[2];
  temp/=geduanmenkan[2];
  height3=temp;
  if(height3>geduanchangdu[2]){
    height3=geduanchangdu[2];
   }    
   //计算高度4
  temp=cp[3];
  temp*=geduanchangdu[3];
  temp/=geduanmenkan[3];
  height4=temp;
  if(height4>geduanchangdu[3]){
    height4=geduanchangdu[3];
   }  
   //计算高度5
  temp=cp[4];
  temp*=geduanchangdu[4];
  temp/=geduanmenkan[4];
  height5=temp;
  if(height5>geduanchangdu[4]){
    height5=geduanchangdu[4];
   }  
     //计算高度6
  temp=cp[5];
  temp*=geduanchangdu[5];
  temp/=geduanmenkan[5];
  height6=temp;
  if(height6>geduanchangdu[5]){
    height6=geduanchangdu[5];
   } 
       //计算高度7
  temp=cp[6];
  temp*=geduanchangdu[6];
  temp/=geduanmenkan[6];
  height7=temp;
  if(height7>geduanchangdu[6]){
    height7=geduanchangdu[6];
   }
     //计算高度8
  temp=cp[7];
  temp*=geduanchangdu[7];
  temp/=geduanmenkan[7];
  height8=temp;
  if(height8>geduanchangdu[7]){
    height8=geduanchangdu[7];
   }
 /*
     //计算高度9
  temp=cp[5];
  temp*=geduanchangdu[8];
  temp/=geduanmenkan[8];
  height9=temp;
  if(height9>geduanchangdu[8]){
    height9=geduanchangdu[8];
   }
     //计算高度10
  temp=cp[9];
  temp*=geduanchangdu[9];
  temp/=geduanmenkan[9];
  height10=temp;
  if(height10>geduanchangdu[9]){
    height10=geduanchangdu[9];
   }  
  */
  //计算高度偏移
   switch (duanshu)
   {
     case  1:        
     height=height1;
     break;
     case  2:        
     height=height1+height2;
     break; 
     case  3:        
     height=height1+height2+height3;
     break;
     case  4:        
     height=height1+height2+height3+height4;
     break;
     case  5:        
     height=height1+height2+height3+height4+height5;
     break;
     case  6:        
     height=height1+height2+height3+height4+height5+height6;
     break;
     case  7:        
     height=height1+height2+height3+height4+height5+height6+height7;
     break;
     case  8:        
     height=height1+height2+height3+height4+height5+height6+height7+height8;
      break;
     default:
     height=height1+height2+height3+height4+height5+height6+height7+height8;
      break;
   }  
 if(height>liangcheng)height=liangcheng;
 /* 
  height=0;
  if(youliaoduan<0x1)
  {
    cshield=geduanmenkan[0];    //第一段参考电容
    cshield<<=1;
    clength=geduanchangdu[0];    //满料长度  
   }
   else
   {
     cshield=cp[youliaoduan-1];    //有料下一段参考电容
     clength=geduanchangdu[youliaoduan-1]; //满料长度 
     
     if((cp[0]>geduanmenkan[1])&&(cp[0]<500))//记住第一段的值
     {
     geduanmenkan[0]=cp[0];
     geduanmenkan[0]>>=1;
     }
     
     for(i=0;i<youliaoduan;i++)
     {
     height+=geduanchangdu[i];
     }
     
    }
  //有料段
    temp=cp[youliaoduan];
    temp*=clength;
    temp/=cshield;
    if(temp>geduanchangdu[youliaoduan])temp=geduanchangdu[youliaoduan];
    temp+=height;
    height=temp;
  //无
    temp=cp[youliaoduan+1];
    temp*=clength;
    temp/=cshield;
    if(temp>geduanchangdu[youliaoduan+1])temp=geduanchangdu[youliaoduan+1];
    temp+=height;
    height=temp;
    if(height>liangcheng)height=liangcheng;
    
  //计算高度偏移
    temp=height;
    if(sym){
    if(temp>yiwei)temp-=yiwei;
    else temp=0;
    }
    else temp+=yiwei;
*/  
   //输出电流  
  
  //计算脉宽
  
    if((level>0)&&(lvbo>0))
    {
      if(height>(level+lvbo)) level+=lvbo;
      else if ((height+lvbo)<level)level-=lvbo;
      else level=height;
    }
    else level=height;
    
          
  temp=level;
  i=ma20;
  i-=ma4;
  temp*=i;
  temp/=liangcheng;
  temp+=ma4;
  
  
  
  if(temp>ma20)temp=ma20;
  i=temp;
  
  //滤波电流 
  
  
  
  

  

     TBCCR5=i;
    return(height);
}


void Init_Port(void)
  {
    P1DIR|=BIT4+BIT5+BIT6+BIT7;
    P2DIR|=BIT2; 
    P2SEL|=BIT2;
    
    P4DIR|=BIT5;
    P4SEL|=BIT5;
    P4DS|=BIT5;
    
    P5DIR|=BIT4+BIT5+BIT6+BIT7;
    P5SEL|=BIT2+BIT3;  
    P7DIR|=BIT2+BIT3;
    P7SEL|=BIT0+BIT1;
    P8DIR|=BIT0+BIT1+BIT2+BIT3+BIT4+BIT6+BIT7;
    P9DIR|=BIT0+BIT1;  
  }






        



//方波
void Init_TA1(void)
{  
  TA1CTL=TACLR;
  TA1R=0X00;
  TA1CCR0=1599;
  TA1CCR1=799;
  TA1CCTL1=OUTMOD0+OUTMOD1;
  TA1CTL=TASSEL1+MC0;  
}

//电流

void Init_TB0(void)
{ 
  TBCTL=0X0220;
  TBCCTL5=0X00e0;
  TBCCR5=ma4;
}
	/*
void Init_RTC(void)
{
  RTCCTL01 = RTCTEVIE + RTCSSEL_2 + RTCTEV_0; // Counter Mode, RTC1PS, 8-bit ovf
                                            // overflow interrupt enable
  RTCPS0CTL = RT0PSDIV_1;                   // ACLK, /8, start timer
  RTCPS1CTL = RT1SSEL_2 + RT1PSDIV_3;       // out from RT0PS, /16, start timer


}

*/


void Init_ADC12(void)

{
    /* Initialize REF module */
  // Enable 2.5V shared reference, disable temperature sensor to save power
 
  REFCTL0 |= REFMSTR+REFVSEL_1+REFON+REFTCOFF; 
    /* Initialize ADC12 */  
  ADC12CTL0 = ADC12ON+ADC12SHT02;  // Turn on ADC12, set sampling time
  ADC12CTL1 = ADC12SHP;            // Use sampling timer
  
//  ADC12MCTL0 = ADC12SREF_1;        // Vr+=Vref+ and Vr-=AVss
 
  __delay_cycles(75);                       // 75 us delay @ ~1MHz
  ADC12CTL0 |= ADC12ENC;                    // Enable conversions


}
/*

*/





   
  void  set_pra(void)
  {
    
    duanshu=6;
    ma4=910;
    ma20=53100;
    liangcheng=16000;
    yiwei=0;
    lvbo=100;
    sym=0x00; 
    
    
    geduanchangdu[0]=1000;
    geduanchangdu[1]=1000;
    geduanchangdu[2]=1000;
    geduanchangdu[3]=1000;
    geduanchangdu[4]=1000;
    geduanchangdu[5]=1000;
    geduanchangdu[6]=1000;
    geduanchangdu[7]=1000;
    geduanchangdu[8]=1000;
    geduanchangdu[9]=1000;
    geduanchangdu[10]=1000;
    geduanchangdu[11]=1000;
    geduanchangdu[12]=1000;
    geduanchangdu[13]=1000;
    
    geduandianrong[0]=70;
    geduandianrong[1]=70;
    geduandianrong[2]=70;
    geduandianrong[3]=70;
    geduandianrong[4]=70;
    geduandianrong[5]=70;
    geduandianrong[6]=70;
    geduandianrong[7]=70;
    geduandianrong[8]=70;
    geduandianrong[9]=70;
    geduandianrong[10]=70;
    geduandianrong[11]=70; 
    geduandianrong[12]=70;
    geduandianrong[13]=70;
     
    geduanmenkan[0]=30;
    geduanmenkan[1]=30;
    geduanmenkan[2]=30;
    geduanmenkan[3]=30;
    geduanmenkan[4]=30;
    geduanmenkan[5]=30;
    geduanmenkan[6]=30;
    geduanmenkan[7]=30;
    geduanmenkan[8]=30;
    geduanmenkan[9]=30;
    geduanmenkan[10]=30;
    geduanmenkan[11]=30;
    geduanmenkan[12]=30;
    geduanmenkan[13]=30;
    
    
    geduanse[0]=10;
    geduanse[1]=10;
    geduanse[2]=10;
    geduanse[3]=10;
    geduanse[4]=10;
    geduanse[5]=10;
    geduanse[6]=10;
    geduanse[7]=10;
    geduanse[8]=10;
    geduanse[9]=10;
    geduanse[10]=10;
    geduanse[11]=10;
    geduanse[12]=10;
    geduanse[13]=10;
    
    geduansf[0]=1000;
    geduansf[1]=1000;
    geduansf[2]=1000;
    geduansf[3]=1000;
    geduansf[4]=1000;
    geduansf[5]=1000;
    geduansf[6]=1000;
    geduansf[7]=1000;
    geduansf[8]=1000;
    geduansf[9]=1000;
    geduansf[10]=1000;
    geduansf[11]=1000;
    geduansf[12]=1000;
    geduansf[13]=1000;
    
   

  }
  

      
  /////////////////////
  
  /////设置各段初始值


  


void check_cal(void)                        // Check if INFO memory blank or contains calibration constants
{
  unsigned int j;


  if (fduanshu == 0xffff)               // Check if Flash INFO Refcal erased?
  {
  //  set_pra();
    save();
  } 
  
  duanshu=fduanshu;
  for(j=0;j<14;j++){ geduanchangdu[j]=fgeduanchangdu[j];   }
  for (j=0;j<14;j++){geduandianrong[j]=fgeduandianrong[j];}
  for(j=0;j<14;j++){geduanmenkan[j]=fgeduanmenkan[j];}
  for(j=0;j<14;j++){geduanse[j]=fgeduanse[j];}
  for(j=0;j<14;j++){geduansf[j]=fgeduansf[j];}
  ma4=fma4;
  ma20=fma20;
  liangcheng=fliangcheng;
  lvbo=flvbo;
  yiwei=fyiwei;
  if(yiwei>=0x8000){yiwei&=0x7fff;sym=0xff;}
  else{sym=0;}
  if(duanshu>14)duanshu=14;
  if(lvbo>200)lvbo=200;
} 
   
void main( void )
{
  //unsigned char i;
  unsigned int j,ui;
  unsigned long ltemp;
  unsigned int cap0=0;
  unsigned int capref=0;
  unsigned char chan=0;
  unsigned int gaodu;
  WDTCTL = WDTPW + WDTHOLD;
   Init_Port();
   __bis_SR_register(SCG0);
  UCSCTL6 &= ~XT2OFF;                     
  UCSCTL3 |= SELREF_2;                                                                                                                                           
  UCSCTL4 |= SELA_2;                       
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }
  while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                            // expected frequency
  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2 /
  P7SEL |= 0x03;                            // Select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap 
  __delay_cycles(600000);
  __delay_cycles(600000);
  
  
 LCD_INIT();  
 check_cal();
 Init_TA1();
 Init_TB0();
 Init_ADC12();
 
 while(1)
    {
  //NC    
   CLR_SC0();
  CLR_SC1();
  CLR_SC2();
  CLR_SC3();
  CLR_SC4();
  CLR_SC5();
  CLR_SC6();
  CLR_SC7();
  CLR_SC8();
  CLR_SC9();
  CLR_SC10();
  CLR_SC11();
  CLR_SC12();
  CLR_SC13();
  CLR_SC14();
  CLR_SC15();
   __delay_cycles(400000);
  ltemp=0;
  for(j=0;j<0x1000;j++)
  {
    ADC12CTL0 |= ADC12SC; 
    while (!(ADC12IFG & BIT0));
    ltemp+=ADC12MEM0;
   }
      ltemp>>=12;
      cap[15]=ltemp; 

     
      if(cap0==0)
      {
        cap0=cap[15];
        cap0<<=4;
      }                              //cap0存储前几次的平均值
      else 
      {
       ltemp=cap0;
      ltemp*=15;   ////滤波,16次平均
      cap[15]<<=4;
      ltemp+=cap[15];
      ltemp>>=4;
      cap0=ltemp;
      cap[15]=cap0;
      cap[15]>>=4;
      }
           
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

  ///REF        
       SET_SC1();
      __delay_cycles(400000);

       ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;  
      cap[0]=ltemp; 
      
   
   if(capref==0)
   {
     capref=cap[0];
     capref<<=4;
    }
    else 
    {
     ltemp=capref;
     ltemp*=15;   //16次平均值 
      cap[0]<<=4;
      ltemp+=cap[0];
      ltemp>>=4;
      capref=ltemp;
      cap[0]=capref;
      cap[0]>>=4;
     }    
      
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

 ////  1
   
      CLR_SC1();
      SET_SC2();
     __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[1]=ltemp; 
       
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

 //    2 
    CLR_SC2();
    SET_SC3();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[2]=ltemp;   
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

  //   3  
    CLR_SC3();
    SET_SC4();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[3]=ltemp;       
          
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

   // 4    
    CLR_SC4();
    SET_SC5();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[4]=ltemp;     
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

  //   5  
    CLR_SC5();
    SET_SC6();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[5]=ltemp;     
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    
 
  //   6  
    CLR_SC6();
    SET_SC7();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[6]=ltemp;     
             
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    
     
  //   7  
    CLR_SC7();
    SET_SC8();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[7]=ltemp;  
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

    // 8    
    CLR_SC8();
    SET_SC9();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[8]=ltemp;    
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

      //   9 
       CLR_SC9();
    SET_SC10();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[9]=ltemp;   
            
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

      
       //  10  
       CLR_SC10();
    SET_SC11();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[10]=ltemp;     
      
      
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

     //   11 
       CLR_SC11();
    SET_SC12();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[11]=ltemp;    
      
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

    //   12 
       CLR_SC12();
    SET_SC13();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[12]=ltemp;  
          
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    
  
    //   13 
       CLR_SC13();
    SET_SC14();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[13]=ltemp;  
           
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    
 
    //   14 
       CLR_SC14();
    SET_SC15();
 __delay_cycles(400000);
   
      ltemp=0;
      for(j=0;j<0x1000;j++)
      {
      ADC12CTL0 |= ADC12SC; 
      while (!(ADC12IFG & BIT0));
      ltemp+=ADC12MEM0;
      }
      ltemp>>=12;
      cap[14]=ltemp;  
      
      
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    

    if(cap[0]<=cap[15])
    {
      ui=1200;
    }
     else
     {
    ui=cap[0];
    ui-=cap[15];
     }    
  for(j=1;j<15;j++)
    {
      ltemp=cap[j];
      if(cap[j]<cap[15])ltemp=0;
      else ltemp-=cap[15];
      ltemp*=1000;
      ltemp/=ui;
      if(ltemp>4000)ltemp=4000;  //最大值1000
      cap[j]=ltemp;
    } 
    gaodu=calheight();
   if(chan==0)
   { hextobcd(cap[15]);
    disp_buffer[0]=0;
   }
    else if(chan==1)
   { hextobcd(cap[0]);
    disp_buffer[0]=16;
   }
    else if(chan<(duanshu+2))
   {
     hextobcd(cap[chan-1]);
     if(chan<=10) 
     {
       disp_buffer[0]=chan-1;
     }
   else
   {disp_buffer[0]=chan;
   }
   }
   
   else if (chan==(duanshu+2))
   {
    hextobcd(gaodu);
    disp_buffer[0]=18;
   }
     chan++;
     if(chan>(duanshu+2))chan=0;
    show(disp_buffer);
    anjian();  
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif    
    
        
      }
   

}








void  displaycs(unsigned char vola,unsigned char volc)
{

switch(vola){
case 0:	      hextobcd(geduanmenkan[volc]);
	      changshuptr=geduanmenkan;
               
	    break;
case 1:	
		hextobcd(geduanchangdu[volc]);
		changshuptr=geduanchangdu;
                
        break;
case 2:	
		hextobcd(geduandianrong[volc]);
		changshuptr=geduandianrong;
	      break;
case 3:	
		hextobcd(duanshu);
		changshuptr=&duanshu;
	  break;
case 4:	
		hextobcd(ma4);
                changshuptr=&ma4;		
      break;
case 5:	
	  hextobcd(ma20);
		changshuptr=&ma20;
      break;
case 6:	
		hextobcd(liangcheng);
		changshuptr=&liangcheng;
	      break;
case 7:	
		hextobcd(yiwei);
                if(sym)disp_buffer[1]=40;
                else disp_buffer[1]=0x0;
                changshuptr=&yiwei;
                break;
case 8:	
		hextobcd(lvbo);
		changshuptr=&lvbo;
      break;
      
 case 9:	
		//hextobcd(ma4b);
                //changshuptr=&ma4b;		
      break;
case 10:	
		//hextobcd(ma20b);
		//changshuptr=&ma20b;
      break;     
      
default:break;



}
	//disp_buffer[]
}








void nosave(unsigned char  ddshu)
{ 
 unsigned char nsadata[6]={24,5,11,0xa,0xa,0xa};
  display(&nsadata[0]);  
  nomove=0;
  savesym=0;
}

void yessave(unsigned char ddshu){
  unsigned char sadata[6]={5,11,0xa,0xa,0xa,0xa};
  display(sadata); 
  nomove=0;
  savesym=1;
}



void hextobcd(unsigned int hexs) {
unsigned int va;
unsigned char i;
    va = 10000;                             //最大数级万位
    for     (i=1;i<6;i++) {
        disp_buffer[i] = 0;                 //目标数组清零
        while ((hexs>=va)&&(va>9)) {
            hexs -= va;                     //减除数
            disp_buffer[i]++;               //商位加1
        }
        va /= 10;                           //除数除10，指向低一位
    }
    disp_buffer[5]=hexs;                    //最后个位数
}







void anjian(void)
{	unsigned char upon;
	unsigned char tim=10;

	unsigned long i,j;
	unsigned char vola,volb,volc,vold;
     //ef各段门槛
     //cd各段长度
     //ca各段初值
     //d5设置段数（1~14)   
     //4a
     //20a
     // LC量程
     //LA移位
     //LB滤波
     //sE
     //sF
        
     //恢复出厂值
 unsigned char caidan[12][6]=
                    {   {15,16,0x0A,0x0A,0x0A,0x0A},
                        {13,14,0x0A,0x0A,0x0A,0x0A},
                        {13,11,0x0A,0x0A,0x0A,0x0A},
                        {14,0x5,0xA,0xA,0xA,0xA},
                        {0X4,11,0xA,0x0A,0x0A,0x0A},
                        {0X2,0X0,11,0x0A,0x0A,0x0A},
                        {22,13,0xA,0x0A,0x0A,0x0A},
                        {22,11,0xA,0x0A,0x0A,0x0A},
                        {22,12,0xA,0x0A,0x0A,0x0A},
                        {0X5,15,0xA,0x0A,0x0A,0x0A},
                        {0X5,16,0xa,0x0A,0x0A,0x0A},
                        {24,0x5,0xb,0x0A,0x0A,0x0A}
                      };

 
 

	upon=P1IN&0Xe;
	nomove=1;
        vola=0;
	if (upon==0)
	{
		//lcd_init(); 
		//display_setup();
	j=0x00;          
	while(upon==0)
	{	
	upon=P1IN&0Xe;
	if((j++)>0x9000)
	{
	  disp_buffer[0]=10;
          disp_buffer[1]=10;                  
          display(&caidan[vola][0]);	
	  j=0x00;
	  while(j<0x8fff)
	  { 
	   upon=P1IN&0Xe;
	  if(upon==0xe)j++;
	   else j=0x00;
	  }			//等待按键松开
        //选择菜单项
        //各段门槛
        //各段长度
        //各段电容
        //段数
        //4maa
        //20maa
        //量程
        //移位
        //滤波
        //4mab
        //20mab
	volb=0xff;
	while(volb)				//VOLB 
	{
	if(SUP==0)				//KEY a 
	{	
        #ifndef  DEBUG    
        WDTCTL =  WDTPW + 0x9;
        #endif   
	  if(++vola>=12)vola=0;
	  display(&caidan[vola][0]);
	//按键松开
	  j=0x00;
          while(j<0x8fff)
	  {
	    if(SUP!=0X00)j++;
	    else j=0x00;
	  }
        }                      
	if(ENTER==0)
        {
          #ifndef  DEBUG    
          WDTCTL =  WDTPW + 0x9;
          #endif 
          
          tim=1;
	  volb=0;
          volc=0;
	  displaycs(vola,volc);	
          if(vola<3) disp_buffer[0]=0x1;
	  vold=0x01;
          display(disp_buffer);
	  j=0x00;
          if(vola==0x4)TBCCR5=ma4;
          else if(vola==0x5)TBCCR5=ma20;//////////////////                              
          if(vola==0xb)WDTCTL = 0x9;
          while(j<0x8fff)
	  {	
	  if(ENTER!=0)j++;
	  else j=0x00;
	  }
	}
    }//无超时退出？
    i=0;
    while(1)
    {
      //闪烁  
      if(nomove)
      {  
       i++;
       if(i>0x20000)
       {
          if(disp_buffer[vold]==0xa)
          {
            disp_buffer[vold]=volb;
            i=0;
          }
      else
       {
          i=0x000;
          volb=disp_buffer[vold];
          disp_buffer[vold]=0xa;
       }
        display(disp_buffer);
       }
      }
       //闪烁          
      
      
      if(SDWN==0)//键按下
      {
          #ifndef  DEBUG    
          WDTCTL =  WDTPW + 0x9;
          #endif 
        
	if(nomove)
	{
          if(disp_buffer[vold]==0xa)disp_buffer[vold]=volb;
	   vold++;
	  if(vold>5)vold=1;
  //	send_command(vold);
	}	//显示移位		
        else if(savesym)
        {              
           if(sym)yiwei|=0x8000;
           // else yiwei&=0x7fff;    
           save();    
           WDTCTL =   0x9;
           while(2);
          
	}//保退出
      else {    
             WDTCTL =   0x9; 
            while(2);
             }//不保存退出
      j=0x00;
      while(j<0x8fff)
      {
	if(SDWN!=0X00)j++;
	else j=0x00;
      }//等待键松开
      }
      
      
      
      if(ENTER==0)
      {          

          #ifndef  DEBUG    
          WDTCTL =  WDTPW + 0x9;
          #endif 
	unsigned char ddshu;
	//菜单切换
	volc++;
	switch(vola)	//vola 子菜单值
	{
          case 0:           //各段门槛
            if(volc>(duanshu+1)){volc=0;}
	    if (volc==duanshu)
	    {
	      //send_command(0x90);
	      //send_data(0x4a);
	      ddshu=duanshu;
	      ddshu+=1;
	      nosave(ddshu);
	    }//不保存退出
	   if (volc==duanshu+1)
	    {
	    //send_command(0x90);
	    //send_data(0x4a);
	    ddshu=duanshu;
	    ddshu+=2;
	    yessave(ddshu);
            } //保存退
	    if (volc<duanshu)
	    {
	      hextobcd(geduanmenkan[volc]); //显示菜单值
              disp_buffer[0]=volc;
              disp_buffer[0]++;
              if (disp_buffer[0]>9)disp_buffer[0]++;
              display(disp_buffer);
              changshuptr=&geduanmenkan[volc];///////////////////////////////////////////
	      nomove=1;
	     }
	    break;

    case 1://各段长度 
            if(volc>(duanshu+1)){volc=0;}
            if (volc==duanshu)
	    {
	      //send_command(0x90);
	      //send_data(0x4c);
	      ddshu=duanshu;
	      ddshu+=1;
	      nosave(ddshu);
	    }//不保存退出
	    if (volc==duanshu+1)
	    {
	    //send_command(0x90);
	    //send_data(0x4c);
	    ddshu=duanshu;
	    ddshu+=2;
	    yessave(ddshu);
	    } //保存退
	    if (volc<duanshu)
	    {
	      hextobcd(geduanchangdu[volc]);
              disp_buffer[0]=volc;
              disp_buffer[0]++;
              if (disp_buffer[0]>9)disp_buffer[0]++;
              display(disp_buffer);
	      changshuptr=&geduanchangdu[volc];////////////////////////////////////////////////								////////////////////////////////////
              nomove=1;
	    }
	    break;
	    case 2:
            if(volc>(duanshu+1)){volc=0;}
	    if (volc==duanshu)
	    {
	      //send_command(0x90);
	      //send_data(0x56);
	      ddshu=duanshu;
	      ddshu+=1;
	      nosave(ddshu);
	      }//不保存退出
	    if (volc==duanshu+1)
            {
	      //send_command(0x90);
	      //send_data(0x56);
	      ddshu=duanshu;
	      ddshu+=2;
	      yessave(ddshu);
	    } //保存退
	    if (volc<duanshu)
	    {
	      hextobcd(geduandianrong[volc]);
              disp_buffer[0]=volc;
              disp_buffer[0]++;
              if (disp_buffer[0]>9)disp_buffer[0]++;
              display(disp_buffer);
	      //display_bcd(0x56,(volc+1));
	      //send_command(0x91);
	      changshuptr=&geduandianrong[volc];////////////////////////////////////////////////
	     // changshu=0x1;///////////////////////////////////////////////////////////////////
	      nomove=1;
	    }
	    break;
            
            case 3:
              if(volc>2){volc=0;}					
              if (volc==1)
		{
	        //send_command(0x90);
		//send_data(0x4e);
		nosave(0x1);
		}//不保存退出
	      if (volc==2)
		{
		//send_command(0x90);
		//send_data(0x4e);
		yessave(0x02);
		} //保存退
	      if (volc==0x00)
		{
	           hextobcd(duanshu);
                   disp_buffer[0]=0xa;
		   display(disp_buffer);
                   changshuptr=&duanshu;
		   nomove=1;
		}
	  break;
          
	case 4:
          if(volc>2){volc=0;}
	  TBCCR5=ma4;
	  if (volc==1)
	{
	//send_command(0x90);
	//send_data(0x41);
	nosave(0x4);
	}//不保存退出
	if (volc==2)
	{
	//send_command(0x90);
	// send_data(0x41);
	  yessave(0x04);
	} //保存退
	if (volc==0x00)
	{
	  hextobcd(ma4);
          disp_buffer[0]=0xa;
	  display(disp_buffer);
          changshuptr=&ma4;
          nomove=1;
	}
	  break; 
          
	case 5:
          if(volc>2){volc=0;}
	  TBCCR5=ma20;
	  if (volc==1)
	  {
	    //send_command(0x90);
	    //send_data(0x41);
	    nosave(0x14);
	  }//不保存退出
	  if (volc==2)
	{
	//send_command(0x90);
	//send_data(0x41);
	  yessave(0x14);
	} //保存退
	if (volc==0x00)
	{
	  hextobcd(ma20);
          disp_buffer[0]=0xa;
	  display(disp_buffer);
	  changshuptr=&ma20;//////////////											//		dianliu_shuchu(ma20);
          nomove=1;
	}
	break;
	
	case 6:
        if(volc>2){volc=0;}
        if (volc==1)
	{
	//send_command(0x90);
	nosave(0x1);
	}//不保存退出
	if (volc==2)
	{
	//send_command(0x90);
	//send_data(0x53);
	yessave(0x2);
	} //保存退
	if (volc==0x00)
	{
	  hextobcd(liangcheng);
          disp_buffer[0]=0xa;
	  display(disp_buffer);
	  changshuptr=&liangcheng;////////////////////////////////////////////////
          nomove=1;
	}
	break;
	
	case 7:
        if(volc>2){volc=0;}
	if (volc==1)
	{
	//send_command(0x90);
	//send_data(0x44);
	nosave(0x1);
	}//不保存退出
	if (volc==2)
	{
	//send_command(0x90);
	//send_data(0x44);
	yessave(0x2);
	} //保存退
	if (volc==0x00)
	{
	hextobcd(yiwei);
        disp_buffer[0]=0xa;
        if(sym)disp_buffer[1]=40;
        else disp_buffer[1]=0x00;
	display(disp_buffer);
        changshuptr=&yiwei;////////////////////////////////////////////////
	nomove=1;
	}
	break;	
        
	case 8:
        if(volc>2){volc=0;}
	if (volc==1)
	{
	//send_command(0x90);
	//send_data(0x46);
	nosave(0x1);
	}//不保存退出
	if (volc==2)
	{
	//send_command(0x90);
	//send_data(0x46);
	yessave(0x2);
	} //保存退
        if (volc==0x00)
	{
	hextobcd(lvbo);
        disp_buffer[0]=0xa;
	display(disp_buffer);
	changshuptr=&lvbo;////////////////////////////////////////////////
	nomove=1;
	}
	break;
                                                    
        case 9:
           if(volc>(duanshu+1)){volc=0;}
            if (volc==duanshu)
	    {
	      //send_command(0x90);
	      //send_data(0x4c);
	      ddshu=duanshu;
	      ddshu+=1;
	      nosave(ddshu);
	    }//不保存退出
	    if (volc==duanshu+1)
	    {
	    //send_command(0x90);
	    //send_data(0x4c);
	    ddshu=duanshu;
	    ddshu+=2;
	    yessave(ddshu);
	    } //保存退
	    if (volc<duanshu)
	    {
	      hextobcd(geduanse[volc]);
              disp_buffer[0]=volc;
              disp_buffer[0]++;
              if (disp_buffer[0]>9)disp_buffer[0]++;
              display(disp_buffer);
	      changshuptr=&geduanse[volc];////////////////////////////////////////////////								////////////////////////////////////
              nomove=1;
	    }
	    break;
        
	case 10:
          if(volc>(duanshu+1)){volc=0;}
            if (volc==duanshu)
	    {
	      //send_command(0x90);
	      //send_data(0x4c);
	      ddshu=duanshu;
	      ddshu+=1;
	      nosave(ddshu);
	    }//不保存退出
	    if (volc==duanshu+1)
	    {
	    //send_command(0x90);
	    //send_data(0x4c);
	    ddshu=duanshu;
	    ddshu+=2;
	    yessave(ddshu);
	    } //保存退
	    if (volc<duanshu)
	    {
	      hextobcd(geduansf[volc]);
              disp_buffer[0]=volc;
              disp_buffer[0]++;
              if (disp_buffer[0]>9)disp_buffer[0]++;
              display(disp_buffer);
	      changshuptr=&geduansf[volc];////////////////////////////////////////////////								////////////////////////////////////
              nomove=1;
	    }
	    break;
		
      default:
        break;													   
        }       
        
        j=0x00;
	while(j<0x8fff)
	{
          if(ENTER!=0X00)j++;
	  else j=0x00;
	}//等待键松开
        
	vold=0X1;
  }	
			
  if((SUP==0)&&(nomove==1))
    {
           #ifndef  DEBUG    
          WDTCTL =  WDTPW + 0x9;
          #endif 
	//vold闪烁位
	if((vola==0x7)&&(vold==0x1))  //，显示移位时，正负号特殊情况
	{
	//send_data(0xa3);			
          if(sym){sym=0x00;disp_buffer[1]=0x00;}
          else {sym=0xff;disp_buffer[1]=40;}
	  display(disp_buffer);
	}
      else
	{
          if(disp_buffer[vold]==0xa)//移位
         {
           volb++;		//显示缓存区数据 ，闪烁位加1
	  if((volb>0x6)&&(vold==1))   //万位数据大于6，变成0
	  {
	    volb=0x00;
	    }			  //参数减少60000；
	  if(volb>0x9)//其它位大于9，变为0
	  {
	    volb=0x0;
	  }
          disp_buffer[vold]=volb;
          if(vola==0x7)
          {
            *changshuptr =1000*disp_buffer[2]+100*disp_buffer[3]+10*disp_buffer[4]+disp_buffer[5];
           }
	  else 
           {
            *changshuptr =10000*disp_buffer[1]+1000*disp_buffer[2]+100*disp_buffer[3]+10*disp_buffer[4]+disp_buffer[5];
            }                               
           disp_buffer[vold]=0xa;
           }
           else
	    {
                (disp_buffer[vold])++;		//显示缓存区数据 ，闪烁位加1
		if(((disp_buffer[vold])>0x6)&&(vold==1))   //万位数据大于6，变成0
		{
		disp_buffer[(vold)]=0x00;
                 }					//参数减少60000；
		else if((disp_buffer[vold])>0x9)//其它位大于9，变为0
		{
		disp_buffer[(vold)]=0x0;
		}			
                if(vola==0x7)
                {
                  *changshuptr =1000*disp_buffer[2]+100*disp_buffer[3]+10*disp_buffer[4]+disp_buffer[5];
                 }
		else 
                 {
                   *changshuptr =10000*disp_buffer[1]+1000*disp_buffer[2]+100*disp_buffer[3]+10*disp_buffer[4]+disp_buffer[5];
                  }
              }
                                                          
		display(disp_buffer);
	  }
				
	if(vola==4)TBCCR5=ma4;
	else if(vola==5)TBCCR5=ma20;
                            
                                        
	j=0x00;
	while(j<0x2fff)
	{	
         if(SUP!=0X00)j++;
	else j=0x00;
	}
	}
					//超时退出
	}
	
      }
        
        else
	{	
	i=0x10000;			//键同时按下，等待
	i-=j;
	if((i%0x1000)==0)
	{	
	tim--;
	//command_data=0x87; 
	//send_command(command_data); /*把显示地址设为0X94*/
	//send_data(tim);
        hextobcd(tim);
        disp_buffer[0]=0xa; 
        disp_buffer[1]=0xa; 
        disp_buffer[2]=0xa;
        disp_buffer[3]=0xa; 
        display(disp_buffer);
      }
		}


	}

	
	}

  	else {
          return;
        }
}





