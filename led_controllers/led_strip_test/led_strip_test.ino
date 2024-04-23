#include <FastLED.h>
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];

float brightness[NUM_LEDS];
int id = 10;

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}

void loop() {
  FastLED.setBrightness(100);
  int dir = 1;

  while(true) {
    if (id == NUM_LEDS-1 || id == 0) {
      dir *= -1;
    }
    id += dir;
    if (dir == 1) {
      leds[id] = CRGB::Purple;
    } else {
      leds[id] = CRGB::Black;
    }
    FastLED.show();
    delay(50);
  }
}