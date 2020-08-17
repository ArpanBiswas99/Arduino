/*
 * This is an example code for a BUCK converter circuit made with arduino
 * I've used arduino NANO. We have to set the timer of the PWM on pin D3
 * No feedback is connected here 
 * Subscribe: http://www.youtube.com/c/electronoobs
 * webpage: http://www.electronoobs.com/eng_circuitos_tut10.php
 */

int potentiometer = A0; //From the main potentiometer
int PWM = 3;          


void setup() {
  pinMode(potentiometer, INPUT);
  pinMode(PWM, OUTPUT);  
  TCCR2B = TCCR2B & B11111000 | B00000001;    // pin 3 and 11 PWM frequency of 31372.55 Hz
}

void loop() {  
  
  float voltage = analogRead(potentiometer);
  int VALUE = map(voltage,0,1023,0,255);
  analogWrite(PWM,VALUE);  

}
