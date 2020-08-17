/*
 * This is an example code for a BOOST converter circuit made with arduino + feedback
 * I've used arduino NANO. We have to set the timer of the PWM on pin D3
 * The feedback is connected to A1 and we set the desired voltage with a
 * potnetiometer connected to A0.
 * 
 * Subscribe: http://www.youtube.com/c/electronoobs
 * webpage: http://www.electronoobs.com/eng_circuitos_tut10.php
 */

 
int potentiometer = A0; //The input from the potentiometer is A0
int feedback = A1;      //The feedback input is A1
int PWM = 3;            //Digital pin D3 por PWM signal
int pwm = 0;            //Initial value of PWM width

void setup() {
  pinMode(potentiometer, INPUT);
  pinMode(feedback, INPUT);
  pinMode(PWM, OUTPUT);  
  TCCR2B = TCCR2B & B11111000 | B00000001;    // pin 3 and 11 PWM frequency of 31372.55 Hz
}

void loop() {  
  float voltage = analogRead(potentiometer);    //We read the value of the potentiometer, which is the desired value
  float output  = analogRead(feedback);         //We read the feedback, which is the real value

  //If the desired value is HIGHER than the real value, we increase PWM width
  if (voltage > output)
   {
    pwm = pwm+1;
    pwm = constrain(pwm, 1, 254);
   }
   
  //If the desired value is LOWER than the real value, we decreaase PWM width
  if (voltage < output)
   {
    pwm = pwm-1;
    pwm = constrain(pwm, 1, 254);
   }

   analogWrite(PWM,pwm);  //Finally, we create the PWM signal
}
