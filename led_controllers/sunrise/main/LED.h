#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
    // Constructor(s) and destructor
    ButtonController(int pin, int numLeds);

    // Declaration of member functions
    void setup();
    void update();

private:
    int pin;
    int numLeds;

    CRGB leds[NUM_LEDS];
    CRGB targets[NUM_LEDS];
    float brightness[NUM_LEDS];

    long last_time;
    const float fade = 0.2; // 0.1 fades absolute 10% per second
};

#endif