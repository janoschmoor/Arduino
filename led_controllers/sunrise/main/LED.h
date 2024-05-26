#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>

const int NUM_LEDS = 60;
const int LED_PIN = 10;

class LED {
public:
    // Constructor(s) and destructor
    LED();

    // Declaration of member functions
    void setup();

    void runTransition(int cooldown, int cooldownTime);
    void runLight();

private:

    CRGB leds[NUM_LEDS];
    CRGB targets[NUM_LEDS];
    float brightness[NUM_LEDS];

    // long last_time;
    // const float fade = 0.2; // 0.1 fades absolute 10% per second
};

#endif