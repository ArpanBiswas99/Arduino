#include<Wire.h>
byte Values[6];

//Variables for STS RR Calculations
float STS_RR_V   = 0.0;   // variable input
float STS_RR     = 0.0;   // variable output

//Variables for STS RR Calculations
float STS_RL_V   = 0.0;   // variable input
float STS_RL     = 0.0;   // variable output

//Variables for Accel X-Axis Calculations
float ACCEL_X_V  = 0.0;   // variable input
float ACCEL_X    = 0.0;   // variable output

//Variables for Accel Y-Axis Calculations
float ACCEL_Y_V  = 0.0;   // variable input
float ACCEL_Y    = 0.0;   // variable output

//Variables for GYRO Calculations
float GYRO_V     = 0.0;   // variable input
float GYRO       = 0.0;   // variable output

//Variables for Rear BPS Calculations
float BPS_Rear_V = 0.0;   // variable input
float BPS_Rear   = 0.0;   // variable output

//Rad_temp Vaiables
float Rad_Temp_V = 0.0;    // input variable
float Vin       = 5.0;       // [V]
float Rt        = 5600;       // Resistor t [ohm]
float R0        = 5876;       // value of NTC in T0 [ohm]
float T0        = 273.15;     // use T0 in Kelvin [K]
float Vout      = 0.0;      // Vout in A11
float Rout      = 0.0;      // Rout in A11
float T1        = 273.15;     // [K] in datasheet 0º C
float T2        = 313.15;     // [K] in datasheet 40° C
float RT1       = 5896;      // [ohms]  resistence in T1
float RT2       = 1175;      // [ohms]   resistence in T2
float beta      = 0.0;      // initial parameters [K]
float Rinf      = 0.0;      // initial parameters [ohm]
float TempK     = 0.0;     // variable output
float Rad_Temp  = 0.0;     // variable output

void setup() {
  Wire.begin(8);
   Wire.onRequest(requestEvent); // register event
  Serial.begin(115200);
  beta = (log(RT1 / RT2)) / ((1 / T1) - (1 / T2));
  Rinf = R0 * exp(-beta / T0);
}

void loop() {
  //Brake Pressure Sensor
  BPS_Rear_V = (((analogRead(A5))  * 5.0) / 1023);
  BPS_Rear   = ((BPS_Rear_V) * 25);
  //Accel X&Y-Axis Calculation
  ACCEL_Y_V  = (((analogRead(A6))  * 5.0) / 1023);
  ACCEL_X_V  = (((analogRead(A7))  * 5.0) / 1023);
  ACCEL_Y    = ((2.5 * ACCEL_Y_V) - 6.25);
  ACCEL_X    = ((2.5 * ACCEL_X_V) - 6.25);
  //Gyro Calculation
  GYRO_V     = (((analogRead(A8))  * 5.0) / 1023);
  GYRO       = ((75.027 * GYRO_V) - 187.57);
  //Shock Travel Sensor Calculation
  STS_RL_V   = (((analogRead(A9))  * 5.0) / 1023);
  STS_RR_V   = (((analogRead(A10)) * 5.0) / 1023);
  STS_RL     = ((0.747 * pow(STS_RR_V, 2)) - (14.243 * STS_RR_V) + 27.241);
  STS_RR     = ((0.747 * pow(STS_RR_V, 2)) - (14.243 * STS_RR_V) + 27.241);
  //Radiator Temp Calculation
  Rad_Temp_V = (((analogRead(A11)) * 5.0) / 1023);
  Vout       = (Vin * (Rad_Temp_V) / 1024.0); // calc for NTC
  Rout       = (Rt * Vout / (Vin - Vout));
  TempK      = (beta / log(Rout / Rinf)); // calc for temperature
  Rad_Temp   = TempK - 273.15;
  //I2C Value Array
  Values[0]  = BPS_Rear;
  Values[1]  = ACCEL_X;
  Values[2]  = ACCEL_Y;
  Values[3] = GYRO;
  Values[4]  = STS_RR;
  Values[5]  = STS_RL;
  Values[6] = Rad_Temp;
  
}

void requestEvent() {
  for(int c=0; c<7; c++){
    Wire.write(Values[c]);
  }  
}
