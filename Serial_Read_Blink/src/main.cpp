#include <Arduino.h>
/*
 * Example 6 for ESP 32 programing class
 * Serial demo code
 * Modification of blink Code
 * Non blocking Serial read and 
 * modify flash rate based on it
 * NF 2022-05-28.
 */

// #define LED_BUILTIN 2

// define base blink period
#define BASE_PERIOD 1000
// buffer size for serial read
#define BUF_LEN 15

// last timer update LED
uint64_t PastMils;
// led on/off
bool CurLEDState;
// LED on/off time mills
uint32_t LEDperiod;
char buffer[BUF_LEN];// buffer for serial read
uint32_t i; //buffer cur char index
bool inputEnd;

// read chars from serial (non-blocking)
// will return done=true when end of buffer or return char
void readSerial(char serData[], uint32_t& i, bool done)
{
  char Ch = 'a';
  done = false;
	if (i < BUF_LEN)
	{
		while ((Serial.available() > 0))
		{
			Ch = Serial.read();
			if ((Ch != '\n') && (Ch != '\r') && (i < BUF_LEN)) //need to trap both <CR> & <LF> !
			{
				serData[i] = Ch;
				i++;
			}
			Serial.print(Ch); // echo to terminal
      if ((Ch == '\n') || (Ch == '\r')|| (i >= BUF_LEN))
      {
        done = true;
        Serial.println(); //echo newline/return
      }
		}
	}
  else
  {
    done =true;
    Serial.println(); //echo newline/return
  }
}

//function to toggle led on / off
bool toggleLed(bool state)
{
  bool newState;
  if (state == true)
  {
  // turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    newState = false;
  }
  else
  {
  // turn the LED off
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
  i = 0;
  inputEnd = false;
  delay(1000);
}

void loop()
{
  if (millis() > PastMils + LEDperiod)
  {
      CurLEDState = toggleLed(CurLEDState);
      PastMils = millis();
  }
 
  //serial read code here
  if (inputEnd == false)
  {
    readSerial(buffer, i, inputEnd);
  }
  else
  {
    if(buffer[0] == '+')
    {
      LEDperiod = LEDperiod / 2;
      Serial.println("led period is now " + LEDperiod);
    }
    i = 0;
    inputEnd = false;
  }
  // reset back to base if below 5 ms
  if (LEDperiod < 5)
    LEDperiod = BASE_PERIOD;
}