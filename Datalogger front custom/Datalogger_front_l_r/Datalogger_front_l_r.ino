/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
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

const byte chipSelect = 10;
double Time_r = 0;
double Time_l = 0;
int val_r = LOW;
int val_l = LOW;
int count_r = 0;
int count_l = 0;
double timeout_r = 0;
double timeout_value_r = 300;
double wheelspeed_r = 0;
double timerise_r = 0;
double time_while_r = 0;

double timeout_l = 0;
double timeout_value_l = 300;
double wheelspeed_l = 0;
double timerise_l = 0;
double time_while_l = 0;
void setup() {
  pinMode(12, INPUT);
  pinMode(36, INPUT);
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
  val_r = digitalRead(12);
  Serial.println(val_r);
  if (val_r != LOW)
  {
    String dataString = "";
    dataString += String(Time_r);
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
    //Serial.println("here");
    attachInterrupt(digitalPinToInterrupt(2), blink, RISING);
    timeout_r = Time_r;
    count_r = 0;
    while ((Time_r - timeout_r) < timeout_value_r)
    {
      //time_while=Time-timeout;
      Serial.println("time_while_r");
      Serial.println(Time_r - timeout_r);

      if (count_r > 2)
      { //Serial.println("count");
        break;
      }
    }
    Serial.println("there");
    if (count_r < 2)
    { wheelspeed_r = 0;
    }

    timeout_r = 0;
    dataString += ",";
    dataString += String(wheelspeed_r);
    Serial.println(wheelspeed_r);
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) 
    {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else 
    {
      Serial.println("error opening datalog.txt");
    }
  }
  else
    Time_r = 0;

  // make a string for assembling the data to log:
  val_l = digitalRead(36);
  Serial.println(val_l);
  if (val_l != LOW)
  {
    String dataString = "";
    dataString += String(Time_l);
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
    //Serial.println("here");
    attachInterrupt(digitalPinToInterrupt(2), blink, RISING);
    timeout_l = Time_l;
    count_l = 0;
    while ((Time_l - timeout_l) < timeout_value_l)
    {
      //time_while=Time-timeout;
      Serial.println("time_while_l");
      Serial.println(Time_l - timeout_l);

      if (count_l > 2)
      { //Serial.println("count");
        break;
      }
    }
    Serial.println("there");
    if (count_l < 2)
    { wheelspeed_l = 0;
    }

    timeout_l = 0;
    dataString += ",";
    dataString += String(wheelspeed_l);
    Serial.println(wheelspeed_l);
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) 
    {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else 
    {
      Serial.println("error opening datalog.txt");
    }
  }
  else
    Time_l = 0;
}

ISR(TIMER2_OVF_vect) 
{
  Time_r = Time_r + 1;
}

ISR(TIMER3_OVF_vect) 
{
  Time_l = Time_l + 1;
}


void blink ()
{ if (count_r < 2)
  {
    if (count_r < 1)
    { //Serial.println("1st:");
      //Serial.println(count);
      timerise_r = Time_r;
      count_r = count_r + 1;
    }
    else
    {
      //Serial.println("2nd:");
      //Serial.println(count);

      wheelspeed_r = Time_r - timerise_r;
      Serial.println(wheelspeed_r);
      timerise_r = 0;
      count_r = 3;
    }
  }
  else
  {
    if (count_l < 2)
    {
    if (count_l < 1)
    { //Serial.println("1st:");
      //Serial.println(count);
      timerise_l = Time_l;
      count_l = count_l + 1;
    }
    else
    {
      //Serial.println("2nd:");
      //Serial.println(count);

      wheelspeed_l = Time_l - timerise_l;
      Serial.println(wheelspeed_l);
      timerise_l = 0;
      count_l = 3;
    }
  }
  }
}
