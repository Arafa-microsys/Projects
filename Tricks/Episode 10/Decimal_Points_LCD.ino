//https://www.youtube.com/user/arafamicrosys

#define inc 2
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define dec 3
#define mov 4

LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float income=20.2;
float setPoint=0;
int BDP,ADP; //BDP 0.   ADP .0    20.2
byte state, sel;
unsigned long timet=0;
void setup() 
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Meas. Value= ");
  lcd.print(income,1);//10.21   10.2
  lcd.setCursor(0,1);
  lcd.print("Set Value= ");
  //Serial.begin(115200);
  //delay(3000);
  pinMode(inc,INPUT_PULLUP);
  pinMode(dec,INPUT_PULLUP);
  pinMode(mov,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  timet=millis();
}

void loop() 
{
  if(digitalRead(mov)==LOW)
  {
    delay(15);
    while(digitalRead(mov)==LOW);
    state++;
    if(state>2)state=1;
  }
  if(state==1)
  {
    if(digitalRead(inc)==LOW)
    {
      delay(10);
      while(digitalRead(inc)==LOW);
      BDP++;
    }else if(digitalRead(dec)==LOW)
    {
      delay(10);
      while(digitalRead(dec)==LOW);
      BDP--;
      if(BDP<0)BDP=0;
    }
  }else if(state==2)
  {
    if(digitalRead(inc)==LOW)
    {
      delay(10);
      while(digitalRead(inc)==LOW);
      ADP++;
      if(ADP>9)ADP=9;
    }else if(digitalRead(dec)==LOW)
    {
      delay(10);
      while(digitalRead(dec)==LOW);
      ADP--;
      if(ADP<0)ADP=0;
    }  
  }
  if((unsigned long)millis()-timet>500)
  {
    //BDP=10  ADP=12     10.12
    String val=String(BDP)+'.'+String(ADP);//"10.12"
    //String->Float
    setPoint=val.toFloat();//"10.12"->10.10
    //Serial.print(" SetPoint= ");
    //Serial.println(setPoint);
    lcd.setCursor(10,1);
    lcd.print(setPoint,1);
    lcd.print("    ");
    timet=millis();
    if(setPoint==income)
    {
      digitalWrite(13,HIGH);
    }else digitalWrite(13,LOW);
  }
  
}
