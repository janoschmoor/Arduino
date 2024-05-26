#include "Dot.h"

// Constructor
Dot::Dot() {}

// Public member functions
void Dot::setup(float startPos, float startVel, CRGB startColor, CRGB* leds, CRGB* targets, float* brightness) {
    position = startPos;
    velocity = startVel;
    color = startColor;
    this->leds = leds;
    this->targets = targets;
    this->brightness = brightness;
}

void Dot::update(float dt, const int NUM_LEDS) {
    position = (position + velocity * dt);
    if (position > (float) NUM_LEDS - 0.5 || position < 0.5) {
        velocity *= -1;
        position = (position + 2.0 * velocity * dt);
    }
}

void Dot::render(float dt, CRGB target) {
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

// Private member functions
float Dot::easing(float x) {
    float res;

    // one sided quadradic easein
    if (x < 0) return 0.0;
    res = (x-1)*(x-1);
    res = constrain(res, 0.0, 1.0);
    return res >= 0.0 ? res : 0.0;
}