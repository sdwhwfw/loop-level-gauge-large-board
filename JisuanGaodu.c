#include "menu_def.h"




void hanshui(void)
  { 
    unsigned long ltemp;
    unsigned int imc[144]={0,};
    unsigned int  imax,i,j;
    unsigned char ci,cw;
    static unsigned int iwater=0;
    if(iwater<IWATER)iwater=IWATER;
    
    
 //   tptr=ptr;

   //��һ��ֵ����ˮ�ż�ֵ
 
/*
    cap[1]=899;
     cap[2]=299;
     cap[3]=299;
 cap[4]=199;
  cap[5]=199;
  cap[6]=89;
  cap[7]=89;  
  cap[8]=99;
  cap[9]=89;
  cap[10]=89; 
  cap[11]=99;
  cap[12]=99;
  cap[13]=99;
 cap[14]=99;
  cap[15]=99;
  cap[16]=89;
  cap[17]=89;  
  cap[18]=99;
  cap[19]=89;
  cap[20]=59; 
  cap[21]=54;
  cap[22]=29;
  cap[23]=29;
 cap[24]=26;
  cap[25]=30;
  cap[26]=29;
  cap[27]=9;  
  cap[28]=9;
  cap[29]=9;
  cap[30]=9; 
  
  */
  /////���㺬ˮ�� 
  //��һ��  
  //ȷ����ˮ��ֵ
      
    imax=cap[duanshu];
    if(imax>VKONGQI)imax=VKONGQI; ///�������ֵ�������󱨾�?
    
    for(ci=1;ci<=duanshu;ci++)     //���μ�������ֵ
    {
    imc[ci]=cap[ci];
    if(imc[ci]>imax)imc[ci]-=imax;
    else imc[ci]=0;                    
    }
    
     //������һ��ֵ 
    ltemp=imc[1];
    ltemp*=ratio;
    ltemp/=10000;
    if(ltemp>6000)ltemp=6000;
    imc[1]=ltemp;
/////////////////////////////////
    
    tempi=hanshui[145];   //hanshui[145]ˮλ�߶�
    tempi/=2;
    if(tempi>duanchangdu) //��һ�δ�ˮֵ 
      {
        imax=imc[1];
        iwater=imax;
      }
      else imax=iwater;   //��ˮֵ
    
      if(imax<IWATER)
        {
        iwater=IWATER;
        }
   //////////////////////////////////////// 
      //1000Ϊ���� ���ι�һ��   
      for(ci=1;ci<=duanshu;ci++)
      { 
      ltemp=imc[ci];
      ltemp*=1000;
      ltemp/=imax;
      hanshui[ci]=ltemp;
      }
      
      
      
//���㺬ˮ�� 
      /*
      ���ε�ֵ���趨��ˮ�ʱ�Ƚϡ�
      �жϺ�ˮ�ʵķ�Χ��
      ����ģ����㺬ˮ��
      */
   
        for(j=1;j<=duanshu;j++)
    {
      cw=0;
      for(i=65;i<86;i++)      //�洢���Ĵ洢��ˮֵ65
      {
      if (hanshui[j]>=Spra[i])
        cw=i;
      }
      if (cw==0)              //����
      {
      hanshui[j]=0;
      }                               
     // else if(cw==65)
      //{
       // hanshui[j]=1;
      //}
      else if(cw==85)        ///��ˮ
      {
       hanshui[j]=1000;
      }
      else 
      {
        /*ǧ�������㺬ˮ��
         ��ĳ�ι�һ������ֵ-�¶κ�ˮ�ʶ�Ӧֵ��*50/���Ϻ�ˮ�ʶ�Ӧֵ-�º�ˮ�ʶ�Ӧֵ��+�º�ˮ��
        */
        imax=Spra[cw+1];      //��֤�趨�ĺ�ˮ��˳������ݵ���
        if (imax>Spra[cw])
        {
          imax-=Spra[cw];
          ltemp=hanshui[j];
          ltemp-=Spra[cw];
          ltemp*=50;
          ltemp/=imax;
          
          imax=cw;
          imax-=65;
          imax*=50;
          ltemp+=imax;
          imax=ltemp;
          if(imax==0)imax=1;
          hanshui[j]=imax;
        }
        else hanshui[j]=1000;
         
      }
    }
    /////////////////////////////////////////////
  // ����ˮλ�߶�
  //  ptr=tptr;
 /*   for(ci=1;ci<=duanshu;ci++)
    {
    imc[ci]=hanshui[ci];
    }
   */ 
     cw=0;
    for(ci=1;ci<=duanshu;ci++)
    {
     if(hanshui[ci]>=zxcengcha)cw=ci;
    }
    if(cw)
    {
    ltemp=imc[cw+1];  
    ltemp*=duanchangdu;
    ltemp/=imc[cw];
    imax=ltemp;
    ltemp=cw;  
    ltemp*=duanchangdu;
    ltemp+=imax;
    }
    else
    {
      ltemp=imc[1];
      ltemp*=duanchangdu;
      ltemp/=iwater;
    }
    
    
    imax=xiuzhengzhi;
    if(imax&0x8000)
    {
    imax&=0x7fff;
    if(ltemp<=imax)ltemp=0;
    else ltemp-=imax;
    }
    else
    {
      ltemp+=imax;
    }
    imax=ltemp;
  
     hanshui[145]=imax;
     cap[145]=imax;
     
     
    
    ///////////////////////////////////////////
    
// �����ϴ��߶�
  

    cw=0; 
    for(ci=1;ci<=duanshu;ci++)
    {
     if(hanshui[ci]>=zshcengcha)cw=ci;
    }   
    if(cw)
    {
    ltemp=imc[cw+1];  
    ltemp*=duanchangdu;
    ltemp/=imc[cw];
    imax=ltemp;
    ltemp=cw;  
    ltemp*=duanchangdu;
    ltemp+=imax;
    
    
    imax=xiuzhengzhi;
    if(imax&0x8000)
    {
    imax&=0x7fff;
    if(ltemp<=imax)ltemp=0;
    else ltemp-=imax;
    }
    else
    {
      ltemp+=imax;
    }
    imax=ltemp;
    
    
    }
    
    else
    {

      imax= hanshui[145];
    }
    
 
    
   if(imax<hanshui[145])imax=hanshui[145];
   hanshui[146]=imax;
   cap[146]=imax;
     
    ///////////////////////////////////////////    
 
// ������λ�߶�
  
 
    cw=0; 
    for(ci=1;ci<=duanshu;ci++)
    {
     if(hanshui[ci]>=1)cw=ci;
    }   
    
    if(cw>1)
    {
    ltemp=imc[cw];  
    ltemp*=duanchangdu;
    ltemp/=imc[cw-1];
    imax=ltemp;
    ltemp=cw;
    ltemp-=1;
    ltemp*=duanchangdu;
    ltemp+=imax;
    }
    
    else
    {
      ltemp=imc[1];
      ltemp+=imc[2];
      ltemp*=duanchangdu;
      ltemp/=100;  
    }
    
    imax=xiuzhengzhi;
    if(imax&0x8000)
    {
    imax&=0x7fff;
    if(ltemp<=imax)ltemp=0;
    else ltemp-=imax;
    }
    else
    {
      ltemp+=imax;
    }
    imax=ltemp;
    
   if(imax<hanshui[146])imax=hanshui[146];
   hanshui[147]=imax;
   cap[147]=imax;     
     
     
 
   
   
    
  ///�����ͺ���  =sum�����γ���*��ƽ�����*��1000-��ˮ�ʣ�����
    //������
   for(i=1;i<=duanchangdu;i++)
   {
     imc[i]=1000;
    if(hanshui[i])imc[i]-=hanshui[i]; 
   else imc[i]=0;
   }
   //����
   
   
   
   ltemp=0;
    for(i=1;i<=duanchangdu;i++)
   {
     imax=imc[i];
    //imax*=mianji;
    ltemp+=imax;
    } 
   
    ltemp*=duanchangdu;
    ltemp*=GUANMIANJI;
    ltemp/=10000;
    
    imax=ltemp/10000;
    hanshui[148]=imax;
    ltemp %=10000;
    imax=ltemp;
    hanshui[149]=imax;
   ///////////////////////////////////////// 

    hanshui[0]=cap[0];
    hanshui[144]=cap[144];
    if(Csend==1) 
    {
      for(ci=1;ci<=duanshu;ci++)
      {
      hanshui[ci]=cap[ci];
      }
    
    }
  }