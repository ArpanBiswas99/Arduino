#include<Wire.h>
#include <mcp_can.h>
#include <SPI.h>
#define INT8U unsigned char
#define INT32U unsigned char


MCP_CAN CAN(53);
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

//Variables for Rear BPS Calculations
float BPS_Rear_V = 0.0;   // variable input
int BPS_Rear     = 0.0;   // variable output

//Variables for STS RR Calculations
float STS_RR_V   = 0.0;   // variable input
int STS_RR       = 0.0;   // variable output

//Variables for STS RR Calculations
float STS_RL_V   = 0.0;   // variable input
int STS_RL       = 0.0;   // variable output

//Variables for Accel X-Axis Calculations
float ACCEL_X_V  = 0.0;   // variable input
int ACCEL_X      = 0.0;   // variable output

//Variables for Accel Y-Axis Calculations
float ACCEL_Y_V  = 0.0;   // variable input
int ACCEL_Y      = 0.0;   // variable output

//Variables for GYRO Calculations
float GYRO_V     = 0.0;   // variable input
int GYRO         = 0.0;   // variable output

//Rad_temp Vaiables
float Rad_Temp_V = 0.0;    // input variable
int Rad_Temp     = 0.0;     // variable output

void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.setClock(400000);
  Wire.onRequest(requestEvent);
if(CAN.begin(CAN_1000KBPS) ==CAN_OK) 
{
  Serial.print("can init ok!!\r\n");
}
else {
  Serial.print("Can init fail!!\r\n");
}

}

void loop() {
  //Brake Pressure Sensor
  BPS_Rear_V = (((analogRead(A5))  * 5.0) / 1023);//analogRead(A5)
  BPS_Rear   = (BPS_Rear_V * 1000);
  //Accel X&Y-Axis Calculation
  ACCEL_Y_V  = (((analogRead(A6))  * 5.0) / 1023);//(analogRead(A6)
  ACCEL_X_V  = (((analogRead(A7))  * 5.0) / 1023);//(analogRead(A7)
  ACCEL_Y    = (ACCEL_Y_V * 1000);
  ACCEL_X    = (ACCEL_X_V * 1000);
  //Gyro Calculation
  GYRO_V     = (((analogRead(A0))  * 5.0) / 1023);//(analogRead(A8)
  GYRO       = (GYRO_V * 1000);
  //Shock Travel Sensor Calculation
  STS_RL_V   = (((analogRead(A1))  * 5.0) / 1023);//(analogRead(A9)
  STS_RR_V   = (((analogRead(A2)) * 5.0) / 1023);//(analogRead(A10)
  STS_RL     = (STS_RL_V * 1000);
  Serial.print(STS_RL);
  STS_RR     = (STS_RR_V * 1000);
  Serial.print(STS_RL);
  //Radiator Temp Calculation
  Rad_Temp_V = (((analogRead(A3)) * 5.0) / 1023);//(analogRead(A11)
  Rad_Temp   = (Rad_Temp * 1000);
  
  CAN.sendMsgBuf(0x201, 0, 3, msg1);  

canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[24]=buf2[2];
Values[25]=buf2[1];
Serial.println("current cmd");
Serial.println(Values[24]);
Serial.println(Values[25]);


CAN.sendMsgBuf(0x201, 0, 3, msg2); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}
Values[14]=buf2[2];
Values[15]=buf2[1];
Serial.println("motor temp");
Serial.println(Values[14]);
Serial.println(Values[15]);


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
CAN.sendMsgBuf(0x201, 0, 3, msg6); 
canId2 = CAN.getCanId();
CAN.readMsgBuf(&len2, buf2);
if( canId2==0x181){ for(int i = 0; i<len2; i++) {abcd[i] = buf2[i];  }}

 Values[22]=buf2[1];
Values[23]=buf2[2];
Serial.println("RPM");
Serial.println(Values[22]);
Serial.println(Values[23]);

  
  //I2C Value Array
  Values[0]   = highByte(BPS_Rear);
  Values[1]   = lowByte(BPS_Rear);
  Values[2]   = highByte(ACCEL_X);
  Values[3]   = lowByte(ACCEL_X);
  Values[4]   = highByte(ACCEL_Y);
  Values[5]   = lowByte(ACCEL_Y);
  Values[6]   = highByte(GYRO);
  Values[7]   = highByte(GYRO);
  Values[8]   = highByte(STS_RR);
  Values[9]   = lowByte(STS_RR);
  Values[10]  = highByte(STS_RL);
  Values[11]  = lowByte(STS_RL);
  Values[12]  = highByte(Rad_Temp);
  Values[13]  = lowByte(Rad_Temp);
}

void requestEvent()
{
  for(int c=0;c<26;c++){
    Wire.write(Values[c]);
  }
}
