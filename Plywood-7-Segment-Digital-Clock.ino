#include <FastLED.h>


#define NUM_LEDS 1     
#define DATA_PIN 6
CRGB LEDs[NUM_LEDS];

void setup() {
  // Initialize LED strip
  FastLED.delay(3000);
  
  // Check if you're LED strip is a RGB or GRB version (third parameter)
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);
}

void loop() {

  LEDs[0] = CRGB::Red;
  FastLED.show();

}
