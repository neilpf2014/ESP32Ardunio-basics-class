/*
 * Example 5 for ESP 32 programing class
 * Serial demo code
 * Modification of button code
 * Read a button cycle
 * Flash LED
 * Send back some info via serial when button is pushed
 * NF 2022-05-28.
 */

#include <Arduino.h>

// comment out for onboard LED
#define LED_BUILTIN 2
// define base blink period
#define BASE_PERIOD 1000
// define debounce period
#define DEBOUNCE_DELAY 20
// define button GPIO
#define BUTTON_PIN 19

// last timer update LED
uint64_t PastMils;
// last timer update debounce
uint64_t DebouncePastMils;
// led on/off
bool CurLEDState;
// current button state
uint8_t CurBtnState;
// button transition count
uint32_t BtnCycles;
// LED on/off time mills
uint32_t LEDperiod;
uint32_t theHz;


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

// read button and check for state change, increment cycle cnt, with debounce
uint32_t btnCycle(uint32_t CycleCnt, uint8_t &LastState, uint64_t &DbTime)
{
  uint8_t ButnState;
  if (millis() > (DbTime + DEBOUNCE_DELAY))
  {
    ButnState = digitalRead(BUTTON_PIN);
    // high to low (button going up)
    if((ButnState == 1) & (LastState == 0))
      CycleCnt++;
    // low to high (button going up)
    if((ButnState == 0) & (LastState == 1))
      CycleCnt++;
    LastState = ButnState;
    DbTime = millis();
  }
  return CycleCnt;
}

void setup()
{
  // initialize serial port
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  CurLEDState = true;
  // attach button GPIO
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  LEDperiod = BASE_PERIOD;
  BtnCycles = 0;
  Serial.println("Started run");
  delay(100);
}

void loop()
{
  if (millis() > (PastMils + LEDperiod))
  {
      CurLEDState = toggleLed(CurLEDState);
      PastMils = millis();
  }
  // check for button state change
  BtnCycles = btnCycle(BtnCycles,CurBtnState,DebouncePastMils);
 
  // button has gone though 2 state changes
  // off-on on-off, speed up the led flashing
  if (BtnCycles > 1)
  {
    LEDperiod = LEDperiod / 2;
    theHz = 1000/LEDperiod;
    BtnCycles = 0;
    Serial.print("blink rate: ");
    Serial.print(theHz);
    Serial.println(" Hz");
    Serial.print(millis());
    Serial.println(" run time ms");
    Serial.println("");
  }
  
  // reset back to base if below 2 ms
  if (LEDperiod < 2)
    LEDperiod = BASE_PERIOD;
}