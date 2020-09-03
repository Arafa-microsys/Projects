//https://www.youtube.com/user/arafamicrosystems

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS1 300
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS1];
char auth[] = "0McpJfXT5mpH4TF9yGkmLpD5LQZhMhYz";
char ssid[] = "Arafa";
char pass[] = "ahlyegypt";
#define PIN1 D2
int data=255;
int mod=0;
int delay1=0;
int r,g,b;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
}

BLYNK_WRITE(V0)
{
data = param.asInt(); 
static1(r, g, b,data);
}

BLYNK_WRITE(V1)
{
  if(mod==0)
  {
    r = param[0].asInt();
    g = param[1].asInt();
    b = param[2].asInt();
    static1(r, g, b,data);
  }
  
}

BLYNK_WRITE(V2)
{
mod = param.asInt(); 
}

BLYNK_WRITE(V3)
{
delay1 = param.asInt(); 
}

void loop()
{
  Blynk.run();
  if(mod==1)
  {
    for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS1; i++) {
      leds1[i] = CHSV(i - (j * 2), data, 255); /* The higher the value 4 the less fade there is and vice versa */ 
    }
    FastLED.show();
    delay(delay1); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
  }
  }
}

void static1(int r, int g, int b,int brightness)
{
  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

//https://www.youtube.com/user/arafamicrosystems
 
