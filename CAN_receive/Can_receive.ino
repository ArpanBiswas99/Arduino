// CAN-BUS Receive Data

#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>

#define INT8U unsigned char
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);

INT8U len = 0;
INT8U buf[8];
unsigned char canId;
char str[20];
int pulse=0;

int btnvalue;
int potvalue;
void setup()
{
  
  Serial.begin(115200);

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
      potvalue = buf[0];
      btnvalue = buf[1];
      
       Serial.print(" Can id : ");
       Serial.print(canId);
       Serial.print(" Potentiometer Value : ");
       Serial.print(potvalue);
       Serial.print(" Button Value : ");
       Serial.println(btnvalue);
                   
  }
  delay(100);
    
}
