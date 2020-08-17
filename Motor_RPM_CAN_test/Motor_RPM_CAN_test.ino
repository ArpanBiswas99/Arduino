#include<Wire.h>
#include <mcp_can.h>
#include <SPI.h>
#define INT8U unsigned char
#define INT32U unsigned char


MCP_CAN CAN(10);
INT32U canId2 = 0x000;
byte abcd[16];
INT8U len2 = 8;
INT8U buf2[8];
byte Values[26];
unsigned char msg1[3] = {0x3D, 0x49, 0x00}; //motor temp --- read reg_id time
unsigned char msg2[3] = {0x3D, 0x4a, 0x00};//controller temp
unsigned char msg3[3] = {0x3D, 0x20, 0x00};//motor current
unsigned char msg4[3] = {0x3D, 0xf6, 0x00};//motor power
unsigned char msg5[3] = {0x3D, 0x30, 0x00};//motor rpm
unsigned char msg6[3] = {0x3D, 0x26, 0x00};//motor current cmd


void setup() {
  Serial.begin(115200);
if(CAN.begin(CAN_250KBPS) ==CAN_OK) 
{
  Serial.print("can init ok!!\r\n");
}
else {
  Serial.print("Can init fail!!\r\n");
}

}

void loop() {
  /*
CAN.sendMsgBuf(0x201, 0, 3, msg1);  
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181)
{
  for(int i = 0; i<len2; i++)
  {
    abcd[i] = buf2[i];
  }
}
Values[24]=buf2[2];
Values[25]=buf2[1];
Serial.println("current cmd");
Serial.println(Values[24]);
Serial.println(Values[25]);
*/

/*CAN.sendMsgBuf(0x201, 0, 3, msg2); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[14]=buf2[2];
Values[15]=buf2[1];
Serial.println("motor temp");
Serial.println(Values[14]);
Serial.println(Values[15]);*/

/*
CAN.sendMsgBuf(0x201, 0, 3, msg3); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[16]=buf2[2];
Values[17]=buf2[1];
Serial.println("controller temp");
Serial.println(Values[16]);
Serial.println(Values[17]);


CAN.sendMsgBuf(0x201, 0, 3, msg4); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[18]=buf2[1];
Values[19]=buf2[2];
Serial.println("current");
Serial.println(Values[18]);
Serial.println(Values[19]);

CAN.sendMsgBuf(0x201, 0, 3, msg5); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[20]=buf2[1];
Values[21]=buf2[2];
Serial.println("power");//power
Serial.println(Values[20]);
Serial.println(Values[21]);
*/
CAN.sendMsgBuf(0x201, 0, 3, msg6); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[22]=buf2[1];
Values[23]=buf2[2];
Serial.println("RPM");
Serial.println(Values[22]);
Serial.println(Values[23]);



delay(500);

}
