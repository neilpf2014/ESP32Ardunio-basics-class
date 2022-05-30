/*
 * Example 6 for ESP 32 programing class
 * Serial demo code
 * Modification of blink Code
 * Serial read and modify flash rate based on it
 * NF 2022-05-28.
 */

#include <Arduino.h>
// #define LED_BUILTIN 2

// define base blink period
#define BASE_PERIOD 1000
// define debounce period

// last timer update LED
uint64_t PastMils;
// led on/off
bool CurLEDState;
// LED on/off time mills
uint32_t LEDperiod;


//function to toggle led on / off
bool toggleLed(bool state)
{
  bool newState;
  if (state == true)
  {
  // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);
    newState = false;
  }
  else
  {
  // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);
    newState = true;
  }
  return newState;
}

void setup()
{
  // initialize serial port
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  CurLEDState = true;
  LEDperiod = BASE_PERIOD;
  Serial.println("Started run");
}

void loop()
{
  if (millis() > PastMils + LEDperiod)
  {
      CurLEDState = toggleLed(CurLEDState);
      PastMils = millis();
  }
 
  // put serial read code here
  if (true)
  {
    
  }
  
  // reset back to base if below 5 ms
  if (LEDperiod < 5)
    LEDperiod = BASE_PERIOD;
}