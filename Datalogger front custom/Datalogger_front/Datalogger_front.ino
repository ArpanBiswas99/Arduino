/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

const byte chipSelect = 4;
double Time=0;
int val=LOW;
int count=0;
double timeout=0;
double timeout_value=300;
double wheelspeed=0;
double timerise=0;
double time_while=0;
void setup() {
  pinMode(6,INPUT);
pinMode(7,OUTPUT);
digitalWrite(7,HIGH);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
   TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   TCCR2B = (TCCR2B & B11111000) | 0x04;
   

}

void loop() 
{ // make a string for assembling the data to log:
  val=digitalRead(6);

    if(val != LOW)
    {
  String dataString = "";
  dataString += String(Time);
dataString += ",";
  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++)
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }
  Serial.println("here");
    attachInterrupt(digitalPinToInterrupt(2), blink, RISING);
  timeout=Time;
  count=0;
while((Time-timeout)<timeout_value)
{
  time_while=Time-timeout;
Serial.println("time_while");
Serial.println(Time-timeout);

  if(count>2)
   { Serial.println("count");
    break;
   }
}
Serial.println("there");
if(count<2)
{wheelspeed=0;
  }

timeout=0;
dataString += ",";
dataString += String(wheelspeed);
Serial.println(wheelspeed);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  }
  else
  Time=0;
    }
ISR(TIMER2_OVF_vect){
   Time=Time+1;
}

void blink ()
{ if(count<2)
{
 if(count<1)
{Serial.println("1st:");
Serial.println(count);
  timerise=Time;
count=count+1;
  }
  else
 { 
Serial.println("2nd:");
Serial.println(count);
  
  wheelspeed=Time-timerise;
 Serial.println(wheelspeed);
timerise=0;
count=3;
 }
 }
}
