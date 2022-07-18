/*
 * Example 1 for ESP32 programing class
 * Modified Blink (also a simple state machine)
 * Turns on an LED on / off, repeatedly.
 * Non blocking version
 * NF 2022-05-28
 */

#include <Arduino.h>
// comment this out if using board with standard LED
#define LED_BUILTIN 2
// define blink period
#define PERIOD 1000

// Var to hold last timer update
uint64_t PastMils;
// hold whether led on/off
bool CurState;

// function to toggle led on / off
bool toggleLed(bool state)
{
  bool newState;
  if (state == true)
  {
  // turn the LED on pin signal HIGH
    digitalWrite(LED_BUILTIN, HIGH);
    newState = false;
  }
  else
  {
  // turn the LED off by making the pin signal LOW
    digitalWrite(LED_BUILTIN, LOW);
    newState = true;
  }
  return newState;
}

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  CurState = true;
}

void loop()
{
  if (millis() > (PastMils + PERIOD))
  {
      CurState = toggleLed(CurState);
      PastMils = millis();
  }
}
