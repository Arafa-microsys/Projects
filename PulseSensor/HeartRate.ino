#include <LiquidCrystal.h>
#define sen    A0

int x = 0;
int y = 0;
int z = 0;
byte Heart1[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
};
byte Heart2[8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
};

LiquidCrystal lcd( 7, 8, 9, 10, 11, 12);

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, Heart1);
  lcd.createChar(1, Heart2);

  pinMode(sen, INPUT);
}
void loop(void) {

  z = 3 * x;
  lcd.print(z);
  lcd.print(" BPM  ");
  Serial.print(z);
  Serial.println( "  BPM ");
  x = 0;



  for (int i = 0 ; i < 100 ; i++ )
  {
    lcd.setCursor(0, 0);
    lcd.print("H.Rate ");
    int val = digitalRead(sen);
    //Serial.println(val);
    if (val != y)
    {
      x = x + 1;
    }
    y = val;
    delay (100);
  }

}
