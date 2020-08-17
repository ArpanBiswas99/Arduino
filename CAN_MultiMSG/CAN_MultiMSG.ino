
#include <Wire.h>
#include <mcp_can.h> 
#include <SPI.h>
#include <stdio.h>
#define INT8U unsigned char
#define INT32U unsigned char
byte c;
int period=300;
unsigned long int time_now;
unsigned long int requestend;

//int combined1,combined2,combined3,combined4,combined5,combined6,combined7,combined8,combined9,combined10,combined11,combined12,combined13,combined14,combined15,combined16;
//float value1,value2,value3,value4,value5,value6,value7,value8,value9,value10,value11,value12,value13,value14,value15,value16;
//int a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1;
//int i,j,k,l,m,n,o,p,i1,j1,k1,l1,m1,n1,o1,p1;
//int abcd[16]={a,a1,b,b1,c,c1,d,d1,e,e1,f,f1,g,g1,h,h1};
//INT8U Flag_Recv = 0;

byte abcd[16];
//byte abcd1[32];
INT8U len = 0;
INT8U buf[8];
INT32U canId = 0x000;

INT8U len1 = 0;
INT8U buf1[8];
INT32U canId1 = 0x000;

INT8U len2 = 0;
INT8U buf2[8];
INT32U canId2 = 0x000;

INT8U len3 = 0;
INT8U buf3[8];
INT32U canId3 = 0x000;

/*INT8U len4 = 0;
INT8U buf4[8];
INT32U canId4 = 0x000;

INT8U len5 = 0;
INT8U buf5[8];
INT32U canId5 = 0x000;

INT8U len6 = 0;
INT8U buf6[8];
INT32U canId6 = 0x000;

INT8U len7 = 0;
INT8U buf7[8];
INT32U canId7 = 0x000;

INT8U len8 = 0;
INT8U buf8[8];
INT32U canId8 = 0x000;

INT8U len9 = 0;
INT8U buf9[8];
INT32U canId9 = 0x000;

INT8U len10 = 0;
INT8U buf10[8];
INT32U canId10 = 0x000;

INT8U len11 = 0;
INT8U buf11[8];
INT32U canId11 = 0x000;

INT8U len12 = 0;
INT8U buf12[8];
INT32U canId12 = 0x000;

INT8U len13 = 0;
INT8U buf13[8];
INT32U canId13 = 0x000;

INT8U len14 = 0;
INT8U buf14[8];
INT32U canId14 = 0x000;

INT8U len15 = 0;
INT8U buf15[8];
INT32U canId15 = 0x000;*/

const int SPI_CS_PIN =4;
MCP_CAN CAN(SPI_CS_PIN)
;

void setup()
{
  //pinMode(7,OUTPUT);
  //digitalWrite(7,HIGH);
  CAN.begin(CAN_1000KBPS);                   
  Serial.begin(115200);
  //Wire.begin(8);       
 // Wire.onRequest(requestEvent); 
//  Wire.onReceive(receiveEvent);
 
}

/*void requestEvent() {
  requeststart=millis();
  Serial.print("giving to i2c");
  Serial.println(requeststart);

   for(int i=0;i<=16;i++){
    Wire.write(abcd[i]);
    }
    }*/


void loop()
{
  
 
  canId = CAN.getCanId();
  CAN.readMsgBuf(&len, buf);
  if( canId==0x7B){ for(int i = 0; i<len; i++) {abcd[i] =   buf[i];  }}
  if( canId==0x7C){ for(int i = 0; i<len; i++) {abcd[i+8]=  buf[i];  }}
  /*if( canId==0x7D){ for(int i = 0; i<len; i++) {abcd[i+16]= buf[i]; }}
  if( canId==0x7E){ for(int i = 0; i<len; i++) {abcd[i+24]= buf[i]; }}
  if( canId==0x7F){ for(int i = 0; i<len; i++) {abcd[i+32]= buf[i]; }}
  if( canId==0x80){ for(int i = 0; i<len; i++) {abcd[i+40]= buf[i]; }}
  if( canId==0x81){ for(int i = 0; i<len; i++) {abcd[i+48]= buf[i]; }}
  if( canId==0x82){ for(int i = 0; i<len; i++) {abcd[i+56]= buf[i]; }}
  if( canId==0x83){ for(int i = 0; i<len; i++) {abcd[i+64]= buf[i]; }}
  if( canId==0x84){ for(int i = 0; i<len; i++) {abcd[i+72]= buf[i]; }}
  if( canId==0x85){ for(int i = 0; i<len; i++) {abcd[i+80]= buf[i]; }}
  if( canId==0x86){ for(int i = 0; i<len; i++) {abcd[i+88]= buf[i]; }}
  if( canId==0x87){ for(int i = 0; i<len; i++) {abcd[i+96]= buf[i]; }}
  if( canId==0x88){ for(int i = 0; i<len; i++) {abcd[i+104]=buf[i];}}
  if( canId==0x89){ for(int i = 0; i<len; i++) {abcd[i+112]=buf[i];}}
  if( canId==0x8A){ for(int i = 0; i<len; i++) {abcd[i+120]=buf[i];}}*/
  
  Serial.print("CAN ID: ");
  Serial.println(canId);
  Serial.print("data len = ");
  Serial.println(len);
  for(int i = 0; i<len; i++){
   Serial.print(buf[i]);
    Serial.print("\t");
  }
  Serial.println();
     
  canId1 = CAN.getCanId();
  CAN.readMsgBuf(&len1, buf1);
  if( canId1==0x7B){ for(int i = 0; i<len1; i++) {abcd[i] =    buf1[i];  }}
  if( canId1==0x7C){ for(int i = 0; i<len1; i++) {abcd[i+8]=   buf1[i];  }}
  /*if( canId1==0x7D){ for(int i = 0; i<len1; i++) {abcd[i+16]=  buf1[i]; }}
  if( canId1==0x7E){ for(int i = 0; i<len1; i++) {abcd[i+24]=  buf1[i]; }}
  if( canId1==0x7F){ for(int i = 0; i<len1; i++) {abcd[i+32]=  buf1[i]; }}
  if( canId1==0x80){ for(int i = 0; i<len1; i++) {abcd[i+40]=  buf1[i]; }}
  if( canId1==0x81){ for(int i = 0; i<len1; i++) {abcd[i+48]=  buf1[i]; }}
  if( canId1==0x82){ for(int i = 0; i<len1; i++) {abcd[i+56]=  buf1[i]; }}
  if( canId1==0x83){ for(int i = 0; i<len1; i++) {abcd[i+64]=  buf1[i]; }}
  if( canId1==0x84){ for(int i = 0; i<len1; i++) {abcd[i+72]=  buf1[i]; }}
  if( canId1==0x85){ for(int i = 0; i<len1; i++) {abcd[i+80]=  buf1[i]; }}
  if( canId1==0x86){ for(int i = 0; i<len1; i++) {abcd[i+88]=  buf1[i]; }}
  if( canId1==0x87){ for(int i = 0; i<len1; i++) {abcd[i+96]=  buf1[i]; }}
  if( canId1==0x88){ for(int i = 0; i<len1; i++) {abcd[i+104]= buf1[i];}}
  if( canId1==0x89){ for(int i = 0; i<len1; i++) {abcd[i+112]= buf1[i];}}
  if( canId1==0x8A){ for(int i = 0; i<len1; i++) {abcd[i+120]= buf1[i];}}*/
  
  Serial.print("CAN ID: ");
  Serial.println(canId1);
  Serial.print("data len = ");
  Serial.println(len1);
  for(int i = 0; i<len1; i++){
    Serial.print(buf1[i]);
   Serial.print("\t");
  }
  Serial.println();

    canId2 = CAN.getCanId();
  CAN.readMsgBuf(&len2, buf2);
  if( canId2==0x7B){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
  if( canId2==0x7C){ for(int i = 0; i<len2; i++) {abcd[i+8]=buf2[i];  }}
  /*if( canId2==0x7D){ for(int i = 0; i<len2; i++) {abcd[i+16]=buf2[i]; }}
  if( canId2==0x7E){ for(int i = 0; i<len2; i++) {abcd[i+24]=buf2[i]; }}
  if( canId2==0x7F){ for(int i = 0; i<len2; i++) {abcd[i+32]=buf2[i]; }}
  if( canId2==0x80){ for(int i = 0; i<len2; i++) {abcd[i+40]=buf2[i]; }}
  if( canId2==0x81){ for(int i = 0; i<len2; i++) {abcd[i+48]=buf2[i]; }}
  if( canId2==0x82){ for(int i = 0; i<len2; i++) {abcd[i+56]=buf2[i]; }}
  if( canId2==0x83){ for(int i = 0; i<len2; i++) {abcd[i+64]=buf2[i]; }}
  if( canId2==0x84){ for(int i = 0; i<len2; i++) {abcd[i+72]=buf2[i]; }}
  if( canId2==0x85){ for(int i = 0; i<len2; i++) {abcd[i+80]=buf2[i]; }}
  if( canId2==0x86){ for(int i = 0; i<len2; i++) {abcd[i+88]=buf2[i]; }}
  if( canId2==0x87){ for(int i = 0; i<len2; i++) {abcd[i+96]=buf2[i]; }}
  if( canId2==0x88){ for(int i = 0; i<len2; i++) {abcd[i+104]=buf2[i];}}
  if( canId2==0x89){ for(int i = 0; i<len2; i++) {abcd[i+112]=buf2[i];}}
  if( canId2==0x8A){ for(int i = 0; i<len2; i++) {abcd[i+120]=buf2[i];}}*/
  Serial.print("CAN ID: ");
  Serial.println(canId2);
  Serial.print("data len = ");
  Serial.println(len2);
  for(int i = 0; i<len2; i++){
  Serial.print(buf2[i]);
  Serial.print("\t");
  }
  Serial.println();

  canId3 = CAN.getCanId();
  CAN.readMsgBuf(&len3, buf3);
  if( canId3==0x7B){ for(int i = 0; i<len3; i++) {abcd[i] = buf3[i];  }}
  if( canId3==0x7C){ for(int i = 0; i<len3; i++) {abcd[i+8]=buf3[i];  }}
  /*if( canId3==0x7D){ for(int i = 0; i<len3; i++) {abcd[i+16]=buf3[i]; }}
  if( canId3==0x7E){ for(int i = 0; i<len3; i++) {abcd[i+24]=buf3[i]; }}
  if( canId3==0x7F){ for(int i = 0; i<len3; i++) {abcd[i+32]=buf3[i]; }}
  if( canId3==0x80){ for(int i = 0; i<len3; i++) {abcd[i+40]=buf3[i]; }}
  if( canId3==0x81){ for(int i = 0; i<len3; i++) {abcd[i+48]=buf3[i]; }}
  if( canId3==0x82){ for(int i = 0; i<len3; i++) {abcd[i+56]=buf3[i]; }}
  if( canId3==0x83){ for(int i = 0; i<len3; i++) {abcd[i+64]=buf3[i]; }}
  if( canId3==0x84){ for(int i = 0; i<len3; i++) {abcd[i+72]=buf3[i]; }}
  if( canId3==0x85){ for(int i = 0; i<len3; i++) {abcd[i+80]=buf3[i]; }}
  if( canId3==0x86){ for(int i = 0; i<len3; i++) {abcd[i+88]=buf3[i]; }}
  if( canId3==0x87){ for(int i = 0; i<len3; i++) {abcd[i+96]=buf3[i]; }}
  if( canId3==0x88){ for(int i = 0; i<len3; i++) {abcd[i+104]=buf3[i];}}
  if( canId3==0x89){ for(int i = 0; i<len3; i++) {abcd[i+112]=buf3[i];}}
  if( canId3==0x8A){ for(int i = 0; i<len3; i++) {abcd[i+120]=buf3[i];}}*/
  Serial.print("CAN ID: ");
  Serial.println(canId3);
  Serial.print("data len = ");
  Serial.println(len3);
  for(int i = 0; i<len3; i++){
     Serial.print(buf3[i]);
      Serial.print("\t");
  }
  Serial.println();
  
/*
canId4 = CAN.getCanId();
  CAN.readMsgBuf(&len4, buf4);
  if( canId4==0x7B){ for(int i = 0; i<len4; i++) {abcd[i] =   buf4[i];  }}
  if( canId4==0x7C){ for(int i = 0; i<len4; i++) {abcd[i+8]=  buf4[i];  }}
  if( canId4==0x7D){ for(int i = 0; i<len4; i++) {abcd[i+16]= buf4[i]; }}
  if( canId4==0x7E){ for(int i = 0; i<len4; i++) {abcd[i+24]= buf4[i]; }}
  if( canId4==0x7F){ for(int i = 0; i<len4; i++) {abcd[i+32]= buf4[i]; }}
  if( canId4==0x80){ for(int i = 0; i<len4; i++) {abcd[i+40]= buf4[i]; }}
  if( canId4==0x81){ for(int i = 0; i<len4; i++) {abcd[i+48]= buf4[i]; }}
  if( canId4==0x82){ for(int i = 0; i<len4; i++) {abcd[i+56]= buf4[i]; }}
  if( canId4==0x83){ for(int i = 0; i<len4; i++) {abcd[i+64]= buf4[i]; }}
  if( canId4==0x84){ for(int i = 0; i<len4; i++) {abcd[i+72]= buf4[i]; }}
  if( canId4==0x85){ for(int i = 0; i<len4; i++) {abcd[i+80]= buf4[i]; }}
  if( canId4==0x86){ for(int i = 0; i<len4; i++) {abcd[i+88]= buf4[i]; }}
  if( canId4==0x87){ for(int i = 0; i<len4; i++) {abcd[i+96]= buf4[i]; }}
  if( canId4==0x88){ for(int i = 0; i<len4; i++) {abcd[i+104]=buf4[i];}}
  if( canId4==0x89){ for(int i = 0; i<len4; i++) {abcd[i+112]=buf4[i];}}
  if( canId4==0x8A){ for(int i = 0; i<len4; i++) {abcd[i+120]=buf4[i];}}
  Serial.print("CAN ID: ");
  Serial.println(canId4);
  Serial.print("data len = ");
  Serial.println(len4);
  for(int i = 0; i<len4; i++){
  Serial.print(buf4[i]);
  Serial.print("\t");
  }
  Serial.println();
  
  canId5 = CAN.getCanId();
  CAN.readMsgBuf(&len5, buf5);
  if( canId5==0x7B){ for(int i = 0; i<len5; i++) {abcd[i] =   buf5[i];  }}
  if( canId5==0x7C){ for(int i = 0; i<len5; i++) {abcd[i+8]=  buf5[i];  }}
  if( canId5==0x7D){ for(int i = 0; i<len5; i++) {abcd[i+16]= buf5[i]; }}
  if( canId5==0x7E){ for(int i = 0; i<len5; i++) {abcd[i+24]= buf5[i]; }}
  if( canId5==0x7F){ for(int i = 0; i<len5; i++) {abcd[i+32]= buf5[i]; }}
  if( canId5==0x80){ for(int i = 0; i<len5; i++) {abcd[i+40]= buf5[i]; }}
  if( canId5==0x81){ for(int i = 0; i<len5; i++) {abcd[i+48]= buf5[i]; }}
  if( canId5==0x82){ for(int i = 0; i<len5; i++) {abcd[i+56]= buf5[i]; }}
  if( canId5==0x83){ for(int i = 0; i<len5; i++) {abcd[i+64]= buf5[i]; }}
  if( canId5==0x84){ for(int i = 0; i<len5; i++) {abcd[i+72]= buf5[i]; }}
  if( canId5==0x85){ for(int i = 0; i<len5; i++) {abcd[i+80]= buf5[i]; }}
  if( canId5==0x86){ for(int i = 0; i<len5; i++) {abcd[i+88]= buf5[i]; }}
  if( canId5==0x87){ for(int i = 0; i<len5; i++) {abcd[i+96]= buf5[i]; }}
  if( canId5==0x88){ for(int i = 0; i<len5; i++) {abcd[i+104]=buf5[i];}}
  if( canId5==0x89){ for(int i = 0; i<len5; i++) {abcd[i+112]=buf5[i];}}
  if( canId5==0x8A){ for(int i = 0; i<len5; i++) {abcd[i+120]=buf5[i];}} 
  Serial.print("CAN ID: ");
  Serial.println(canId5);
  Serial.print("data len = ");
  Serial.println(len5);
  for(int i = 0; i<len5; i++){
  Serial.print(buf5[i]);
  Serial.print("\t");
  }
 Serial.println();

   canId6 = CAN.getCanId();
  CAN.readMsgBuf(&len6, buf6);
  if( canId6==0x7B){ for(int i = 0; i<len6; i++) {abcd[i] =   buf6[i];  }}
  if( canId6==0x7C){ for(int i = 0; i<len6; i++) {abcd[i+8]=  buf6[i];  }}
  if( canId6==0x7D){ for(int i = 0; i<len6; i++) {abcd[i+16]= buf6[i]; }}
  if( canId6==0x7E){ for(int i = 0; i<len6; i++) {abcd[i+24]= buf6[i]; }}
  if( canId6==0x7F){ for(int i = 0; i<len6; i++) {abcd[i+32]= buf6[i]; }}
  if( canId6==0x80){ for(int i = 0; i<len6; i++) {abcd[i+40]= buf6[i]; }}
  if( canId6==0x81){ for(int i = 0; i<len6; i++) {abcd[i+48]= buf6[i]; }}
  if( canId6==0x82){ for(int i = 0; i<len6; i++) {abcd[i+56]= buf6[i]; }}
  if( canId6==0x83){ for(int i = 0; i<len6; i++) {abcd[i+64]= buf6[i]; }}
  if( canId6==0x84){ for(int i = 0; i<len6; i++) {abcd[i+72]= buf6[i]; }}
  if( canId6==0x85){ for(int i = 0; i<len6; i++) {abcd[i+80]= buf6[i]; }}
  if( canId6==0x86){ for(int i = 0; i<len6; i++) {abcd[i+88]= buf6[i]; }}
  if( canId6==0x87){ for(int i = 0; i<len6; i++) {abcd[i+96]= buf6[i]; }}
  if( canId6==0x88){ for(int i = 0; i<len6; i++) {abcd[i+104]=buf6[i];}}
  if( canId6==0x89){ for(int i = 0; i<len6; i++) {abcd[i+112]=buf6[i];}}
  if( canId6==0x8A){ for(int i = 0; i<len6; i++) {abcd[i+120]=buf6[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId6);
  Serial.print("data len = ");
  Serial.println(len6);
  for(int i = 0; i<len6; i++){
   Serial.print(buf6[i]);
    Serial.print("\t");
  }
  Serial.println();

  canId7 = CAN.getCanId();
  CAN.readMsgBuf(&len7, buf7);
  if( canId7==0x7B){ for(int i = 0; i<len7; i++) {abcd[i] =   buf7[i];  }}
  if( canId7==0x7C){ for(int i = 0; i<len7; i++) {abcd[i+8]=  buf7[i];  }}
  if( canId7==0x7D){ for(int i = 0; i<len7; i++) {abcd[i+16]= buf7[i]; }}
  if( canId7==0x7E){ for(int i = 0; i<len7; i++) {abcd[i+24]= buf7[i]; }}
  if( canId7==0x7F){ for(int i = 0; i<len7; i++) {abcd[i+32]= buf7[i]; }}
  if( canId7==0x80){ for(int i = 0; i<len7; i++) {abcd[i+40]= buf7[i]; }}
  if( canId7==0x81){ for(int i = 0; i<len7; i++) {abcd[i+48]= buf7[i]; }}
  if( canId7==0x82){ for(int i = 0; i<len7; i++) {abcd[i+56]= buf7[i]; }}
  if( canId7==0x83){ for(int i = 0; i<len7; i++) {abcd[i+64]= buf7[i]; }}
  if( canId7==0x84){ for(int i = 0; i<len7; i++) {abcd[i+72]= buf7[i]; }}
  if( canId7==0x85){ for(int i = 0; i<len7; i++) {abcd[i+80]= buf7[i]; }}
  if( canId7==0x86){ for(int i = 0; i<len7; i++) {abcd[i+88]= buf7[i]; }}
  if( canId7==0x87){ for(int i = 0; i<len7; i++) {abcd[i+96]= buf7[i]; }}
  if( canId7==0x88){ for(int i = 0; i<len7; i++) {abcd[i+104]=buf7[i];}}
  if( canId7==0x89){ for(int i = 0; i<len7; i++) {abcd[i+112]=buf7[i];}}
  if( canId7==0x8A){ for(int i = 0; i<len7; i++) {abcd[i+120]=buf7[i];}}
  Serial.print("CAN ID: ");
  Serial.println(canId7);
  Serial.print("data len = ");
  Serial.println(len7);
  for(int i = 0; i<len7; i++){
   Serial.print(buf7[i]);
   Serial.print("\t");
  }
  Serial.println();

  canId8 = CAN.getCanId();
  CAN.readMsgBuf(&len8, buf8);
  if( canId8==0x7B){ for(int i = 0; i<len8; i++) {abcd[i] =   buf8[i];  }}
  if( canId8==0x7C){ for(int i = 0; i<len8; i++) {abcd[i+8]=  buf8[i];  }}
  if( canId8==0x7D){ for(int i = 0; i<len8; i++) {abcd[i+16]= buf8[i]; }}
  if( canId8==0x7E){ for(int i = 0; i<len8; i++) {abcd[i+24]= buf8[i]; }}
  if( canId8==0x7F){ for(int i = 0; i<len8; i++) {abcd[i+32]= buf8[i]; }}
  if( canId8==0x80){ for(int i = 0; i<len8; i++) {abcd[i+40]= buf8[i]; }}
  if( canId8==0x81){ for(int i = 0; i<len8; i++) {abcd[i+48]= buf8[i]; }}
  if( canId8==0x82){ for(int i = 0; i<len8; i++) {abcd[i+56]= buf8[i]; }}
  if( canId8==0x83){ for(int i = 0; i<len8; i++) {abcd[i+64]= buf8[i]; }}
  if( canId8==0x84){ for(int i = 0; i<len8; i++) {abcd[i+72]= buf8[i]; }}
  if( canId8==0x85){ for(int i = 0; i<len8; i++) {abcd[i+80]= buf8[i]; }}
  if( canId8==0x86){ for(int i = 0; i<len8; i++) {abcd[i+88]= buf8[i]; }}
  if( canId8==0x87){ for(int i = 0; i<len8; i++) {abcd[i+96]= buf8[i]; }}
  if( canId8==0x88){ for(int i = 0; i<len8; i++) {abcd[i+104]=buf8[i];}}
  if( canId8==0x89){ for(int i = 0; i<len8; i++) {abcd[i+112]=buf8[i];}}
  if( canId8==0x8A){ for(int i = 0; i<len8; i++) {abcd[i+120]=buf8[i];}}
  Serial.print("CAN ID: ");
  Serial.println(canId8);
 Serial.print("data len = ");
 Serial.println(len8);
  for(int i = 0; i<len8; i++){
    Serial.print(buf8[i]);
    Serial.print("\t");
  }


  canId9 = CAN.getCanId();
  CAN.readMsgBuf(&len9, buf9);
  if( canId9==0x7B){ for(int i = 0; i<len9; i++) {abcd[i] =   buf9[i];  }}
  if( canId9==0x7C){ for(int i = 0; i<len9; i++) {abcd[i+8]=  buf9[i];  }}
  if( canId9==0x7D){ for(int i = 0; i<len9; i++) {abcd[i+16]= buf9[i]; }}
  if( canId9==0x7E){ for(int i = 0; i<len9; i++) {abcd[i+24]= buf9[i]; }}
  if( canId9==0x7F){ for(int i = 0; i<len9; i++) {abcd[i+32]= buf9[i]; }}
  if( canId9==0x80){ for(int i = 0; i<len9; i++) {abcd[i+40]= buf9[i]; }}
  if( canId9==0x81){ for(int i = 0; i<len9; i++) {abcd[i+48]= buf9[i]; }}
  if( canId9==0x82){ for(int i = 0; i<len9; i++) {abcd[i+56]= buf9[i]; }}
  if( canId9==0x83){ for(int i = 0; i<len9; i++) {abcd[i+64]= buf9[i]; }}
  if( canId9==0x84){ for(int i = 0; i<len9; i++) {abcd[i+72]= buf9[i]; }}
  if( canId9==0x85){ for(int i = 0; i<len9; i++) {abcd[i+80]= buf9[i]; }}
  if( canId9==0x86){ for(int i = 0; i<len9; i++) {abcd[i+88]= buf9[i]; }}
  if( canId9==0x87){ for(int i = 0; i<len9; i++) {abcd[i+96]= buf9[i]; }}
  if( canId9==0x88){ for(int i = 0; i<len9; i++) {abcd[i+104]=buf9[i];}}
  if( canId9==0x89){ for(int i = 0; i<len9; i++) {abcd[i+112]=buf9[i];}}
  if( canId9==0x8A){ for(int i = 0; i<len9; i++) {abcd[i+120]=buf9[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId9);
  Serial.print("data len = ");
  Serial.println(len9);
  for(int i = 0; i<len9; i++){
   Serial.print(buf9[i]);
    Serial.print("\t");
  }
 Serial.println();

  canId10 = CAN.getCanId();
  CAN.readMsgBuf(&len10, buf10);
  if( canId10==0x7B){ for(int i = 0; i<len10; i++) {abcd[i] =   buf10[i];  }}
  if( canId10==0x7C){ for(int i = 0; i<len10; i++) {abcd[i+8]=  buf10[i];  }}
  if( canId10==0x7D){ for(int i = 0; i<len10; i++) {abcd[i+16]= buf10[i]; }}
  if( canId10==0x7E){ for(int i = 0; i<len10; i++) {abcd[i+24]= buf10[i]; }}
  if( canId10==0x7F){ for(int i = 0; i<len10; i++) {abcd[i+32]= buf10[i]; }}
  if( canId10==0x80){ for(int i = 0; i<len10; i++) {abcd[i+40]= buf10[i]; }}
  if( canId10==0x81){ for(int i = 0; i<len10; i++) {abcd[i+48]= buf10[i]; }}
  if( canId10==0x82){ for(int i = 0; i<len10; i++) {abcd[i+56]= buf10[i]; }}
  if( canId10==0x83){ for(int i = 0; i<len10; i++) {abcd[i+64]= buf10[i]; }}
  if( canId10==0x84){ for(int i = 0; i<len10; i++) {abcd[i+72]= buf10[i]; }}
  if( canId10==0x85){ for(int i = 0; i<len10; i++) {abcd[i+80]= buf10[i]; }}
  if( canId10==0x86){ for(int i = 0; i<len10; i++) {abcd[i+88]= buf10[i]; }}
  if( canId10==0x87){ for(int i = 0; i<len10; i++) {abcd[i+96]= buf10[i]; }}
  if( canId10==0x88){ for(int i = 0; i<len10; i++) {abcd[i+104]=buf10[i];}}
  if( canId10==0x89){ for(int i = 0; i<len10; i++) {abcd[i+112]=buf10[i];}}
  if( canId10==0x8A){ for(int i = 0; i<len10; i++) {abcd[i+120]=buf10[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId10);
  Serial.print("data len = ");
  Serial.println(len10);
 for(int i = 0; i<len10; i++){
   Serial.print(buf10[i]);
    Serial.print("\t");
  }
  Serial.println();

  canId11 = CAN.getCanId();
  CAN.readMsgBuf(&len11, buf11);
  if( canId11==0x7B){ for(int i = 0; i<len11; i++) {abcd[i] =   buf11[i];  }}
  if( canId11==0x7C){ for(int i = 0; i<len11; i++) {abcd[i+8]=  buf11[i];  }}
  if( canId11==0x7D){ for(int i = 0; i<len11; i++) {abcd[i+16]= buf11[i]; }}
  if( canId11==0x7E){ for(int i = 0; i<len11; i++) {abcd[i+24]= buf11[i]; }}
  if( canId11==0x7F){ for(int i = 0; i<len11; i++) {abcd[i+32]= buf11[i]; }}
  if( canId11==0x80){ for(int i = 0; i<len11; i++) {abcd[i+40]= buf11[i]; }}
  if( canId11==0x81){ for(int i = 0; i<len11; i++) {abcd[i+48]= buf11[i]; }}
  if( canId11==0x82){ for(int i = 0; i<len11; i++) {abcd[i+56]= buf11[i]; }}
  if( canId11==0x83){ for(int i = 0; i<len11; i++) {abcd[i+64]= buf11[i]; }}
  if( canId11==0x84){ for(int i = 0; i<len11; i++) {abcd[i+72]= buf11[i]; }}
  if( canId11==0x85){ for(int i = 0; i<len11; i++) {abcd[i+80]= buf11[i]; }}
  if( canId11==0x86){ for(int i = 0; i<len11; i++) {abcd[i+88]= buf11[i]; }}
  if( canId11==0x87){ for(int i = 0; i<len11; i++) {abcd[i+96]= buf11[i]; }}
  if( canId11==0x88){ for(int i = 0; i<len11; i++) {abcd[i+104]=buf11[i];}}
  if( canId11==0x89){ for(int i = 0; i<len11; i++) {abcd[i+112]=buf11[i];}}
  if( canId11==0x8A){ for(int i = 0; i<len11; i++) {abcd[i+120]=buf11[i];}}
  
    Serial.print("CAN ID: ");
  Serial.println(canId11);
  Serial.print("data len = ");
  Serial.println(len11);
  for(int i = 0; i<len11; i++){
   Serial.print(buf11[i]);
    Serial.print("\t");
  }
  Serial.println();

       
  canId12 = CAN.getCanId();
  CAN.readMsgBuf(&len12, buf12);
  if( canId12==0x7B){ for(int i = 0; i<len12; i++) {abcd[i] = buf12[i];  }}
  if( canId12==0x7C){ for(int i = 0; i<len12; i++) {abcd[i+8]=buf12[i];  }}
  if( canId12==0x7D){ for(int i = 0; i<len12; i++) {abcd[i+16]=buf12[i]; }}
  if( canId12==0x7E){ for(int i = 0; i<len12; i++) {abcd[i+24]=buf12[i]; }}
  if( canId12==0x7F){ for(int i = 0; i<len12; i++) {abcd[i+32]=buf12[i]; }}
  if( canId12==0x80){ for(int i = 0; i<len12; i++) {abcd[i+40]=buf12[i]; }}
  if( canId12==0x81){ for(int i = 0; i<len12; i++) {abcd[i+48]=buf12[i]; }}
  if( canId12==0x82){ for(int i = 0; i<len12; i++) {abcd[i+56]=buf12[i]; }}
  if( canId12==0x83){ for(int i = 0; i<len12; i++) {abcd[i+64]=buf12[i]; }}
  if( canId12==0x84){ for(int i = 0; i<len12; i++) {abcd[i+72]=buf12[i]; }}
  if( canId12==0x85){ for(int i = 0; i<len12; i++) {abcd[i+80]=buf12[i]; }}
  if( canId12==0x86){ for(int i = 0; i<len12; i++) {abcd[i+88]=buf12[i]; }}
  if( canId12==0x87){ for(int i = 0; i<len12; i++) {abcd[i+96]=buf12[i]; }}
  if( canId12==0x88){ for(int i = 0; i<len12; i++) {abcd[i+104]=buf12[i];}}
  if( canId12==0x89){ for(int i = 0; i<len12; i++) {abcd[i+112]=buf12[i];}}
  if( canId12==0x8A){ for(int i = 0; i<len12; i++) {abcd[i+120]=buf12[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId12);
  Serial.print("data len = ");
  Serial.println(len12);
  for(int i = 0; i<len12; i++){
    Serial.print(buf12[i]);
   Serial.print("\t");
  }
  Serial.println();

   canId13 = CAN.getCanId();
  CAN.readMsgBuf(&len13, buf13);
  if( canId13==0x7B){ for(int i = 0; i<len13; i++) {abcd[i] =    buf13[i];  }}
  if( canId13==0x7C){ for(int i = 0; i<len13; i++) {abcd[i+8]=   buf13[i];  }}
  if( canId13==0x7D){ for(int i = 0; i<len13; i++) {abcd[i+16]=  buf13[i]; }}
  if( canId13==0x7E){ for(int i = 0; i<len13; i++) {abcd[i+24]=  buf13[i]; }}
  if( canId13==0x7F){ for(int i = 0; i<len13; i++) {abcd[i+32]=  buf13[i]; }}
  if( canId13==0x80){ for(int i = 0; i<len13; i++) {abcd[i+40]=  buf13[i]; }}
  if( canId13==0x81){ for(int i = 0; i<len13; i++) {abcd[i+48]=  buf13[i]; }}
  if( canId13==0x82){ for(int i = 0; i<len13; i++) {abcd[i+56]=  buf13[i]; }}
  if( canId13==0x83){ for(int i = 0; i<len13; i++) {abcd[i+64]=  buf13[i]; }}
  if( canId13==0x84){ for(int i = 0; i<len13; i++) {abcd[i+72]=  buf13[i]; }}
  if( canId13==0x85){ for(int i = 0; i<len13; i++) {abcd[i+80]=  buf13[i]; }}
  if( canId13==0x86){ for(int i = 0; i<len13; i++) {abcd[i+88]=  buf13[i]; }}
  if( canId13==0x87){ for(int i = 0; i<len13; i++) {abcd[i+96]=  buf13[i]; }}
  if( canId13==0x88){ for(int i = 0; i<len13; i++) {abcd[i+104]= buf13[i];}}
  if( canId13==0x89){ for(int i = 0; i<len13; i++) {abcd[i+112]= buf13[i];}}
  if( canId13==0x8A){ for(int i = 0; i<len13; i++) {abcd[i+120]= buf13[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId13);
 Serial.print("data len = ");
  Serial.println(len13);
  for(int i = 0; i<len13; i++){
  Serial.print(buf13[i]);
   Serial.print("\t");
  }
  Serial.println();

  canId14 = CAN.getCanId();
  CAN.readMsgBuf(&len14, buf14);
  if( canId14==0x7B){ for(int i = 0; i<len14; i++) {abcd[i] =    buf14[i];  }}
  if( canId14==0x7C){ for(int i = 0; i<len14; i++) {abcd[i+8]=   buf14[i];  }}
  if( canId14==0x7D){ for(int i = 0; i<len14; i++) {abcd[i+16]=  buf14[i]; }}
  if( canId14==0x7E){ for(int i = 0; i<len14; i++) {abcd[i+24]=  buf14[i]; }}
  if( canId14==0x7F){ for(int i = 0; i<len14; i++) {abcd[i+32]=  buf14[i]; }}
  if( canId14==0x80){ for(int i = 0; i<len14; i++) {abcd[i+40]=  buf14[i]; }}
  if( canId14==0x81){ for(int i = 0; i<len14; i++) {abcd[i+48]=  buf14[i]; }}
  if( canId14==0x82){ for(int i = 0; i<len14; i++) {abcd[i+56]=  buf14[i]; }}
  if( canId14==0x83){ for(int i = 0; i<len14; i++) {abcd[i+64]=  buf14[i]; }}
  if( canId14==0x84){ for(int i = 0; i<len14; i++) {abcd[i+72]=  buf14[i]; }}
  if( canId14==0x85){ for(int i = 0; i<len14; i++) {abcd[i+80]=  buf14[i]; }}
  if( canId14==0x86){ for(int i = 0; i<len14; i++) {abcd[i+88]=  buf14[i]; }}
  if( canId14==0x87){ for(int i = 0; i<len14; i++) {abcd[i+96]=  buf14[i]; }}
  if( canId14==0x88){ for(int i = 0; i<len14; i++) {abcd[i+104]= buf14[i];}}
  if( canId14==0x89){ for(int i = 0; i<len14; i++) {abcd[i+112]= buf14[i];}}
  if( canId14==0x8A){ for(int i = 0; i<len14; i++) {abcd[i+120]= buf14[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId14);
  Serial.print("data len = ");
  Serial.println(len14);
  for(int i = 0; i<len14; i++){
    Serial.print(buf14[i]);
   Serial.print("\t");
  }
  Serial.println();

  canId15 = CAN.getCanId();
  CAN.readMsgBuf(&len15, buf15);
  if( canId15==0x7B){ for(int i = 0; i<len15; i++) {abcd[i] =    buf15[i];  }}
  if( canId15==0x7C){ for(int i = 0; i<len15; i++) {abcd[i+8]=   buf15[i];  }}
  if( canId15==0x7D){ for(int i = 0; i<len15; i++) {abcd[i+16]=  buf15[i]; }}
  if( canId15==0x7E){ for(int i = 0; i<len15; i++) {abcd[i+24]=  buf15[i]; }}
  if( canId15==0x7F){ for(int i = 0; i<len15; i++) {abcd[i+32]=  buf15[i]; }}
  if( canId15==0x80){ for(int i = 0; i<len15; i++) {abcd[i+40]=  buf15[i]; }}
  if( canId15==0x81){ for(int i = 0; i<len15; i++) {abcd[i+48]=  buf15[i]; }}
  if( canId15==0x82){ for(int i = 0; i<len15; i++) {abcd[i+56]=  buf15[i]; }}
  if( canId15==0x83){ for(int i = 0; i<len15; i++) {abcd[i+64]=  buf15[i]; }}
  if( canId15==0x84){ for(int i = 0; i<len15; i++) {abcd[i+72]=  buf15[i]; }}
  if( canId15==0x85){ for(int i = 0; i<len15; i++) {abcd[i+80]=  buf15[i]; }}
  if( canId15==0x86){ for(int i = 0; i<len15; i++) {abcd[i+88]=  buf15[i]; }}
  if( canId15==0x87){ for(int i = 0; i<len15; i++) {abcd[i+96]=  buf15[i]; }}
  if( canId15==0x88){ for(int i = 0; i<len15; i++) {abcd[i+104]= buf15[i];}}
  if( canId15==0x89){ for(int i = 0; i<len15; i++) {abcd[i+112]= buf15[i];}}
  if( canId15==0x8A){ for(int i = 0; i<len15; i++) {abcd[i+120]= buf15[i];}}
  
  Serial.print("CAN ID: ");
  Serial.println(canId15);
 Serial.print("data len = ");
  Serial.println(len15);
  for(int i = 0; i<len15; i++){
    Serial.print(buf15[i]);
   Serial.print("\t");
  }*/
 
  Serial.println();
 
  for(int i=0;i<16;i++){Serial.print(abcd[i]); Serial.print(" ");}
  //for(int i=0;i<32;i++){Serial.print(abcd1[i]); Serial.print(" ");}
 // Serial.println();

 //Wire.write(abcd,16); //delay(500);
  // Wire.write(abcd1,32); delay(500);

     //for(int i=0;i<64;i++){
  //Wire.write(abcd[i]); delay(1000);}
  
 // if(uvw==127){uvw=0;}
  
  Serial.println("****************************************");




 
    if(millis() > time_now + period){
        time_now = millis();
        digitalWrite(7,HIGH);
        Serial.println("Interrupt Low"); 
        delayMicroseconds(1000);
        digitalWrite(7,LOW);

        
    }


    digitalWrite(7,HIGH);
   // Serial.println("Interrupt High");
}


/*
 void receiveEvent(int howMany) {
  if (Wire.available()!=0) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    Serial.print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"); Serial.println(c);       
  }
}*/
