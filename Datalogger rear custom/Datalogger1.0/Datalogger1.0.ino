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
int buttonStateRising=1;
int buttonRisingEdge = 1;        
int lastButtonStateRising = 1;      

const int chipSelect = 10;
unsigned long Time=0;
unsigned long Time_wheel=0;
unsigned long Time_rise=0;



void setup() {
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
    while (1);
  }
    Serial.println("card initialized.");
  TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  TCCR2B = (TCCR2B & B11111000) | 0x06;
  Serial.println("card initialized.");
  
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";
    dataString += String(Time);
    dataString += ",";
  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    if(analogPin>0)
    {
      sensor=sensor*5;
    }
    else
    {sensor=sensor*1.22;
      }
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }
Time_wheel=Time;
  //Here starts the code for detecting a rising edge on pin 11
  while(Time-Time_wheel<300)
  {
   buttonStateRising = digitalRead(11);
   if (buttonStateRising != lastButtonStateRising) {
     if (buttonStateRising == LOW) {
      Serial.println("There was a rising edge on pin 11");
      if(buttonRisingEdge<1)
      {
        Time_rise=Time;
           Serial.println("Time_rise");
      }
      else
      {wheel_speed=Time-Time_rise
        }
      buttonRisingEdge = buttonRisingEdge+1;
      }
   
   else{
          Serial.println("There was no rising edge on pin 11");
   }  
   }
   lastButtonStateRising = buttonStateRising;  
}
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


ISR(TIMER2_OVF_vect) {
  Time = Time + 1;
}
