//https://www.youtube.com/arafamicrosystems
#include <MaxMatrix.h>
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 5;   // CLK pin of MAX7219 module
int CS = 6;    // CS pin of MAX7219 module
int maxInUse = 1;
MaxMatrix m(DIN, CS, CLK, maxInUse); 
char A[] = {4, 8,  //4 Column, 8 Row
            B01111110,
            B00010001,
            B00010001,
            B01111110,
           };
char B[] = {4, 8,
            B01111111,
            B01001001,
            B01001001,
            B00110110,
           };
char H[] = {4, 8,  //4 Column, 8 Row
            B01111110,
            B00010000,
            B00010000,
            B01111110,
           };
char R[] = {4, 8,  //4 Column, 8 Row
            B01111111,
            B00011001,
            B00101001,
            B01001111,
           };
char smile01[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10100001,
                  B10100001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile02[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10010001,
                  B10010001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile03[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10100101,
                  B10010001,
                  B10010001,
                  B10100101,
                  B01000010,
                  B00111100
                 };

char heart[] = {8, 8,
                  B00001100,
                  B00010010,
                  B00100001,
                  B01000010,
                  B01000010,
                  B00100001,
                  B00010010,
                  B00001100
                 };
void setup() {
  m.init(); // MAX7219 initialization
  m.setIntensity(15); // initial led matrix intensity, 0-15
  //m.setDot(7,5,true);//Column,Row
  m.writeSprite(2, 0, A);
  delay(500);
  shift();
  m.writeSprite(2, 0, B);
  delay(500);
  shift();
  m.writeSprite(0, 0, smile01);
  delay(500);
  m.writeSprite(0, 0, smile02);
  delay(500);
  m.writeSprite(0, 0, smile03);
  delay(500);
}
void loop() 
{
   
}

void shift()
{
  for (int i=0; i<8; i++)
  {
    m.shiftLeft(false,false);
    delay(200);
  }
  m.clear();
}
