// Arduino pin numbers
#define SW_pin 2 // digital pin connected to switch output
#define X_pin A0 // analog pin connected to X output
#define Y_pin A1 // analog pin connected to Y output
#define led 13

void setup() {
  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print(" | ");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print(" | ");
  Serial.print("Y-axis: ");
  Serial.print(analogRead(Y_pin));
  Serial.println(" | ");
  if(analogRead(A0)>900&&analogRead(A0)<=1023||digitalRead(SW_pin)==0)
  {
    delay(10);
    digitalWrite(led,HIGH);
  }else digitalWrite(led,LOW);
  delay(200);
}
