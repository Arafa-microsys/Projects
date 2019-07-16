//LCD Date Format Application by
//https://www.youtube.com/arafamicrosystems
/*
  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * ends to +5V and ground
 */

// include the library code:
#include <LiquidCrystal.h>
#define sw1 11 //Decrease Button
#define sw2 10 //Increase Button
#define sw3 9 //Move Left Button
#define sw4 8 //Move Right Button

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
char st[]="00/00/0000";
int count=0;
void setup() {
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  pinMode(sw4,INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("      Date      ");
}

void loop() 
{
  lcd.setCursor(3, 1);
  lcd.print(st);
  delay(150);
  if(digitalRead(sw4)==LOW)
  {
    delay(10);
    while(digitalRead(sw4)==LOW);
    count++;
    if(count<=0) count=0;
    if(count==3) count=4;
    if(count==6) count=7;
    if(count>=11) count=0;
  }

  if(digitalRead(sw3)==LOW)
  {
    delay(10);
    while(digitalRead(sw3)==LOW);
    count--;
    if(count==3) count=2;
    if(count==6) count=5;
    //if(count==11) count=0;
  }
  if(digitalRead(sw2)==LOW&&count>0)
  {
    delay(10);
    while(digitalRead(sw2)==LOW);
    if(st[count-1]>='0'&&st[count-1]<'9')
    {
    st[count-1]=st[count-1]+1;
    }
    //Date Format Conditions
    if(st[0]>'3')st[0]='3';
    if(st[0]=='3'&&st[1]>'1')st[1]='1';
    if(st[3]>'1')st[3]='1';
    if(st[3]=='1'&&st[4]>'2')st[4]='2';
  }

  if(digitalRead(sw1)==LOW&&count>0)
  {
    delay(10);
    while(digitalRead(sw1)==LOW);
    if(st[count-1]>'0'&&st[count-1]<='9')
    {
    st[count-1]=st[count-1]-1;
    }
    if(st[0]>'3')st[0]='3';
    if(st[0]=='3'&&st[1]>'1')st[1]='1';
    if(st[3]>'1')st[3]='1';
    if(st[3]=='1'&&st[4]>'2')st[4]='2';
  }
  switch(count)
  {
    case 1:
    flash(1);
    break;

    case 2:
    flash(2);
    break;

    case 4:
    flash(4);
    break;

    case 5:
    flash(5);
    break;

    case 7:
    flash(7);
    break;
    case 8:
    flash(8);
    break;
    case 9:
    flash(9);
    break;
    case 10:
    flash(10);
    break;
  }
  
}

void flash(int inc)
{
  lcd.setCursor(inc+2,1);
  lcd.print(" ");
  delay(50);
}

