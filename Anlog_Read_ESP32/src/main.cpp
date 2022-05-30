/*
 * Example 7 for ESP 32 programing class
 * Simple Analog read example
 * Read and report value over serial
 * NF 2022-05-28.
 */

#include <Arduino.h>
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
#define A_PIN 34
// Delay in Ms
#define DELAY_PER 500

// variable for storing the potentiometer value
uint32_t potValue = 0;
// For loop timing
uint64_t PastMils;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println('Ready');
}

void loop() {
  // Reading potentiometer value
  if (millis() > (PastMils + DELAY_PER))
  {
      potValue = analogRead(A_PIN);
      Serial.println('Run time:' + millis());
      Serial.println('Read is ' + potValue);
      PastMils = millis();
  }
}
