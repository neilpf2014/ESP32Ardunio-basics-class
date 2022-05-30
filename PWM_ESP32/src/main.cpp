/*
 * Example 8 for ESP 32 programing class
 * PWM LED - use external LED on GPIO 16
 * Will use ESP32 "LED" PWM
 * This will not work on other hardware
 * NF 2022-05-28.
 */

#include <Arduino.h>
#define LED_PIN 16  /* GPIO16 */


/* Setting ESP32 PWM Properties */
#define PWM_FREQ  5000 /* 5 KHz */
#define PWM_CHANNEL 0
#define PWMResolution 10

uint32_t dutyCycle;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);

void setup()
{  
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWMResolution);
  /* Attach the LED PWM Channel to the GPIO Pin */
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}
void loop()
{
  /* Increasing the LED brightness with PWM */
  for(dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++)
  {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(3);
    //delayMicroseconds(100);
  }
      /* Decreasing the LED brightness with PWM */
  for(dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(3);
    //delayMicroseconds(100);
  }
}