// 74XX4051 ADDRESS PINS :
#define S0 2
#define  S1 3
#define  S2 4

// 74XX4051 ANALOG PIN :
#define  Z A0
int analogVal[8];
void setup()
{
  // CONFIGURE ADDRESS PINS
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  Serial.begin(115200);
}

void loop () 
{
  // LOOP THROUGH ALL THE ADDRESSES
  for (int count=0;count<8;count++)
  {
     // SET THE ADDRESS
     digitalWrite(S0, bitRead(count, 0) );
     digitalWrite(S1, bitRead(count, 1) );
     digitalWrite(S2, bitRead(count, 2) );
     // READ THE ANALOG FOR THAT ADDRESS
     int reading = analogRead(Z);
     // SERIAL OUTPUT
     // print something like : A0-### value
     Serial.print("bit");
     Serial.print(count);
     Serial.print("=");
     Serial.print(reading);
     Serial.print("  ");
     delay(100);
   }
   Serial.println();Serial.println();
  
}
