//By Eng. Hossam Arafa - Arafa Microsys

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define POT_PIN A0
                                      // FREQ_MAX > FREQ_MIN
const float FREQ_MIN = 10000.0;       //Min = 122.07 Hz
const float FREQ_MAX = 8000000.0;     //Max = 8Mhz Min = 122.07 Hz 

const float FILTER = 0.05; //if FILTER = 1.0   Exponential Moving Average = OFF       if FILTER = 0.05 Smooth Change

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float smoothFreq = FREQ_MIN;

void DrawOLED(float freq)
{
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(4);
    display.setCursor(0, 0);

    if (freq >= 1000000.0)
    {
        display.print(freq / 1000000.0, 2);

        display.setTextSize(1);
        display.setCursor(102, 24);
        display.print("MHz");
    }
    else
    {
        float kHz = freq / 1000.0;

        if (kHz < 100.0)
        {
            display.print(kHz, 1);
        }
        else
        {
            display.print(kHz, 0);
        }

        display.setTextSize(1);
        display.setCursor(104, 24);
        display.print("kHz");
    }

    display.display();
}

void setup()
{
    Serial.begin(115200);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();

    pinMode(9, OUTPUT);
    //CTC Mode (Clear Timer on Compare Match) - Toggle OC1A - Square Wave - Duty Cycle 50%
    TCCR1A = _BV(COM1A0); // Timer 1 on as Toggle OC1A
    TCCR1B = _BV(WGM12) | _BV(CS10); // WGM12: CTC Mode     CS10:Prescaler=1

    OCR1A = 799; //Arduino starts at a 10 kHz frequency
}

void loop()
{
    int pot = analogRead(POT_PIN);

    float x = pot / 1023.0;

    float targetFreq =
        FREQ_MIN *
        pow(FREQ_MAX / FREQ_MIN, x); // To make a frequency change as a Logarithmic Change 

    smoothFreq += (targetFreq - smoothFreq) * FILTER; // Exponential Moving Average



    //fout​=FCPU/(2×(OCR1A+1))    So    OCR1A=(FCPU/(2×fout​​​))−1      For Ex if you want 1MHz OCR   =(16000000Hz/2*1000000)-1=7


    long ocr =
        (16000000.0 / (2.0 * smoothFreq)) - 1.0;

    if (ocr < 0) // Prevent negative values
        ocr = 0;

    if (ocr > 65535)
        ocr = 65535;

    OCR1A = (uint16_t)ocr;

    static unsigned long t = 0; //static keeps the variable's value between successive calls to loop(), so it is initialized only once

    if (millis() - t > 200) // To Update OLED Every 200ms
    {
        t = millis();

        float realFreq =
            16000000.0 /
            (2.0 * (OCR1A + 1)); // Recalculate the actual output frequency to account for OCR1A integer rounding.
            //e.g. Desired Freq = 1.234567 MHz    calculated OCR1A = 5.48   but reg save it as 5 after rounding so Real Freq = 1.333333

        Serial.print("Freq = ");

        if (realFreq >= 1000000.0)
        {
            Serial.print(realFreq / 1000000.0, 3);
            Serial.println(" MHz");
        }
        else
        {
            Serial.print(realFreq / 1000.0, 1);
            Serial.println(" kHz");
        }

        DrawOLED(realFreq);
    }
}
