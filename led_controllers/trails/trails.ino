#include <FastLED.h>
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];
CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];

// init dots
#define dotCount 2
float dotPos[dotCount];
float dotSpeed[dotCount];
float dotHue[dotCount];
float dotHueSpeed[dotCount];

CRGB fadeOut = CRGB::Black;

void setup() {
  // Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);

  //testing
  dotSpeed[0] = 0.2;
  dotPos[0] = 5;
  dotHue[0] = 100;
  // dotHueSpeed[0] = 0.3;

  dotSpeed[1] = -0.3;
  dotHue[1] = 200;
  // dotHueSpeed[1] = 0.7;
}

void loop() {
  //FastLED.setBrightness(100);

  // move dots
  for(int i = 0; i < dotCount; i++) {
    dotPos[i] += dotSpeed[i];
    if (dotPos[i] < 0) {
      dotPos[i] += NUM_LEDS;
    } else if (dotPos[i] >= NUM_LEDS) {
      dotPos[i] -= NUM_LEDS;
    }
    dotHue[i] += dotHueSpeed[i];
    if (dotHue[i] < 0) {
      dotHue[i] += 255;
    } else if (dotHue[i] >= 255) {
      dotHue[i] -= 255;
    }
  }




  leds[(int) dotPos[0]] = CHSV(dotHue[0], 255, 255);
  leds[(int) dotPos[1]] = CHSV(dotHue[1], 255, 255);


  // Serial.println(dotPos[0]);

  FastLED.show();

  delay(3);


  // target = CHSV(hue, 255, 255);

  // brightness[id] = 1.0;
  // targets[id] = CHSV((int) hue, 255, 255);

  // for (int j = 0; j < 1; j++) {
  //   for (int i = 0; i < NUM_LEDS; i++) {
  //     if (brightness[i] < 0.005) {
  //       leds[i] = CRGB::Black;
  //     } else {
  //       leds[i] = blend(targets[i], fadeOut, floor(255 * (1 - brightness[i])));
  //     }
  //     brightness[i] *= 0.99;
  //   }

  //   FastLED.show();
  //   delay(500);
  // }
}
