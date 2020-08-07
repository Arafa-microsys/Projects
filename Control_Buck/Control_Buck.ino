//Coding by Eng.Hossam Arafa
//https://www.youtube.com/user/arafamicrosystems
#define pwm 9
void setup() 
{
  Serial.begin(115200);
  TCCR1B = TCCR1B & B11111000 | B00000001; // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
  pinMode(pwm,OUTPUT);
  delay(2000);

  for(int i=255;i>=0;i--)
  {
    analogWrite(pwm,i);
    Serial.println(i);
    delay(100);
  }
  for(int i=0;i<256;i++)
  {
    analogWrite(pwm,i);
    Serial.println(i);
    delay(100);
  }
}

void loop() 
{
  
  
}
