// the idea of this file is to build a lights animation that runs on < 150 leds, where over the period of 30 minutes 3 dots spawn:
// yellow, red to blue or something. they move slowly and can blend inbetween pixels (subpixel rendering)
// when they move along the strip they pull the led target value closer to their own which chould also be a way
// of morphing between their own values. 
// this strip will be mounted under the bed ;)

#include <FastLED.h>
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];

class Dot {
  private:
    int position;
    int previousPosition;
    int velocity;
    CRGB color;

  public:
    Dot(int startPos, int startVel, CRGB startColor) {
      position = startPos;
      previousPosition = startPos;
      velocity = startVel;
      color = startColor;
    }

    void update() {
      previousPosition = position;
      position += velocity;
    }

    void render() {
      leds[position] = color;
      leds[previousPosition] = CRGB::Black;
    }
};

Dot dot(0, 1, CRGB::Yellow); // Example dot object

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);

}


void loop() {
  dot.update();

  dot.render();

  FastLED.show();
  delay(100); // Adjust the delay time as needed
}
