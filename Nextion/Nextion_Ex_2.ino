//https://www.youtube.com/user/arafamicrosystems
#define led 13
#define an A0
unsigned long time1=0;
void setup() 
{
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  time1=millis();
}

void loop() 
{
  if(Serial.available())
  {
    String rec= Serial.readString();
    if(int(rec[0])==1)
    {
      digitalWrite(led,HIGH);
    }else if(int(rec[0])==0)
    {
      digitalWrite(led,LOW);
    }
  }
  if((unsigned long)millis()-time1>100)
  {
    Serial.print("number.val=");
    int adc=analogRead(an);
    Serial.print(adc);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.print("bar.val=");
    int bar=map(adc,0,1023,0,100);
    bar=constrain(bar,0,100);
    Serial.print(bar);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    time1=millis();
  }
  
}
