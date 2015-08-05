#include <eHealth.h>

extern volatile unsigned long timer0_overflow_count;
float fanalog0;
int analog0;
unsigned long time;
byte serialByte;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(1)
  {        
    fanalog0=eHealth.getSkinConductance();  
    Serial.println(fanalog0,5);
    delay(20);
  }
}
