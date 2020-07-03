//progr am untuk pendeteksi kebisingan 
//edited by : IDNmakerspace Algorithm Factory

#include <FreqMeasure.h>

int led = 4;

void setup() 
{
  Serial.begin(9600);
  FreqMeasure.begin();
  pinMode(4, OUTPUT);
}

double sum=0;
int count=0;
bool state = false; 
float frequency;
int continuity =0;

void loop() 
{
  if (FreqMeasure.available()) 
  {
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 100) 
     {
      frequency = FreqMeasure.countToFrequency(sum / count);
      Serial.println(frequency); 
      sum = 0;
      count = 0;
      }
  }
    if (frequency>1800 && frequency<2000)
  { 
    continuity++;
    Serial.print("Continuity -> ");
    Serial.println(continuity);
    frequency=0;
   }
    if (continuity >=3 && state==false)
       {
        state = true;
        continuity=0; 
        Serial.println("Light Turned ON");
        delay(1000);
       }

    if (continuity >=3 && state==true)
      {
        state = false;
        continuity=0;
        Serial.println("Light Turned OFF");
        delay(1000);
       }

    digitalWrite(LED_BUILTIN, state);
}
