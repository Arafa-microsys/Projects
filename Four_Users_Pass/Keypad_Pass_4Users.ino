//Please mention the source if you used the code
//The Sourcs: https://www.youtube.com/user/arafamicrosystems
//Code Created By: Eng. Hossam Arafa 
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
#define led 13
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
bool mask=0;
char userN,userN1,passN;
char pass[4][6];
char check[4][6];
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 1);
  MemExt();
  welcome();
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if (customKey=='A')
  {
    setP();
    mask=1;
  }else if(customKey=='B')
  {
    EntP();
    mask=1;
  }else if(customKey=='C')
  {
    ClearP();
    mask=1;
  }
  
}

void welcome()
{
  lcd.setCursor(0,0);
  lcd.print("SetP EntP ClearP");
  lcd.setCursor(0,1);
  lcd.print(" A     B    C  ");
  
}

void setP()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Select User No ");
  lcd.setCursor(0,1);
  lcd.print("  From 1 to 4  ");
  delay(1500);
  lcd.setCursor(0,0);
  lcd.print("Then press #    ");
  lcd.setCursor(0,1);
  lcd.print("User No=        ");
  
  lable2:
  userN=customKeypad.getKey();
  if(userN=='#')
  {
    goto lable1;
  }else if(userN>0&&userN>='1'&&userN<='4')
  {
    lcd.setCursor(9,1);
    lcd.print(userN);
    userN1=userN;
  }
  goto lable2;
  lable1:
  CreatePass(userN1);
}

void EntP()
{
  char UserNo=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter the userNo");
  lcd.setCursor(0,1);
  lcd.print("(");
  lcd.setCursor(4,1);
  lcd.print(")Then Press#");
  byte UserNo1;
  loop11:
  char us=customKeypad.getKey();
  if(us!='#'&&us>='0'&&us<='4')
  {
    lcd.setCursor(2,1);
    lcd.print(us);
    UserNo=us;
    UserNo1=UserNo-'0';
    
  }else if(us=='#')
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter the Pass  ");
    byte i=0;
    lcd.setCursor(0,1);
    loop12:
    char no=customKeypad.getKey();
    if(no>='0'&&no<='9')
    {
      check[UserNo1-1][i]=no;
      lcd.print('*');
      i++;
      if(i<6)
      {
        goto loop12;
      }else if(i==6)
      {
        delay(1500);
        goto loop13;
      }
    }else goto loop12;
    
  }
  goto loop11;
  loop13:
  passCh(UserNo1);
  
}

void passCh(byte Uno)
{
  byte ch=0;
  for(int i=0;i<6;i++)
  {
    if(pass[Uno-1][i]==check[Uno-1][i])
    {
      ch++;
    }
  }
  if(ch==6)
  {
    if((Uno-1)==0)
    {
      userone();
    }else if((Uno-1)==1)
    {
      usertwo();
    }else if((Uno-1)==2)
    {
      userthree();
    }else if((Uno-1)==3)
    {
      userfour();
    }
  }else 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wrong Password  ");
  }
  setup();
}

void ClearP()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("To Clear Pass   ");
  lcd.setCursor(0,1);
  lcd.print("Select User(");
  lcd.setCursor(13,1);
  lcd.print(") #");
  byte UserNo1;
  char UserNo;
  loop11:
  char us=customKeypad.getKey();
  if(us!='#'&&us>='0'&&us<='4')
  {
    lcd.setCursor(12,1);
    lcd.print(us);
    UserNo=us;
    UserNo1=UserNo-'0';
    
  }else if(us=='#')
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter the Pass  ");
    byte i=0;
    lcd.setCursor(0,1);
    loop12:
    char no=customKeypad.getKey();
    if(no>='0'&&no<='9')
    {
      check[UserNo1-1][i]=no;
      lcd.print('*');
      i++;
      if(i<6)
      {
        goto loop12;
      }else if(i==6)
      {
        delay(1500);
        goto loop13;
      }
    }else goto loop12;
  }
  goto loop11;
  loop13:
  passCh1(UserNo1);
}

void passCh1(byte Uno)
{
  byte ch=0;
  for(int i=0;i<6;i++)
  {
    if(pass[Uno-1][i]==check[Uno-1][i])
    {
      ch++;
    }
  }
  if(ch==6)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    clearPass(Uno);
    lcd.print("Password Cleared");
    
    
  }else 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wrong Password  ");
  }
  delay(1000);
  setup();
}

void clearPass(byte User)
{
  User=User-1;
  if(User==0)
  {
    EEPROM.write(0,0);
  }else if(User==1)
  {
    EEPROM.write(1,0); 
  }else if(User==2)
  {
    EEPROM.write(2,0);
  }else if(User==3)
  {
    EEPROM.write(28,0);
  }
  
}
void CreatePass(char user)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ent Pass User ");
  lcd.print(user);
  lcd.print("      ");
  if(user=='1')
  {
    byte value= EEPROM.read(0);
    if(value==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pass found      ");
      lcd.setCursor(0,1);
      lcd.print("Goto Clear Pass ");
      delay(4000);
      goto loop4;
    }
    byte i=0;
    lcd.setCursor(0,1);
    loop3:
    passN=customKeypad.getKey();
    if(passN>0&&passN>='0'&&passN<='9')
    {
      pass[0][i]=passN;
      EEPROM.update(i+3,passN);
      i++;
      lcd.print('*');
      if(i==6)delay(1500);
    }
    if(i==6)
    {
      goto loop5;
    }else goto loop3;
    loop5:
    EEPROM.write(0,1);
    delay(20);
    message();
    loop4:
    int m=0;
  }else if(user=='2')
  {
    byte value= EEPROM.read(1);
    if(value==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pass found      ");
      lcd.setCursor(0,1);
      lcd.print("Goto Clear Pass ");
      delay(4000);
      goto loop6;
    }
    byte i=0;
    lcd.setCursor(0,1);
    loop8:
    passN=customKeypad.getKey();
    if(passN>0&&passN>='0'&&passN<='9')
    {
      pass[1][i]=passN;
      EEPROM.update(i+9,passN);
      i++;
      lcd.print('*');
      if(i==6)delay(1500);
    }
    if(i==6)
    {
      goto loop7;
    }else goto loop8;
    loop7:
    EEPROM.write(1,1);
    delay(20);
    message();
    loop6:
    int m=0;
  }else if(user=='3')
  {
    byte value= EEPROM.read(2);
    if(value==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pass found      ");
      lcd.setCursor(0,1);
      lcd.print("Goto Clear Pass ");
      delay(4000);
      goto loop9;
    }
    byte i=0;
    lcd.setCursor(0,1);
    loop10:
    passN=customKeypad.getKey();
    if(passN>0&&passN>='0'&&passN<='9')
    {
      pass[2][i]=passN;
      EEPROM.update(i+15,passN);
      i++;
      lcd.print('*');
      if(i==6)delay(1500);
    }
    if(i==6)
    {
      goto loop11;
    }else goto loop10;
    loop11:
    EEPROM.write(2,1);
    delay(20);
    message();
    loop9:
    int m=0;
  }else if(user=='4')
  {
    byte value= EEPROM.read(28);
    if(value==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pass found      ");
      lcd.setCursor(0,1);
      lcd.print("Goto Clear Pass ");
      delay(4000);
      goto loop18;
    }
    byte i=0;
    lcd.setCursor(0,1);
    loop19:
    passN=customKeypad.getKey();
    if(passN>0&&passN>='0'&&passN<='9')
    {
      pass[3][i]=passN;
      EEPROM.update(i+21,passN);
      i++;
      lcd.print('*');
      if(i==6)delay(1500);
    }
    if(i==6)
    {
      goto loop20;
    }else goto loop19;
    loop20:
    EEPROM.write(28,1);
    delay(20);
    message();
    loop18:
    int m=0;
  }
  setup();
}


void message()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pass Created");
  lcd.setCursor(0,1);
  lcd.print("Successfully");
}

void MemExt()
{
  for(int i=0;i<6;i++)
  {
    pass[0][i]=EEPROM.read(3+i);
    pass[1][i]=EEPROM.read(9+i);
    pass[2][i]=EEPROM.read(15+i);
    pass[3][i]=EEPROM.read(21+i);
  }
  
}

void userone()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Pass 1 Correct ");
    digitalWrite(led,HIGH);
    delay(1500);
    digitalWrite(led,LOW);
}

void usertwo()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Pass 2 Correct ");
    digitalWrite(led,HIGH);
    delay(1500);
    digitalWrite(led,LOW);
}

void userthree()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Pass 3 Correct ");
    digitalWrite(led,HIGH);
    delay(1500);
    digitalWrite(led,LOW);
}

void userfour()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Pass 4 Correct ");
    digitalWrite(led,HIGH);
    delay(1500);
    digitalWrite(led,LOW);
}
