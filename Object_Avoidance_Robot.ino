//Created by : Eng. Hossam Arafa
//www.youtube.com/arafamicrosystems
//www.fb.com/arafa.microsys
#include <Servo.h>
#define in1 2  //Right motor pole 1
#define in2 3  //Right motor pole 2
#define in3 4  //left motor pole 1
#define in4 7  //left motor pole 1
#define ena 5  //Right motor speed
#define enb 6  //Right motor speed
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
const int trigPin = 11;//Trigger Pin of Ultrasonic
const int echoPin = 12;//Echo Pin of Ultrasonic
long duration;//used by ultrasonic Function
int distance,Cdistance,Rdistance,Ldistance;//Cdistance=center Distance Rdistance=Right Distance Ldistance=Left Distance
void setup() 
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(85);  // Initial Pos of Servo at center
}

void loop()
{
  Cdistance=ultrasonic();//take ultrasonic distance value
  if(Cdistance>30)//if greater than 30 Cm
  {
    forward();//go to forward
  }else 
  {
    if(Cdistance<=10&&Cdistance>2)reverse();// if close to object reverse to get more space to change orientation
    off();                   //stop robot
    myservo.write(35);       //Turn servo Right 
    delay(300);
    Rdistance=ultrasonic();  //get ultrasonic value at right
    myservo.write(135);      // Turn servo Left
    delay(300);
    Ldistance=ultrasonic();  //get ultrasonic value at left
    myservo.write(85);       //return to center pos
    delay(300);
    comparison(Rdistance, Ldistance); //go to Comparasion function
    off();                    // stop after execute Comparison function action
    delay(150);
  }
  // reset all variables
  Rdistance=0;
  Ldistance=0;
  Cdistance=0;
}

int ultrasonic(void)//get distance captured by ultrasonic sensor
{
  distance=0;
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance;
}

void comparison(int r, int l)//compare values of right and left Servo Pos 
{
  if(r>25||l>25)
  {
   if(r>l||r==l)
   {
     Tright90();
   }else if(l>r)
   {
     Tleft90();
   }
  }else if(r<25&&l<25)
  {
    Tleft180();
  }
}
void forward()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void off()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void Tleft90()
{
  analogWrite(ena,160);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(650);
}
void Tright90()
{
  analogWrite(ena,150);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(750);  
}

void Tleft180()
{
  analogWrite(ena,150);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1500);
}
void reverse()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(450);
}




