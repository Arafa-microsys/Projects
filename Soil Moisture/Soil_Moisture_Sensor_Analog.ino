#define an A0
int value=0,moisture=0;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  value=analogRead(an);
  moisture=map(value,1017,100,0,100);
  Serial.print("Soil Moisture % = ");
  Serial.print(moisture);
  Serial.println("%");
  
  delay(100);
}
