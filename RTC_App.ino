/*
  DS1307 RTC (Real-Time-Clock) Example

  Uno       A4 (SDA), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
 */

#include <Wire.h>
#include <DS1307.h>
#define buz 2
#define gnd 5

DS1307 rtc;


void setup()
{
  //init Serial port
  Serial.begin(9600);
  pinMode(buz,OUTPUT);
  pinMode(gnd,OUTPUT);
  digitalWrite(gnd,LOW);
  //init RTC
  Serial.println("Init RTC...");

  //only set the date+time one time
   //rtc.set(40, 22, 20, 11, 8, 2018); //08:00:00 24.12.2014 //sec, min, hour, day, month, year

  //stop/pause RTC
  // rtc.stop();

  //start RTC
  rtc.start();
}


void loop()
{
  uint8_t sec1, min1, hour1, day1, month1;
  uint16_t year1;

  //get time from RTC
  rtc.get(&sec1, &min1, &hour1, &day1, &month1, &year1);

  //serial output
  Serial.print("\nTime: ");
  Serial.print(hour1, DEC);
  Serial.print(":");
  Serial.print(min1, DEC);
  Serial.print(":");
  Serial.print(sec1, DEC);

  Serial.print("\nDate: ");
  Serial.print(day1, DEC);
  Serial.print(".");
  Serial.print(month1, DEC);
  Serial.print(".");
  Serial.print(year1, DEC);
  /*
  if(hour1==20&&min1==23&&sec1>=0&&sec1<=30)
  {
    digitalWrite(buz,HIGH);
  }else digitalWrite(buz,LOW);
  */

  /*
  if(hour1%10==0&&min1==0&&sec1==0)
  {
    digitalWrite(buz,HIGH);
  }else digitalWrite(buz,LOW);
  //wait a second
  */
  //delay(1000);


}
