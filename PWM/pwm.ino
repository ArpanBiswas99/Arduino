void setup() 
{
 pinMode(8,OUTPUT);
}

void loop()
{
digitalWrite(8,HIGH);
delayMicroseconds(500);

digitalWrite(8,LOW);
delayMicroseconds(500);
}
