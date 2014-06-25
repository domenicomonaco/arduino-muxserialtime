#include "Statistic.h"
#include "Arduino.h"
#include "muxserialtime.h"

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

MuxSerialTime mux1;
MuxSerialTime mux2;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  mux1.config("potentiomeeter", "1","#", 0, 60);
  mux2.config("potentiomeeter", "2","#", 0, 60);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  mux1.putValue(sensorValue);
  mux2.putValue(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(550);                     
}
