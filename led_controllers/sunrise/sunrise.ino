#include <FastLED.h>
#define NUM_LEDS 60 // 60
CRGB leds[NUM_LEDS];
CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];

long last_time;
float fade = 0.2; // 0.1 fades absolute 10% per second

class Dot {
  public:
    float position;
    float velocity;
    CRGB color;

  public:
    Dot(float startPos, float startVel, CRGB startColor) {
      position = startPos;
      velocity = startVel;
      color = startColor;
    }

    void update(float dt) {
      position = (position + velocity * dt);
      if (position > (float) NUM_LEDS - 0.5 || position < 0.5) {
        velocity *= -1;
        position = (position + 2.0 * velocity * dt);
      }
    }

    void render(float dt, CRGB target) {
      int px = ((int) position);

      // brightness
      float distance = (position - (float) px);
      if (velocity > 0) {
        distance = 1-distance;
      }
      float intensity = easing(distance);
      brightness[px] = max(intensity, brightness[px]);

      // blending
      // float blendamt = 0.02;
      // targets[px] = blend(targets[px], color, blendamt*255);
      // targets[px] = target;
      targets[px] = blend(targets[px], target, 40);

    }

    //    Helper
    float easing(float x) {
      float res;

      // one sided quadradic easein
      if (x < 0) return 0.0;
      res = (x-1)*(x-1);
      res = constrain(res, 0.0, 1.0);
      return res >= 0.0 ? res : 0.0;
    }
};

// Dot dots[] = {
//   Dot(NUM_LEDS / 2, -1.0, CHSV(60, 255, 255)),
//   Dot(NUM_LEDS / 2, 1.8, CHSV(280, 255, 255)),
//   Dot(NUM_LEDS / 2, 1.3, CHSV(0, 255, 255))
// };
Dot dots[] = {
  Dot(5.0, 2.5, CHSV(0, 255, 255)),
  Dot(15.0, -2.0, CHSV(213, 255, 255)),
  Dot(NUM_LEDS / 2, 3.3, CHSV(42, 255, 255))
};








 //
//      < RUN THE SKETCH >
//

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  last_time = millis();
}


void loop() {

  float delta = ((float) millis() - (float) last_time) / 1000;
  last_time = millis();

  // simulate 
  for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
    dots[i].update(delta);

    CRGB target = dots[i].color;
    for (int j = 0; j < sizeof(dots) / sizeof(dots[0]); j++) {
      if (i != j) {
        float distance = abs(dots[i].position - dots[j].position);
        float blendAmt = pow(1.25, -distance) / 2.0; // adjust first float for steeper or shallower blending
        target = blend(target, dots[j].color, blendAmt * 255);
      }
    }
    dots[i].render(delta, target);
  }

  // apply lighting to leds
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = blend(CRGB::Black, targets[i], (int) (brightness[i] * 255));
    brightness[i] = max(brightness[i] - fade * delta, 0.0);
  }

  FastLED.show();
  delay(3);
}







