//https://www.youtube.com/user/arafamicrosystems
#include <SoftwareSerial.h>
#define led 13
#define an A0
SoftwareSerial mySerial(2, 3); // RX, TX
int threshold=5;
unsigned long time1=0,time2=0;
int adc1, adc2;
void setup() 
{
  pinMode(led,OUTPUT);
  mySerial.begin(115200);
  time1=millis();
  time2=millis();
}

void loop() 
{
  
  if(mySerial.available())
  {
    String rec= mySerial.readString();
    if(rec[0]=="1")
    {
      digitalWrite(led,HIGH);
    }else if(rec[0]=="0")
    {
      digitalWrite(led,LOW);
    }
  }
  
  if((unsigned long)millis()-time1>100)
  {
    mySerial.print("number.val=");
    int adc=analogRead(an);
    //Serial.println(adc);
    mySerial.print(adc);
    mySerial.write(0xff);
    mySerial.write(0xff);
    mySerial.write(0xff);
    mySerial.print("bar.val=");
    int bar=map(adc,0,1023,0,100);
    bar=constrain(bar,0,100);
    mySerial.print(bar);
    mySerial.write(0xff);
    mySerial.write(0xff);
    mySerial.write(0xff);
    time1=millis();
  }
   adc1=analogRead(an);
   if(adc1>(adc2+threshold)||adc1<(adc2-threshold))
   {
    mySerial.print("va0.val=");
    int va=map(adc1,0,1023,0,270);
    mySerial.print(va);
    mySerial.write(0xff);
    mySerial.write(0xff);
    mySerial.write(0xff);
    adc2=adc1;
   }
   /*
    if((unsigned long)millis()-time2>50)
    {
      mySerial.print("va0.val=");
      int va=map(analogRead(an),0,1023,0,270);
      mySerial.print(va);
      mySerial.write(0xff);
      mySerial.write(0xff);
      mySerial.write(0xff);
      time2=millis();
    }
    
  */
  
}
