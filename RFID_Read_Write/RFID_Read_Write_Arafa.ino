//https://www.youtube.com/arafamicrosystems
#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library
#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

void setup() 
{
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("Scan a MIFARE Classic card");
  for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
}
int block=8;//this is the block number we will write into and then read.
//Do not write into 'sector trailer' block, since this can make the block unusable.                       
byte blockcontent[16] = {"Ahmed___________"};//an array with 16 bytes to be written into one of the 64 card blocks
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//all zeros. This can be used to delete a block.
byte readbackblock[18];//This array is used for reading out a block. 
//The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.
void loop()
{   
  // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;
  }
  Serial.println("card selected");         
  writeBlock(block, blockcontent);//the blockcontent array is written into the card block
  readBlock(block, readbackblock);//read the block back
  Serial.print("read block: ");
  for (int j=0 ; j<16 ; j++)//print the block contents
  {
    Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
  }
  Serial.println();
  
}
