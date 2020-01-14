int i=3;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for(int i=0;i<2;i++)
  {
    if(i==1)
    {
      Serial.println("Value = 1");
    }
  }
  Serial.println(i);
  delta();
  while(1);
}

void delta()
{
  int i=5;
  Serial.println(i);
}
