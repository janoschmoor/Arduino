#include <FastLED.h>
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];

/*

Research shows that its likely that the update frequency of ws2812 is around 400 hz corresponding to an update 
every 2.5 ns

*/

CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];
int id = 10;
int hue = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
}

void loop() {
  //FastLED.setBrightness(100);
  int dir = 1;

  CRGB target;
  CRGB fadeOut = CRGB::Black;

  while(true) {

    id += dir;
    if (id == NUM_LEDS-1 || id == 0) {
      dir *= -1;
    }

    hue++;
    if (hue > 255) {
      hue = 0;
    }
    // target = CHSV(hue, 255, 255);

    brightness[id] = 1.0;
    targets[id] = CHSV(hue, 255, 255);

    for (int j = 0; j < 2; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        if (brightness[i] < 0.005) {
          leds[i] = CRGB::Black;
        } else {
          leds[i] = blend(targets[i], fadeOut, floor(255 * (1 - brightness[i])));
        }
        brightness[i] *= 0.99;
      }

      FastLED.show();
      delay(3);
    }


  }
}
