 int potVal = 0;
 int speedPot = A0;
 int pwmSpeed; 
 int G1 = 3;
 int G2 = 5;
 int G3 = 6;
 int G4 = 9;
 int G5 = 10;
 int G6 = 11;
 int GND = 7;
 int VCC = 4;
 int potGND = 12; 
 
void setup() 
{
 pinMode(speedPot, INPUT);
 pinMode(G1, OUTPUT);
 pinMode(G2, OUTPUT);
 pinMode(G3, OUTPUT);
 pinMode(G4, OUTPUT);
 pinMode(G5, OUTPUT);
 pinMode(G6, OUTPUT);
 pinMode(GND, OUTPUT);
 pinMode(VCC, OUTPUT);
 pinMode(potGND, OUTPUT);
 digitalWrite(GND, LOW);
 digitalWrite(VCC, HIGH);
 digitalWrite(potGND, LOW);

 
for (int i=20; i>0; i--)
 { 
  pulseMotor(20000);
 } 
for (int i=20; i>0; i--)
 {
 pulseMotor(19000);
 }
 for (int i=20; i>0; i--)
 { 
pulseMotor(18000);
 }
 for (int i=20; i>0; i--)
 { 
pulseMotor(17000);
 } 
 for (int i=20; i>0; i--)
 {
 pulseMotor(16000);
 }
 for (int i=20; i>0; i--)
 {
 pulseMotor(15500);
 }
 for (int i=20; i>0; i--)
 {
 pulseMotor(15000);
 } 
 for (int i=20; i>0; i--)
 {
 pulseMotor(14500);
 } 
for (int i=20; i>0; i--)
 { 
pulseMotor(14000);
 } 
 for (int i=20; i>0; i--)
 { 
pulseMotor(13500);
 }
 for (int i=20; i>0; i--)
 { 
pulseMotor(13000);
 }
 for (int i=20; i>0; i--) 
{ 
pulseMotor(12500); 
 }
 for (int i=20; i>0; i--) 
{
 pulseMotor(12000);
 } 
for (int i=20; i>0; i--) 
{
 pulseMotor(11500);
 }
 for (int i=20; i>0; i--) 
{
 pulseMotor(11000);
 }
 for (int i=20; i>0; i--) 
{ 
pulseMotor(10500);
 }
 for (int i=20; i>0; i--)
 {
 pulseMotor(10000);
 }
 for (int i=20; i>0; i--) 
{
 pulseMotor(9500);
 } 
for (int i=20; i>0; i--)
 { 
pulseMotor(9000); 
 } 
for (int i=20; i>0; i--) 
{
 pulseMotor(8500); 
} 
for (int i=20; i>0; i--)
 {
 pulseMotor(8000); 
} 
for (int i=20; i>0; i--)
 {
 pulseMotor(7500);
 }
 for (int i=20; i>0; i--)
 {
 pulseMotor(7000);
 }
 for (int i=20; i>0; i--)
 {
 pulseMotor(6600); 
 }
 for (int i=20; i>0; i--)
 {
   pulseMotor(6200);
 }
 for (int i=20; i>0; i--) 
{
 pulseMotor(5800);
 } 
for (int i=20; i>0; i--)
 {
  pulseMotor(5400);
 } 
for (int i=40; i>0; i--)
 {
  pulseMotor(5000);
 }
 for (int i=40; i>0; i--)
 { 
pulseMotor(4900);
 } 
for (int i=40; i>0; i--) 
{ 
pulseMotor(4800);
 } 
for (int i=40; i>0; i--) 
{ 
pulseMotor(4700);
 } 
for (int i=40; i>0; i--)
 { 
pulseMotor(4600);
 }
 for (int i=40; i>0; i--) 
{
 pulseMotor(4500);
 } 
for (int i=40; i>0; i--)
 {
  pulseMotor(4400);
 } 
for (int i=40; i>0; i--) 
{
 pulseMotor(4300);
 }
 for (int i=40; i>0; i--)
 { 
pulseMotor(4200); 
} 
for (int i=20; i>0; i--) 
{
 pulseMotor(4000);
 } 
for (int i=20; i>0; i--) 
{ 
pulseMotor(3500);
 } 
for (int i=20; i>0; i--)
 {
 pulseMotor(3100);
 } 
for (int i=20; i>0; i--)
 { 
pulseMotor(3000);
 } 
} 

void pulseMotor(int delayMicroseconds) 
{
 //while (1)
 digitalWrite(G1, HIGH); //Q1
 digitalWrite(G5, HIGH); //Q5 
digitalWrite(G4, LOW); 
digitalWrite(G2, LOW); 
digitalWrite(G3, LOW); 
digitalWrite(G6, LOW); 
delayMicroseconds(delayMicroseconds); // wait for a period of time 
digitalWrite(G1, HIGH); //Q1 
digitalWrite(G6, HIGH); //G6 
digitalWrite(G4, LOW); 
digitalWrite(G2, LOW); 
digitalWrite(G5, LOW); 
digitalWrite(G3, LOW); 
delayMicroseconds(delayMicroSeconds); // wait for a period of time 
digitalWrite(G2, HIGH); //Q2 
digitalWrite(G6, HIGH); //Q6 
digitalWrite(G4, LOW); 
digitalWrite(G1, LOW); 
digitalWrite(G5, LOW); 
digitalWrite(G3, LOW); 
delayMicroseconds(delayMicroSeconds); // wait for a period of time
 digitalWrite(G2, HIGH); //Q2 
digitalWrite(G4, HIGH); //Q4 
digitalWrite(G1, LOW); 
digitalWrite(G5, LOW); 
digitalWrite(G3, LOW); 
digitalWrite(G6, LOW); 
delayMicroseconds(delayMicroSeconds); // wait for a period of time 
digitalWrite(G3, HIGH); //Q3 
digitalWrite(G4, HIGH); //Q4 
digitalWrite(G1, LOW); 
digitalWrite(G2, LOW); 
digitalWrite(G5, LOW); 
digitalWrite(G6, LOW); 
delayMicroseconds(delayMicroSeconds); // wait for a period of time 
digitalWrite(G3, HIGH); //Q3 
digitalWrite(G5, HIGH); //Q5 
digitalWrite(G4, LOW); 
digitalWrite(G1, LOW); 
digitalWrite(G2, LOW); 
digitalWrite(G6, LOW); 
delayMicroseconds(delayMicroSeconds); // wait for a period of time 
 } 
 
void loop() { for (int i=40; i>0; i--) 
{
  pulseMotor(3000); 
 }
}
