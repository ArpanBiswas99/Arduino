#include <mcp_can.h>
#include <SPI.h>
#define INT8U unsigned char
#define INT32U unsigned char


MCP_CAN CAN(10);
INT32U canId2 = 0x000;
byte abcd[16];
INT8U len2 = 8;
INT8U buf2[8];

void setup()
{
  Serial.begin(115200);
if(CAN.begin(CAN_1000KBPS) ==CAN_OK) Serial.print("can init ok!!\r\n");
else Serial.print("Can init fail!!\r\n");
//attachInterrupt(digitalPinToInterrupt(2),send_can,LOW);
}

unsigned char msg2[3] = {0x3D, 0x49, 0x00};

void loop()
{
// send data:  id = 0x123, standrad flame, data len = 8, stmp: data buf



  CAN.sendMsgBuf(0x201, 0, 3, msg2);  
delay(500);



// receiveeeeeeeeeeeeeeeeeeeeeee__________________________________________________________________________________________________________
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}


Serial.print("CAN ID: ");
  Serial.println(canId2);
  Serial.print("data len = ");
  Serial.println(len2);
  for(int i = 0; i<len2; i++){
  Serial.print(buf2[i]);
  Serial.print("\t");
  }
  Serial.println();
  for(int i=0;i<16;i++){Serial.print(abcd[i]); Serial.print(" ");
  }
  Serial.println("****************************************");
}
