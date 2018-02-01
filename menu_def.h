






////////////////////////////////////
//选通模拟开关 
#define SET_SC0()        P5OUT&=~BIT4
#define CLR_SC0()        P5OUT|=BIT4

#define SET_SC1()        P5OUT&=~BIT5
#define CLR_SC1()        P5OUT|=BIT5

#define SET_SC2()        P5OUT&=~BIT6
#define CLR_SC2()        P5OUT|=BIT6


#define SET_SC3()        P5OUT&=~BIT7
#define CLR_SC3()        P5OUT|=BIT7


#define SET_SC4()        P7OUT&=~BIT2
#define CLR_SC4()        P7OUT|=BIT2

#define SET_SC5()        P7OUT&=~BIT3
#define CLR_SC5()        P7OUT|=BIT3





#define SET_SC6()        P8OUT&=~BIT0
#define CLR_SC6()        P8OUT|=BIT0


#define SET_SC7()        P8OUT&=~BIT1
#define CLR_SC7()        P8OUT|=BIT1

#define SET_SC8()        P8OUT&=~BIT2
#define CLR_SC8()        P8OUT|=BIT2





#define SET_SC9()        P8OUT&=~BIT3
#define CLR_SC9()        P8OUT|=BIT3
#define SET_SC10()        P8OUT&=~BIT4
#define CLR_SC10()        P8OUT|=BIT4
#define SET_SC11()        P8OUT&=~BIT5
#define CLR_SC11()        P8OUT|=BIT5





#define SET_SC12()        P8OUT&=~BIT6
#define CLR_SC12()        P8OUT|=BIT6
#define SET_SC13()        P8OUT&=~BIT7
#define CLR_SC13()        P8OUT|=BIT7

#define SET_SC14()        P9OUT&=~BIT0
#define CLR_SC14()        P9OUT|=BIT0
#define SET_SC15()        P9OUT&=~BIT1
#define CLR_SC15()        P9OUT|=BIT1








__ro_placement const  volatile unsigned char 
            selIndex[]=
                      {
                       0x10,0x00,0x20,0x01,0x30,0x11,0x31,0x21, 
                      // 0x10,0x00,0x20,0x01,0x30,0x11,0x31,0x21,
                       0x02,0x22,0x12,0x32,0x13,0x03,0x23,0x04,
                       0x33,0x14,0x34,0x24,0x05,0x25,0x15,0x35,
                       0x16,0x06,0x26,0x07,0x36,0x17,0x37,0x27,
                       0x08,0x28,0x18,0x38,
                       
                       0x70,0x50,0x60,0x40,
                       0x61,0x71,0x51,0x72,
                       0x41,0x62,0x42,0x52,
                       0x73,0x53,0x63,0x43,
                       0x64,0x74,0x54,0x75,
                       0x44,0x65,0x45,0x55,
                       0x76,0x56,0x66,0x46,
                       0x67,0x77,0x57,0x78,
                       0x47,0x68,0x48,0x58,   
                        
                       0x10,0x00,0x20,0x01,0x30,0x11,0x31,0x21,
                       0x02,0x22,0x12,0x32,0x13,0x03,0x23,0x04,
                       0x33,0x14,0x34,0x24,0x05,0x25,0x15,0x35,
                       0x16,0x06,0x26,0x07,0x36,0x17,0x37,0x27,
                       0x08,0x28,0x18,0x38,
                         0x70,0x50,0x60,0x40,
                       0x61,0x71,0x51,0x72,
                       0x41,0x62,0x42,0x52,
                       0x73,0x53,0x63,0x43,
                       0x64,0x74,0x54,0x75,
                       0x44,0x65,0x45,0x55,
                       0x76,0x56,0x66,0x46,
                       0x67,0x77,0x57,0x78,
                       0x47,0x68,0x48,0x58                        
                         
                      };




__ro_placement const  volatile 
unsigned int  tmint[]={
      64166  , // 11*3.5*8000000/1200/4,
      13750 ,//11*1.5*8000000/1200/4,
      
};
