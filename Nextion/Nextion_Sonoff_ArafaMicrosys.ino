//Created By: Eng.Hossam Arafa
//https://www.youtube.com/user/arafamicrosystems
//Explanation Video: https://youtu.be/srOZZfNpim8

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>


// Fingerprint for demo URL, expires on June 2, 2019, needs to be updated well before this date
// convert : to ,
const uint8_t fingerprint[20] = {0xAA, 0x75, 0xCB, 0x41, 0x2E, 0xD5, 0xF9, 0x97, 0xFF, 0x5D, 0xA0, 0x8B, 0x7D, 0xAC, 0x12, 0x21, 0x08, 0x4B, 0x00, 0x8C};

ESP8266WiFiMulti WiFiMulti;
//Smart_Plug
String FirstDeviceOn="https://maker.ifttt.com/trigger/smart_plug_on/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";
String FirstDeviceOff="https://maker.ifttt.com/trigger/smart_plug_off/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";
//mini
String SecondDeviceOn="https://maker.ifttt.com/trigger/mini_on/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";
String SecondDeviceOff="https://maker.ifttt.com/trigger/mini_off/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";
//basic
String ThirdDeviceOn="https://maker.ifttt.com/trigger/basic_on/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";
String ThirdDeviceOff="https://maker.ifttt.com/trigger/basic_off/with/key/gfKJK1XPPGCs-wknJd-L1F3wOeXsOy9IBAKQJTuFnG4";

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.setTimeout(250);
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Arafa", "ahlyegypt");//SSID and Pass of your WiFi Network
}

void httpRequest(String x)
{
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);

    HTTPClient https;
    
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, x)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
}

void loop() {
  // wait for WiFi connection
  
    if(Serial.available())
    {
      String income=Serial.readString();
      if(income[0]=='F')
      {
        Serial.println("Device 1");
        if(income[1]=='1')
        {
          Serial.println("Activate Smart_Plug");
          httpRequest(FirstDeviceOn);
        }else if(income[1]=='0')
        {
          Serial.println("Deactivate Smart_Plug");
          httpRequest(FirstDeviceOff);
        }
      }else if(income[0]=='S')
      {
        Serial.println("Device 2");
        if(income[1]=='1')
        {
          Serial.println("Activate Mini");
          httpRequest(SecondDeviceOn);
        }else if(income[1]=='0')
        {
          Serial.println("Deactivate Mini");
          httpRequest(SecondDeviceOff);
        }
      }else if(income[0]=='T')
      {
        Serial.println("Device 3");
        if(income[1]=='1')
        {
          Serial.println("Activate Basic");
          httpRequest(ThirdDeviceOn);
        }else if(income[1]=='0')
        {
          Serial.println("Deactivate Basic");
          httpRequest(ThirdDeviceOff);
        }
      }
    }
    
}
