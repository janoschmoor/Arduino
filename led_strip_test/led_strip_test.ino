#include <FastLED.h>
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];

float brightness[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  
}

void loop() {
  // // Define start and end colors
  // CRGB startColor = CRGB::White;
  // CRGB endColor = CRGB::Red;

  // FastLED.setBrightness(100);
  
  // // Gradually change the color
  // for (int i = 0; i <= 255; i++) {
  //   // Calculate intermediate color
  //   CRGB color = blend(startColor, endColor, i);
    
  //   // Set all LEDs to the calculated color
  //   for (int j = 0; j < NUM_LEDS; j++) {
  //     leds[j] = color;
  //   }
    
  //   // Display the LEDs
  //   FastLED.show();
    
  //   // Delay to control the speed of color change
  //   delay(10);
  // }
  FastLED.setBrightness(10);
  for (int j = 0; j < NUM_LEDS; j++) {
    leds[j] = CRGB::Blue;
    FastLED.show();
    delay(16);
    leds[j] = CRGB::Black;

  }
  // leds[NUM_LEDS-1] = CRGB::Black;
  // FastLED.show();

}
