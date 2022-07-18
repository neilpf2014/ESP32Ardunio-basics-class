#include <Arduino.h>

#define HOLD_MS 20
#define LED_PIN 9           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

uint32_t dutyCycle;
uint32_t LastdutyCycle;
uint64_t pastMils;


// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(LED_PIN, OUTPUT);
  pastMils = millis();
  dutyCycle = 1;
  LastdutyCycle = 0;
}

// the loop routine runs over and over again forever:
void loop() {

  /*
  // set the brightness of pin 9:
  analogWrite(LED_PIN, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
*/
  if(millis() > (pastMils + HOLD_MS))
  {
    // Going up
    if((dutyCycle > LastdutyCycle) && (dutyCycle < 255))
    {
      LastdutyCycle = dutyCycle;
      dutyCycle++;
    }
    // Going down
    if((dutyCycle < LastdutyCycle) && (dutyCycle > 0))
    {
      LastdutyCycle = dutyCycle;
      dutyCycle--;
    }
    // At top
    if (dutyCycle == 255)
    {
      LastdutyCycle = dutyCycle;
      dutyCycle--;
    }
    // At Bottom
    if (dutyCycle == 0)
    {
      LastdutyCycle = dutyCycle;
      dutyCycle++;
    }
    analogWrite(LED_PIN, dutyCycle);
  }
}