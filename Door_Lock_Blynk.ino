//Arafa Microsys
//www.youtube.com/arafamicrosystems
//www.fb.com/arafa.microsys
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <EEPROM.h>
#include <Servo.h>

Servo myservo;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d475dd9903e94fa3840b55f2e883af94";

void setup()
{
  EEPROM.begin(512);
  Serial.begin(9600);
  myservo.attach(4);
  myservo.write(180);
  WiFiManager wifiManager;
  //wifiManager.resetSettings();    //Uncomment this to wipe WiFi settings from EEPROM on boot.  Comment out and recompile/upload after 1 boot cycle.
  wifiManager.autoConnect("NodeMCU");
  //if you get here you have connected to the WiFi
  Serial.println("connected...:)");
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output, I like blinkies.
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
  Blynk.virtualWrite(V0, "Door State");
  if(pinValue)
  {
    Blynk.virtualWrite(V1, "Open");
    servo();
    
  }else 
  {
    Blynk.virtualWrite(V1, "Closed");
    myservo.write(180);
  }
  
}

void loop()
{
  Blynk.run();  // Commented out for a short time.

}

void servo()
{
  myservo.write(90);
}

