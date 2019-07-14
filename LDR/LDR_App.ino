#define an A0
#define led 13
float value=0;
unsigned long res=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() 
{
  value=analogRead(an);
  value=(value/1023)*5;
  res=(1000*value)/(5-value);
  Serial.println(res);
  if(res>=30000)
  {
    digitalWrite(led,HIGH);
  }else digitalWrite(led,LOW);
  delay(100);
}
