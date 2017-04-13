#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>

#define BUTTON_PIN 2
#define LED_DATA_PIN A0

#define NUM_LEDS 144
CRGB leds[NUM_LEDS];

#include "modes.h"


bool chkin(){
  static bool changeable = true;
  if (changeable && digitalRead(BUTTON_PIN)) {
    changeable = false;
    mode::next();
  } else if (!changeable && !digitalRead(BUTTON_PIN)) {
    changeable = true;
  }
}

void setup(){
  // pushbutton to switch modes
  pinMode(BUTTON_PIN, INPUT);

  // link the colors to the LEDs
  FastLED.addLeds <WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop(){
  // check input
  chkin();

  // run light pattern
  mode::run();

  // apply the colors
  FastLED.show();
}


