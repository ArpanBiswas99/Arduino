#include "mcp_can.h"
#include <SPI.h>
#define INT8U unsigned char
#define INT32U unsigned char




MCP_CAN CAN(8);
INT32U canId2 = 0x000;
byte abcd[16];
INT8U len2 = 8;
INT8U buf2[8];
unsigned char msg2[3] = {0x3D, 0x30, 0x00};

void setup()
{
  Serial.begin(115200);
while (CAN_OK != CAN.begin(CAN_250KBPS))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
    
//attachInterrupt(digitalPinToInterrupt(2),send_can,LOW);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
}

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

  pulse = analogRead(A1);
  if (pulse > 83) {
    digitalWrite(8, HIGH);
  }
  if (pulse <= 83) {
    digitalWrite(8, LOW);
  }
  if (pulse > 166) {
    digitalWrite(7, HIGH);
  }
  if (pulse <= 166) {
    digitalWrite(7, LOW);
  }
  if (pulse > 249) {
    digitalWrite(6, HIGH);
  }
  if (pulse <= 249) {
    digitalWrite(6, LOW);
  }
  if (pulse > 332) {
    digitalWrite(5, HIGH);
  }
  if (pulse <= 332) {
    digitalWrite(5, LOW);
  }
  if (pulse > 415) {
    digitalWrite(4, HIGH);
  }
  if (pulse <= 415) {
    digitalWrite(4, LOW);
  }
  if (pulse > 498) {
    digitalWrite(3, HIGH);
  }
  if (pulse <= 498) {
    digitalWrite(3, LOW);
  }
  if (pulse > 581) {
    digitalWrite(2, HIGH);
  }
  if (pulse <= 581) {
    digitalWrite(2, LOW);
  }
  if (pulse > 664) {
    digitalWrite(1, HIGH);
  }
  if (pulse <= 664) {
    digitalWrite(1, LOW);
  }
  if (pulse > 747) {
    digitalWrite(0, HIGH);
  }
  if (pulse <= 747) {
    digitalWrite(0, LOW);
  }
  
  delay(10);

  
  }
  Serial.println("****************************************"); 


delay(1000);


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
// picture loop
  
}
