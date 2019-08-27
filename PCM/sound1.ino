/*
Arduino Based Music Player

 This example shows how to play three songs from SD card by pressing a push button

 The circuit:
 * Push Button on pin 2 and 3
 * Audio Out - pin 9
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 

 created  25 Jun 2017
 by Aswinth Raj

 This example code was created for CircuitDigest.com

 */
 
#include "SD.h" //Lib to read SD card
#include "TMRpcm.h" //Lib to play auido
#include "SPI.h" //SPI lib for SD card
#define led 13
#define SD_ChipSelectPin 4 //Chip select is pin number 4
TMRpcm music; //Lib object is named "music"


void setup(){
  pinMode(led,OUTPUT);
music.speakerPin = 9; //Auido out on pin 9
Serial.begin(9600); //Serial Com for debugging 
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

music.setVolume(5);    //   0 to 7. Set volume level 5&1 or 6&0
music.quality(1);        //  Set 1 for 2x oversampling Set 0 for normal
//music.volume(0);        //   1(up) or 0(down) to control volume
music.play("1.wav"); //plays a file starting at 30 seconds into the track    
}

void loop()
{ 
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
