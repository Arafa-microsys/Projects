#define pirSensor 2
#define led 13
byte mask=1;
void setup() 
{
  Serial.begin(9600);
  pinMode(pirSensor, INPUT);
  pinMode(led, OUTPUT);  
}
void loop() {
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) 
  {
    if(mask==1)
    {
      Serial.println("Motion Detect.");
      mask=0;
    }
    
    digitalWrite(led, HIGH); // The Relay Input works Inversly
  }else
  {
    mask=1;
    digitalWrite(led, LOW);
  }
}
