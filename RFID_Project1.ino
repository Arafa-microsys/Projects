//https://www.youtube.com/arafamicrosystems
//www.fb.com/arafa.microsys
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define Buzzer 5
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
bool flag=false;
bool flag1=false;
 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  pinMode(Buzzer,OUTPUT);
  Serial.println("Approximate your Card to the Reader....");
}
void loop() 
{
  rfid1();
  if(flag)
  {
    digitalWrite(Buzzer,HIGH);
    delay(50);
    digitalWrite(Buzzer,LOW);
    delay(50);
    digitalWrite(Buzzer,HIGH);
    delay(50);
    digitalWrite(Buzzer,LOW);
    delay(1000);
    flag=false;
  }
  
} 

void rfid1()
{
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
  String UID="";
  for (byte i=0;i<rfid.uid.size;i++) 
  {
     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");// E8 07 C7 D2
     Serial.print(rfid.uid.uidByte[i], HEX);
     UID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ")); // 0E c2 12 
     UID.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  UID.toUpperCase();
  // E8 07 C7 D2
  if (UID.substring(1) == "E0 7E E5 87") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Ahmed");
    Serial.println("Authorized access");
    flag=true;
  }else if(UID.substring(1) == "9F 30 19 89")
  {
    Serial.println("Mohammed");
    Serial.println("Authorized access");
    flag=true;
  }else
  {
    Serial.println(" Access denied");
    digitalWrite(Buzzer,HIGH);
    delay(500);
    digitalWrite(Buzzer,LOW);
    delay(800);
    flag=false;
  }
  
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  
}
}
