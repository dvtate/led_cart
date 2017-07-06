#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>

// pushbutton to swich modes
#define BUTTON_PIN 2

// 1M of a 144LED/M led strip
#define LED_DATA_PIN A0
#define NUM_LEDS 144
CRGB leds[NUM_LEDS];

// light and color modes and switching mechanisms
#include "modes.h"

// check mode change button for input
// ret - true if mode changed, else false
bool chkin(){
  // don't want repeated triggering
  static bool changeable = true;
  if (changeable && digitalRead(BUTTON_PIN)) {
    // if triggered change modes and disable trigger
    changeable = false;
    mode::next();
    return true;
  } else if (!changeable && !digitalRead(BUTTON_PIN)) {
    // if trigger disabled and they arent pressing btn, re-enable
    changeable = true;
  }
  return false;
}

// run once at startup
void setup(){
  // pushbutton to switch modes
  pinMode(BUTTON_PIN, INPUT);

  // link the colors to the LEDs
  FastLED.addLeds <WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);

}

// looped repeatedly forever
void loop(){
  // check input
  chkin();

  // run light pattern
  mode::run();

  // apply the colors
  FastLED.show();
}

