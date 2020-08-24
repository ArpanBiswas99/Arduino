#include <SoftwareSerial.h> //header file of software serial port
SoftwareSerial Serial1(2,3); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code
and directly use Serial1 serial port*/

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
float temprature;
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package
//unsigned long Time=0;
//unsigned long val=0;

// laps info
unsigned long currentRunStartMillis;
unsigned long lastRunInMillis;
unsigned long bestRunInMillis;
int currentLap;
unsigned long savedMillis;

// global for display
int sec_val, milli_val;
 
// laser gate
int LidarState;             // the current reading from the lidar
int lastLidarState = LOW;   // the previous reading from lidar
int reading;
unsigned long lastDebounceTime = 0;  // the last time the lidar state was toggled
int debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer Page 3
  Serial1.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino
  TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  TCCR2B = (TCCR2B & B11111000) | 0x06;

//
  delay(50); // to let the lidar work, so we won't get the lap triggered
  // reset params
  currentRunStartMillis = 0;
  lastRunInMillis = 0;
  bestRunInMillis = 0;
  currentLap = 0;
//
}


void loop() 
{
  if (Serial1.available()) 
  { //check if serial port has data input
    if(Serial1.read() == HEADER) 
    { //assess data package frame header 0x59
      uart[0]=HEADER;
      if (Serial1.read() == HEADER) 
      { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) 
        {  //save data in array
          uart[i] = Serial1.read();
        }
 
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))
        {
          //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256; //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          temprature = uart[6] + uart[7] *256;//calculate chip temprature
          temprature = temprature/8 - 256;
          
          if(dist>10)
          {
//          val=Time;
            reading = LOW;
          }
          else 
          {
            reading = HIGH;
          }
//
          if (reading != lastLidarState) 
          {
            // reset the debouncing timer
            lastDebounceTime = millis();
          } //end if
 
          // if passes the debounce time
          if ((millis() - lastDebounceTime) > debounceDelay) 
          {
            if (reading != LidarState) 
            {
              LidarState = reading;
 
              // If we went high, this mean the beam was broken
              if (LidarState == LOW) 
              {
              // save the millis so all the math on it will be done with the same value.
                savedMillis = millis();
                // if its not the first lap
                if (currentLap > 0) 
                {
                  // save the last run
                  lastRunInMillis = savedMillis - currentRunStartMillis;
                  // if last run is faster then best run
                  if (lastRunInMillis < bestRunInMillis || bestRunInMillis == 0) 
                  {
                    //save as best
                    bestRunInMillis = lastRunInMillis;
                  } //end if
                } //end if
       
                //reset the current
                currentRunStartMillis = savedMillis;
       
                // move lap counter
                currentLap++;
              } //end if
            } //enf if
          } //end if

          // save the reading. Next time through the loop, it'll be the lastLidarState:
          lastLidarState = reading;
//          
          Serial.print("dist = ");
          Serial.print(dist); //output measure distance value of LiDAR
          
          Serial.print('\t');
          
//          Serial.print("strength = ");
//          Serial.print(strength); //output signal strength value

          Serial.print("Lap = ");
//          Serial.print(val*8); //output time value
          Serial.print(currentLap); //output current lap number
          
          savedMillis = millis();
          Serial.print('\n');

          if (currentLap > 0) {
            calcResultFromMillis(savedMillis - currentRunStartMillis, &sec_val, &milli_val);
          } 
          else {
            calcResultFromMillis(0, &sec_val, &milli_val);
          } //end if

          // CURRENT RUN
          Serial.print("Current run: %02d.%03d");
          Serial.print(sec_val, milli_val);

          Serial.print('\t');
          
          // LAST RUN
          calcResultFromMillis(lastRunInMillis, &sec_val, &milli_val);
          Serial.print("Last run: %02d.%03d");
          Serial.print(sec_val, milli_val);

          Serial.print('\t');
 
          // BEST RUN
          calcResultFromMillis(bestRunInMillis, &sec_val, &milli_val);
          Serial.print("Best run: %02d.%03d");
          Serial.print(sec_val, milli_val);

          Serial.print('\n');
        }
      }
    }
  }
}


// calculate millis into 2 values, seconeds and millis for display
void calcResultFromMillis(unsigned long value, int *sec_val, int *milli_val) {
  *sec_val = int(value / 1000);
  *milli_val = value - *sec_val * 1000;
}



//ISR(TIMER2_OVF_vect) 
//{
//  Time = Time + 1;
//}
