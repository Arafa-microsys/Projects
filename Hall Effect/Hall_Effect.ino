#define sensor 2

void setup() 
{
  Serial.begin(115200);
  pinMode(sensor,INPUT);
}

void loop() 
{
  Serial.println(digitalRead(sensor));
  delay(100);
}
