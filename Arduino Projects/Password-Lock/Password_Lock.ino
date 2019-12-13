// Code Written by Arafa Microsystem
// Interfacing Between Arduino Keypad and LCD to Password Lock App
//www.youtube.com/arafamicrosystems


#include "Keypad.h" 
#include <LiquidCrystal.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const int led=8; // Connected the Green LED on Pin 8 
int delay1=3000; // Delay Value are used
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// pin 12 RW pin
// pin 11 EN pin , D4=22 , D5=24 , D6=26 , D7=28
int c=0; // flag1 used to check The Password
int i=0; //flag2 used to Limiting The Password Letters
int error=0; //flag3 Check if Invalid Password it Reached Specific Value
char keys[ROWS][COLS] =
 {{'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}}; // Keypad Form
  
char pass[]={'A','B','C','D','#','*'}; // The Password 
char newpass[6];  // New Array That's Carried The typed Password
byte rowPins[ROWS] = {
  31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  39, 41, 43, 45}; //connect to the column pinouts of the keypad
int count=0;
int f=0; // to Enter Clear Display one time
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup()
{
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0,0); // Set Cursor to Row 0 Column 0 16x2 LCD
  // Intro Message
  lcd.print("   Hint:If you  ");
  lcd.setCursor(0,1);
  lcd.println("Enter Wrong Pass");
  delay(delay1);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  After 5 Times ");
  lcd.setCursor(0,1);
  lcd.println("Wt 5s to Retries");
  delay(delay1);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter The Pass");
  lcd.setCursor(0,1);
  lcd.print("Please?");
  delay(delay1);
  
 
}

 void print1()
 {
   // it's Function Using to Display The Password Screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter The Pass");
    lcd.setCursor(0,1);
    lcd.print("Please?");
 }
 
void loop()
{
  char key = keypad.getKey();
  if(key != NO_KEY&&i<6)
  {
    if(f==0)
    {
      lcd.clear(); // Clear Everything On the LCD
      f=1;
    }
   lcd.setCursor(0,0);
   lcd.print("Password:");
   lcd.setCursor(i,1);
   lcd.print("*");  // Display '*' For Every Charachter 
   newpass[i]=key;
   if(newpass[i]==pass[i])c++;
   i++;
  }
  
  if(c==6)
  {
    // If all charachters entered by User are Correct(Equal to Set Password)
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Correct Password");
    digitalWrite(led,HIGH);
    delay(2000);
    digitalWrite(led,LOW);
    char newpass[]={'0','0','0','0','0','0'}; // Clear The Value of password entered by user.
    print1();
    c=0;
    i=0;
    f=0;
  }else if(c<6&&i==6)//Invalid Password Function
  {
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Invalid Password");
    delay(1000);
    i=0;
    c=0;
    error++;
    if(error<5)
    {
      print1();
    }
    f=0;
  }
  
  if(error==5)// Error Function
  {
    // if invalid states reached 5 times Entry The Function
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You Ent Invalid ");
    lcd.setCursor(0,1);
    lcd.print(" Pass 5 Times");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wait until 5 Sec");
    delay(5000);
    error=0;
    print1();
    f=0;
  } 

  
  
}
