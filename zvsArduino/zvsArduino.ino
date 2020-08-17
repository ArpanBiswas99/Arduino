/*
* Arduino Nano BLDC Controller
*
* Motor speed is controlled by a single potentiometer
* Motor position is determined with EMF Feedback

This project use open loop startup and bemf zero crossing detection method with ADC.
Speed change can be done only when motor is not running, ADC is used during spinning phase 
in zc detection so it can not be used during the motor spinning, but digital speed changing can be implemented.
ZC threshold current should be defined by user depending on the motor type.

* PWM outputs on pins 6(D3), 8(D5), 9(D6), 12(D9), 13(D10) and 14 (D11) at 32 kHz

* Pin 26(A0) is connected to Total Current
* Pin 25(A1) is connected to BEMF Phase 1
* Pin 24(A2) is connected to BEMF Phase 2
* Pin 23(A3) is connected to BEMF Phase 3
* Pin 22(A2) is connected to a potentiometer to change the PWM duty and speed of motor
* Pin 21(D25) is connected to a switch to RUN and STOP Motor
* Pin 20(D24) is connected to a switch to change direction of Motor
*/
 
// Constants won't change. They're used here to set pin numbers:
const int dirPin = 15;// Direction Switch
const int runPin = 16;  // Run Switch
const int potPin = 3;   // Potentiometer
const int PWM1H =3;     // Phase 1 Low PWM
const int PWM1L =5;     // Phase 1 High PWM
const int PWM2H =6;     // Phase 2 Low PWM
const int PWM2L =9;    // Phase 2 High PWM
const int PWM3H =10;    // Phase 3 Low PWM
const int PWM3L =11;    // Phase 3 High PWM
const int mEMF1 =6;    // Phase 2 High PWM
const int mEMF2 =5;    // Phase 3 Low PWM
const int mEMF3 =4;    // Phase 3 High PWM
const int mCur  =7;    // Motor Current
const int rpmConversion  = 100;    // Pot Value to Actual RPM Conversion factor

//direction definitions
#define motorDirection_CW 0
#define motorDirection_CCW 1
//startup delay, the startup delay for every step is given by startup delay array*LDCSENSORLESS_STARTUPDELAYMULT
// #define BLDCSENSORLESS_STARTUPDELAYS {2000,1900,1800,1600,1400,1200,1000,800,600,550,500,480,460,440,420,400,380,360,355,350,345,340,335,330,325,320,315,310,305,300}
// #define BLDCSENSORLESS_STARTUPCOMMUTATIONS 29 //number of startup commutations
// zc bemf threshold value
#define BLDCSENSORLESS_ZCERRORS 100 //number of zc threshold reading error befor emit a motor startup
#define BLDCSENSORLESS_ZCTHRESHOLD 150

//freq = FCPU/1+(prescaler*ICR1)
//note: ICR1 can not be small, because we have some commands to execute during the interrupt routine
//20000Hz = 8000000Hz/(1+(1*399))
// #define TIMER1_ICR1 199
// #define TIMER1_PRESCALER (1<<CS11) //8 prescaler

// Variables will change:
int currentDirection = motorDirection_CW;
int oldDirection = 0;
int runSwitchState = 0;    // Stores state of RUN Switch
int dirSwitchState = 0;    // Stores state of Direcion Switch
int BEMF1; //Stores Phase 1 BEMF Voltage Value
int BEMF2; //Stores Phase 2 BEMF Voltage Value
int BEMF3; //Stores Phase 3 BEMF Voltage Value
int mPos; //Stores Motor Position from EMF
int mCurrent; //Stores Motor Total Current
int mSpeed = 0; //Stores speed of the motor in PWM
int mRPM = 0; //Stores speed of the motor in RPM
int mRunning =0; // Stores if motor is running
int potValue = 0; //this variable is used with analog in to measure the position of the potentiometer
int commutationStep; //Stores current step of 6 step cycle
int mDelay; //Stores delay time between Steps
int controlUpdate_interval;
boolean warmUp = true;

void setup() {

 pinMode(mEMF1,INPUT);    
 pinMode(mEMF2,INPUT);    
 pinMode(mEMF3,INPUT);
 pinMode(dirPin,INPUT);    
 pinMode(runPin,INPUT);    
 pinMode(potPin,INPUT);
 pinMode(mCur,INPUT);    
 
// Outputs for the IR2101 FET Drivers
 pinMode(PWM1L,OUTPUT);    
 pinMode(PWM1H,OUTPUT);   
 pinMode(PWM2L,OUTPUT);       
 pinMode(PWM2H,OUTPUT);   
 pinMode(PWM3L,OUTPUT);  
 pinMode(PWM3H,OUTPUT);  
  
/* Set PWM frequency on pins 3,5,6,9,10,11 */

// TCCR2B = TCCR2B & 0b11111000 | 1; // PWM ON pins 11 and 3 set to 31kHz
// TCCR1B = TCCR1B & 0b11111000 | 1; // PWM ON pins 9 and 10 set to 31kHz
// TCCR0B = TCCR0B & 0b11111000 | 1; // PWM ON pins 5 and 6 set to 62kHz
 
 Serial.begin(9600);
}

// Main Control Loop
void loop(){
 
 // Control Update Loop
 controlUpdate_interval++;
   if(controlUpdate_interval > 500)
 {
   controlUpdate_interval = 0;
   controlUpdate();
 }
 if (runSwitchState == 1)
 {
 //  motor_setDirection();
 //  motor_setSpeed();
   motor_warmUp();
 //  pulseMotor(2300);
 //  delayMillisecond(2000);  
 //  motor_nextStep();
 //  motor_runStep(commutationStep);
 //  motor_Run(currentDirection);
   calc_motorSpeed();
 }
 else
 {
   motor_off();
 }
 }


void controlUpdate()
{
 // Check for Speed
 potValue = analogRead(potPin); //value of the potentiometer
   
 // Check for ON/OFF Switch and Direction
 runSwitchState = digitalRead(runPin); // Run State
 dirSwitchState = digitalRead(dirPin); // Direction State

 // Check Back EMF Position
 BEMF1 = analogRead(25)*0.0048828125; //value of EMF for Phase 1
 BEMF2 = analogRead(24)*0.0048828125; //value of EMF for Phase 2
 BEMF3 = analogRead(23)*0.0048828125; //value of EMF for Phase 3
}

void motor_setDirection()
{

// Set currentDirection to Old Direction
oldDirection = currentDirection;

//check for desired direction
if(dirSwitchState == 1)
{
 currentDirection = motorDirection_CCW;
} 
else
{
 currentDirection = motorDirection_CW;
}

if(currentDirection != oldDirection) //Direction has changed
{

//stop motor
motor_stop();

//wait for the motor to stop
delay(2000);  

}
}

void motor_setSpeed()
{
 mSpeed = map(potValue, 0, 1023, 0, 255); //Pot is mapped to desired PWM
}

void motor_nextStep(void)
{

commutationStep = 1;  

//mSpeed Controls Delay between 100% PWM
//set Delay with Variable PWM

if (currentDirection == motorDirection_CW)
{
  commutationStep++;
}
else if (currentDirection == motorDirection_CCW)
{
  commutationStep--;
}

if (commutationStep >= 6)
{
  commutationStep = 0;
}
if (commutationStep < 0)
{
  commutationStep = 6;
}
}

void calc_motorSpeed() // Calculate Motor Speed in RPM
{
 // Send Motor Speed in RPM to Serial Display
   mRPM =   potValue * rpmConversion;
   Serial.print(mRPM);
}

void motor_stop()
{
mSpeed = 0;
mDelay = 0;
digitalWrite(PWM1H, LOW);
digitalWrite(PWM1L, LOW);
digitalWrite(PWM2H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM3H, LOW);
digitalWrite(PWM3L, LOW);
}

void motor_off()
{
if (runSwitchState==0)
{
mSpeed = 0;
mDelay = 0;
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2L, LOW);
}
}
   
void motor_warmUp()
{
if (warmUp==true) {
 Serial.println("Motor Warmup Started");
for (int i=20; i>0; i--) {
pulseMotor(10000);
}

for (int i=20; i>0; i--) {
pulseMotor(9000);
}

for (int i=20; i>0; i--) {
pulseMotor(8000);
}

for (int i=20; i>0; i--) {
pulseMotor(7500);
}

for (int i=20; i>0; i--) {
pulseMotor(7000);
}

for (int i=20; i>0; i--) {
pulseMotor(6500);
}

for (int i=20; i>0; i--) {
pulseMotor(6000);
}

for (int i=20; i>0; i--) {
pulseMotor(5500);
}

for (int i=20; i>0; i--) {
pulseMotor(5000);
}

for (int i=20; i>0; i--) {
pulseMotor(4500);
}

for (int i=20; i>0; i--) {
pulseMotor(4000);
}

for (int i=20; i>0; i--) {
pulseMotor(3500);
}

for (int i=20; i>0; i--) {
pulseMotor(3100);
}

for (int i=20; i>0; i--) {
pulseMotor(3000);
}

for (int i=20; i>0; i--) {
pulseMotor(2900);
}

for (int i=20; i>0; i--) {
pulseMotor(2800);
}

for (int i=40; i>0; i--) {
pulseMotor(2750);
}

for (int i=40; i>0; i--) {
pulseMotor(2700);
}

for (int i=40; i>0; i--) {
pulseMotor(2650);
}

for (int i=40; i>0; i--) {
pulseMotor(2600);
}

for (int i=40; i>0; i--) {
pulseMotor(2550);
}

for (int i=40; i>0; i--) {
pulseMotor(2500);
}

for (int i=40; i>0; i--) {
pulseMotor(2450);
}

for (int i=40; i>0; i--) {
pulseMotor(2400);
}

for (int i=40; i>0; i--) {
pulseMotor(2350);
}
}

warmUp = false;
while(1)
{
pulseMotor(2300);
}
}



void pulseMotor(int delayMicroSeconds)
{

if(currentDirection == motorDirection_CW)
Serial.println("Motor Running");
while (1)
{
digitalWrite(PWM1H, HIGH); //Q1
digitalWrite(PWM2L, HIGH); //Q5
digitalWrite(PWM1L, LOW);
digitalWrite(PWM2H, LOW);
digitalWrite(PWM3H, LOW);
digitalWrite(PWM3L, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
digitalWrite(PWM1H, HIGH); //Q1
digitalWrite(PWM3L, HIGH); //G6
digitalWrite(PWM1L, LOW);
digitalWrite(PWM2H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM3H, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
digitalWrite(PWM2H, HIGH); //Q2
digitalWrite(PWM3L, HIGH); //Q6
digitalWrite(PWM1L, LOW);
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM3H, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
digitalWrite(PWM2H, HIGH); //Q2
digitalWrite(PWM1L, HIGH); //Q4
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM3H, LOW);
digitalWrite(PWM3L, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
digitalWrite(PWM3H, HIGH); //Q3
digitalWrite(PWM1L, HIGH); //Q4
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2H, LOW);
digitalWrite(PWM2L, LOW);
digitalWrite(PWM3L, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
digitalWrite(PWM3H, HIGH); //Q3
digitalWrite(PWM2L, HIGH); //Q5
digitalWrite(PWM1L, LOW);
digitalWrite(PWM1H, LOW);
digitalWrite(PWM2H, LOW);
digitalWrite(PWM3L, LOW);
delayMicroseconds(delayMicroSeconds); // wait for a period of time
}
}
