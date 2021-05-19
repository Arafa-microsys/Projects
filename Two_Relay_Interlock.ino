#define relay1 12
#define relay2 13
#define sw1 4
#define sw2 5

void setup() {
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
}

void loop() 
{
  if(digitalRead(sw1)==LOW||digitalRead(sw2)==HIGH)
  {
    delay(10);
    digitalWrite(relay2,LOW);
    digitalWrite(relay1,HIGH);
  }else if(digitalRead(sw1)==HIGH||digitalRead(sw2)==LOW)
  {
    delay(10);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay1,LOW);
  }else
  {
    digitalWrite(relay2,LOW);
    digitalWrite(relay1,LOW);
  }
}
