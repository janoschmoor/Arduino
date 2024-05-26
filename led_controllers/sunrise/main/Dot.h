#ifndef DOT_H
#define DOT_H

#include <FastLED.h>

class Dot {
public:
    // Constructor(s) and destructor
    Dot();

    // Declaration of member functions
    void setup(float startPos, float startVel, CRGB startColor, CRGB* leds, CRGB* targets, float* brightness);
    void update(float dt, const int NUM_LEDS);
    void render(float dt, CRGB target);

    float position;
    float velocity;
    CRGB color;

private:

    // Private member functions
    float easing(float x);

    CRGB* leds;
    CRGB* targets;
    float* brightness;

};

#endif