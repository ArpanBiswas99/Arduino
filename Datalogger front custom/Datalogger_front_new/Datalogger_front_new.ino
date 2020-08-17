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
#include <i2cmaster.h>
#include <SPI.h>
#include <SD.h>
 int sensor;
const int chipSelect = 10;
unsigned long Time=0;
int val=0;

// 0x__ is the assigned address for I²C
// communication for sensor __.
// These addresses were changed from default
// using the code Change_MLX90614_Address. 
// Shift the address 1 bit right, the
// I²Cmaster library only needs the 7 most
// significant bits for the address.
int device1Address = 0x0B<<1; 
int device2Address = 0x01<<1;
int device3Address = 0x02<<1; 
int device4Address = 0x03<<1; 
int device5Address = 0x04<<1;
int device6Address = 0x05<<1; 
int device7Address = 0x06<<1;
int device8Address = 0x07<<1; 
int device9Address = 0x08<<1; 
int device10Address = 0x09<<1;

// Variable to hold temperature in Celcius
float celcius1 = 0;
float celcius2 = 0;             
float celcius3 = 0;
float celcius4 = 0;
float celcius5 = 0;
float celcius6 = 0;
float celcius7 = 0;
float celcius8 = 0;             
float celcius9 = 0;
float celcius10 = 0;
float sensorValue = 0;
float sensorValue1 = 0;
// Variable to count the number read cycles
int cycle = 0;



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
    return;
  }
  Serial.println("card initialized.");
    TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  TCCR2B = (TCCR2B & B11111000) | 0x06;

 // Initialize the I²C bus
  i2c_init();
  // Enable pullups
  PORTC = (1 << PORTC4) | (1 << PORTC5);
  
  pinMode(12,INPUT);
}


void celcius()
{
    // Read data from MLX90614 at address and return temperature
  celcius1 = temperatureCelcius(device1Address);
  celcius2 = temperatureCelcius(device2Address);
  celcius3 = temperatureCelcius(device3Address);
  celcius4 = temperatureCelcius(device4Address);
  celcius5 = temperatureCelcius(device5Address);
  celcius6 = temperatureCelcius(device6Address);
  celcius7 = temperatureCelcius(device7Address);
  celcius8 = temperatureCelcius(device8Address);
  celcius9 = temperatureCelcius(device9Address);
  celcius10 = temperatureCelcius(device10Address);
  //celcius11 = temperatureCelcius(device11Address);
  
  // Output data over serial
//  Serial.println("READING %d",cycle);
  Serial.print("C1:");
  Serial.print(celcius1);
  Serial.print(", C2:");
  Serial.print(celcius2);
  Serial.print(", C3:");
  Serial.print(celcius3);
  Serial.print(", C4:");
  Serial.print(celcius4);
  Serial.print(", C5:");
  Serial.print(celcius5);
  Serial.print(", C6:");
  Serial.print(celcius6);
  Serial.print(", C7:");
  Serial.print(celcius7);
  Serial.print(", C8:");
  Serial.print(celcius8);
  Serial.print(", C9:");
  Serial.print(celcius9);
  Serial.print(", C10:");
  Serial.print(celcius10);
  /*Serial.print(", C11:");
  Serial.print(celcius11);*/
  Serial.println(" end");
  
  // Pause for a second
  delay(1000);
}

float temperatureCelcius(int address)
{
  int device = address;
  int dataLow = 0;
  int dataHigh = 0;
  int pec = 0;

  // Write
  i2c_start_wait(device+I2C_WRITE);
  i2c_write(0x07);

  // Read
  i2c_rep_start(device+I2C_READ);
  dataLow = i2c_readAck();       // Read 1 byte and then send ack.
  dataHigh = i2c_readAck();      // Read 1 byte and then send ack.
  pec = i2c_readNak();
  i2c_stop();
 
  // Scaling factor for the MLX90614
  double temperatureFactor = 0.02;
  double temperatureData = 0x0000;

  // This masks off the error bit of the high byte
  // Then moves it left 8 bits and adds the low byte.
  temperatureData = (double)(((dataHigh & 0x007F) << 8) + dataLow);
  temperatureData = (temperatureData * temperatureFactor)-0.01;
  
  //Convert Kelvin to Celcius
  float celcius = temperatureData - 273.15;
  
  // Return temperature in Celcius.
  return celcius;
}



void loop() 
{
  val=digitalRead(12);
  Time=0;
  // make a string for assembling the data to log:
  while(val==HIGH)
  {
  String dataString = "";
    dataString += String(Time);
    dataString += ",";

  // read three sensors and append to the string:
  
    sensor = analogRead(1);
      sensor=sensor*5;
      dataString += String(sensor);
      dataString += ",";
      sensor = analogRead(0);
    sensor=sensor*1.22;
      dataString += String(sensor);
      dataString += ",";

  sensor = analogRead(14);
  //sensor=(sensor-460)*0.345;
  dataString += String(sensor);
  dataString += ",";
  sensor = analogRead(15);
  sensor=sensor*5;
   dataString += String(sensor);
  

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
  File dataFile1 = SD.open("Tiretemp.txt", FILE_WRITE);
  celcius();
  if (dataFile1) {
    dataFile1.print(celcius1);
    dataFile1.print(",");
    dataFile1.print(celcius2);
    dataFile1.print(",");
    dataFile1.print(celcius3);
    dataFile1.print(",");
    dataFile1.print(celcius4);
    dataFile1.print(",");
    dataFile1.print(celcius5);
    dataFile1.print(",");
    dataFile1.print(celcius6);
    dataFile1.print(",");
    dataFile1.print(celcius7);
    dataFile1.print(",");
    dataFile1.print(celcius8);
    dataFile1.print(",");
    dataFile1.print(celcius9);
    dataFile1.print(",");
    dataFile1.print(celcius10);
    dataFile1.close();  
  }
  else {
    Serial.println("error opening Tiretemp.txt");
    }  
  }
  
}

ISR(TIMER2_OVF_vect) {
  Time = Time + 1;
}
