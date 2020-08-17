
int pot = A0;

void setup() {
 pinMode(3,OUTPUT);
 pinMode(pot,INPUT);
}

void loop() {

analogRead(pot);
analogWrite(0,1023);
float on = pot*100/1023;
float off = 100 - on;

digitalWrite(3,HIGH);
delayMicroseconds(on);

digitalWrite(3,LOW);
delayMicroseconds(off);
}
