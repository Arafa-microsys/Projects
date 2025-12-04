#include "ThingsBoard.h"

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//D1: SCL
//D2: SDA

#define WIFI_AP             "SSID"
#define WIFI_PASSWORD       "PASS"

// See https://thingsboard.io/docs/getting-started-guides/helloworld/
// to understand how to obtain an access token
#define TOKEN               "XXXXXXXXXXXXXXXXXXX"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// the Wifi radio's status
int status = WL_IDLE_STATUS;

void setup() {
  // initialize serial for debugging
  Serial.begin(SERIAL_DEBUG_BAUD);
  delay(2000);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  mlx.begin();  
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  InitWiFi();
  //Serial.println("Dashboard URL: ");
  //Serial.println(F(""));
}

void loop() {
  

  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
  }

  if (!tb.connected()) {
    // Connect to the ThingsBoard
//    Serial.print("Connecting to: ");
//    Serial.print(THINGSBOARD_SERVER);
//    Serial.print(" with token ");
//    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Sending data...");

  float x = mlx.readObjectTempC();
  x = x + 0.05;       //123.506
  x = x*10.0; //1235.06
  int y = (int)x; //1235
  float z = (float)y/10.0; //123.5
  tb.sendTelemetryFloat("temperature",z );
  

  tb.loop();

  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  lcd.setCursor(6,0);
  lcd.print(String(mlx.readObjectTempC()));
  lcd.print("          ");
  delay(1000);
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
