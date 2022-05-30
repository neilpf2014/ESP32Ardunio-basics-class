/*
 * Example 2 For ESP32 programing class
 * Modified Blink (also a simple state machine)
 * read a button press
 * Stop blinking if button is down
 * NF 2022-5-28
 */

#include <Arduino.h>
// #define LED_BUILTIN 2
// define blink period
#define PERIOD 100
// define button GPIO
#define BUTTON_PIN 19

// Var to hold last timer update
uint64_t PastMils;
// hold whether led on/off
bool CurState;
uint8_t ButnState;

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
  ButnState = 0;
  // attach button GPIO
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  if (millis() > PastMils + PERIOD)
  {
      CurState = toggleLed(CurState);
      PastMils = millis();
  }
  //read button
  ButnState = digitalRead(BUTTON_PIN);
  // keep led lit as long as button is pressed
  if(ButnState == 1)
    digitalWrite(LED_BUILTIN, HIGH);
}