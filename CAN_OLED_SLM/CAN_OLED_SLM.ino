// CAN-BUS Receive Data

#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>
#define INT8U unsigned char

#include <FastLED.h>
#include<Nextion.h>
#define NUM_LEDS 10
#define DATA_PIN 7


const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);
INT8U len = 0;
INT8U buf[8];
unsigned char canId;
char str[20];
int pulse=0;
int RPM_id;
int map_val;


/*
int RPML; char RPM_L;
int RPMH; char RPM_H;
char RPM_F; char RPM_F1;
unsigned int RPM_dec;*/


CRGB leds[NUM_LEDS];


void setup()
{
  FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_500KBPS))   // canbus baudrate 500kbps
    {
        Serial.println("CAN BUS Shield init fail!!!");
        Serial.println("Init CAN BUS Shield again...");
        delay(100);
    }
    Serial.println("CAN BUS Initialisation Succesful");
    CAN.init_Mask(0, 0, 0x3ff);                         // there are 2 mask in mcp2515, you need to set both of them
    CAN.init_Mask(1, 0, 0x3ff);
    /*
     * set filter, we can receive id from 0x04 ~ 0x09
     */
    CAN.init_Filt(0, 0, 0x45);                          // there are 6 filter in mcp2515
}


void loop()
{
while (CAN_MSGAVAIL == CAN.checkReceive())
  {
       CAN.readMsgBuf(&len, buf);
       canId = CAN.getCanId();
       RPM_id = buf[0];
       map_val = buf[1];
      // RPMH = buf[2];
       Serial.print(" Can id : ");
       Serial.print(canId);
       Serial.print(" RPM id : ");
       Serial.print(RPM_id);
       Serial.print(" RPM : ");
       Serial.print(map_val);
    /*   Serial.print(" RPM L : ");
       Serial.print(RPML);
       Serial.print(" RPM H : ");
       Serial.print(RPMH); */

                       /*RPM_L=String(RPML, HEX);
RPM_H=String(RPMH, HEX);
RPM_F=RPML+RPMH;
RPM_F1=0xFFFF-RPM_F;
RPM_dec=String(RPM_F1, DEC);*/
//Display code Begins ...

 unsigned int RPM= map(map_val,0,255,0,5000);
   
 int RPM1=111;
  Serial.print("rpm.val=");  
  Serial.print(RPM1);
  Serial.write(0xff);  
  Serial.write(0xff);
  Serial.write(0xff);
 

 //SLM Stick code begins...

/*
   if(RPM>=0&&RPM<=500)
  {
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Black;
    FastLED.show();
  leds[2] = CRGB::Black;
    FastLED.show();
  leds[3] = CRGB::Black;
    FastLED.show();
  leds[4] = CRGB::Black;
    FastLED.show();
  leds[5] = CRGB::Black;
    FastLED.show();
  leds[6] = CRGB::Black;
    FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
  FastLED.show();
 
  }
  else if(RPM>500&&RPM<=1000)
  {
  leds[0] = CRGB::Red;
  FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Black;
    FastLED.show();
  leds[3] = CRGB::Black;
    FastLED.show();
  leds[4] = CRGB::Black;
    FastLED.show();
  leds[5] = CRGB::Black;
    FastLED.show();
  leds[6] = CRGB::Black;
    FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
  FastLED.show();
   }
 
else if(RPM>1000&&RPM<=1500)
{
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Black;
    FastLED.show();
  leds[4] = CRGB::Black;
    FastLED.show();
  leds[5] = CRGB::Black;
    FastLED.show();
  leds[6] = CRGB::Black;
    FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
    FastLED.show();
 
}
 
 else if(RPM>1500&&RPM<=2000)
 {
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Yellow;
    FastLED.show();
  leds[4] = CRGB::Black;
    FastLED.show();
  leds[5] = CRGB::Black;
    FastLED.show();
  leds[6] = CRGB::Black;
    FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
  FastLED.show();
 }
 
 else if(RPM>2000&&RPM<=2500)
  {
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Yellow;
    FastLED.show();
  leds[4] = CRGB::Yellow;
    FastLED.show();
  leds[5] = CRGB::Yellow;
    FastLED.show();
   leds[6] = CRGB::Black;
     FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
    FastLED.show();
  }
 else if(RPM>2500&&RPM<=3000)
 {
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Yellow;
    FastLED.show();
  leds[4] = CRGB::Yellow;
    FastLED.show();
  leds[5] = CRGB::Yellow;
    FastLED.show();
  leds[6] = CRGB::Yellow;
    FastLED.show();
  leds[7] = CRGB::Black;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
  FastLED.show();
 }
 else if(RPM>3000&&RPM<=3500)
 {
  leds[0] = CRGB::Red;
    FastLED.show();  
  leds[1] = CRGB::Red;
    FastLED.show();  
  leds[2] = CRGB::Red;
    FastLED.show();  
  leds[3] = CRGB::Yellow;
    FastLED.show();
   leds[4] = CRGB::Yellow;
     FastLED.show();
  leds[5] = CRGB::Yellow;
    FastLED.show();
  leds[6] = CRGB::Yellow;
    FastLED.show();
  leds[7] = CRGB::Green;
    FastLED.show();
  leds[8] = CRGB::Black;
    FastLED.show();
  leds[9] = CRGB::Black;
  FastLED.show();
 }
else if(RPM>3500&&RPM<=4000)
{
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Yellow;
    FastLED.show();
     leds[4] = CRGB::Yellow;
       FastLED.show();
  leds[5] = CRGB::Yellow;
    FastLED.show();
  leds[6] = CRGB::Yellow;
    FastLED.show();
  leds[7] = CRGB::Green;
    FastLED.show();
  leds[8] = CRGB::Green;
    FastLED.show();
    leds[9] = CRGB::Black;
  FastLED.show();
}

 else if (RPM<4000&&RPM<=4500)
 {
  leds[0] = CRGB::Red;
    FastLED.show();
  leds[1] = CRGB::Red;
    FastLED.show();
  leds[2] = CRGB::Red;
    FastLED.show();
  leds[3] = CRGB::Yellow;
    FastLED.show();
    leds[4] = CRGB::Yellow;
      FastLED.show();
  leds[5] = CRGB::Yellow;
    FastLED.show();
  leds[6] = CRGB::Yellow;
    FastLED.show();
  leds[7] = CRGB::Green;
    FastLED.show();  
  leds[8] = CRGB::Green;
    FastLED.show();  
   leds[9] = CRGB::Green;
  FastLED.show();
 }
 else
  {
      leds[0] = CRGB::Blue;
    FastLED.show();
    leds[1] = CRGB::Blue;
    FastLED.show();
  leds[2] = CRGB::Blue;
    FastLED.show();
  leds[3] = CRGB::Blue;
    FastLED.show();
  leds[4] = CRGB::Blue;
    FastLED.show();
  leds[5] = CRGB::Blue;
    FastLED.show();
  leds[6] = CRGB::Blue;
    FastLED.show();
  leds[7] = CRGB::Blue;
    FastLED.show();
  leds[8] = CRGB::Blue;
    FastLED.show();
  leds[9] = CRGB::Blue;
  FastLED.show();
  }*/
  }
  delay(50);

}
