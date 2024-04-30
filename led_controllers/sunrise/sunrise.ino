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
    float position;
    float previousPosition;
    float velocity;
    CRGB color;

  public:
    Dot(float startPos, float startVel, CRGB startColor) {
      position = startPos;
      previousPosition = startPos;
      velocity = startVel;
      color = startColor;
    }

    void update() {
      previousPosition = position;
      position = (position + velocity);
      if (position > NUM_LEDS || position < 0) {
        velocity *= -1;
      }
    }

    void render() {
      
      int render_dist = 4;

      for (int px = (int) (position - render_dist / 2) + 1; px < (int) (position + render_dist / 2)+1; px++) {
        
        if (px < 0 || px >= NUM_LEDS ) {continue;}
        
        // for each pixel within the renderdistance

        float distance = px - position;

        float intensity = easing(distance);
        leds[px] = blend(CRGB::Black, color, (int) (intensity * 255));
      }

      
      // leds[(int)position] = color;
      // leds[(int)previousPosition] = CRGB::Black;
    }

    //    Helper
    float easing(float x) {
      float res;

      //double sided quad
      res = (1 + -1*(x*x));
      
      //double sided linear
      //res = 
      
      return res >= 0.0 ? res : 0.0;
    }
};

Dot dot(3.5, 0.01, blend(CRGB::Purple, CRGB::Black, 0)); // Example dot object

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);

}


void loop() {

  dot.update();

  dot.render();

  FastLED.show();
  delay(5); // Adjust the delay time as needed
}







