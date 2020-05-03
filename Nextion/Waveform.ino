unsigned long time1;
void setup() 
{
  Serial.begin(115200);
  pinMode(A0,OUTPUT);
  digitalWrite(A4,HIGH);
  pinMode(A4,OUTPUT);
  time1=millis();
}

void loop() 
{
  if((unsigned long)millis()-time1>10)
  {
    Serial.print("add 1,0,");
    Serial.print(map(analogRead(A2),0,1023,128,255));
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    time1=millis();
  }
}
