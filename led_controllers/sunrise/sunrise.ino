// the idea of this file is to build a lights animation that runs on < 150 leds, where over the period of 30 minutes 3 dots spawn:
// yellow, red to blue or something. they move slowly and can blend inbetween pixels (subpixel rendering)
// when they move along the strip they pull the led target value closer to their own which chould also be a way
// of morphing between their own values. 
// this strip will be mounted under the bed ;)

#include <FastLED.h>
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];

long last_time;
float fade = 0.998;

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

    void update(float dt) {
      previousPosition = position;
      position = (position + velocity * dt);
      if (position > NUM_LEDS || position < 0) {
        velocity *= -1;
      }
    }

    void render() {
      
      float render_dist = 2;

      for (int px = (int) (position - render_dist) + 1; px < (int) (position + render_dist)+1; px++) {
        
        if (px < -0.001 || px >= NUM_LEDS ) {continue;}
        
        // for each pixel within the renderdistance

        float distance = (px - position) / (render_dist / 2.0);

        if ((distance < 0.0 && velocity > 0.0) || (distance > 0.0 && velocity < 0.0)) {continue;}

        float intensity = easing(distance);
        intensity = intensity > 0.01 ? intensity : 0.0;

        //leds[px] = blend(CRGB::Black, color, (int) (intensity * 255));

        targets[px] = blend(targets[px], color,3);
        brightness[px] = ((brightness[px])>(intensity)?(brightness[px]):(intensity));
      }
    }

    //    Helper
    float easing(float x) {
      float res;

      //double sided quad
      //res = (1 + -1*(x*x));
      
      //double sided linear
      res = abs(x) <= 1.0 ? 1.0 - abs(x) : 0.0;

      return res >= 0.0 ? res : 0.0;
    }
};

Dot dots[] = {
  Dot(0.0, 1.5, blend(CRGB::Purple, CRGB::Black, 0)),
  // Dot(10.0, 1.0, blend(CRGB::Yellow, CRGB::Black, 0)),
  // Dot(20.0, 2.0, blend(CRGB::Red, CRGB::Black, 0))
};

//Dot dot(0.0, 5.0, blend(CRGB::Purple, CRGB::Black, 0)); // Example dot object

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  last_time = millis();
}


void loop() {

  float delta = ((float) millis() - (float) last_time) / 1000;
  last_time = millis();

  for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
    dots[i].update(delta);
    dots[i].render();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = blend(CRGB::Black, targets[i], (int) (brightness[i] * 255));
    brightness[i] *= fade;
  }

  FastLED.show();
  delay(3); // Adjust the delay time as needed
}







