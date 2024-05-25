#include "LED.h"
#include "FastLED.h"

// Constructor
LED::LED(int buttonPin, int numLeds) {
    pin = buttonPin;
    this.numLeds = numLeds;
    leds = new CRGB[numLeds];
    targets = new CRGB[numLeds];
    brightness = new float[numLeds];
}

// Public member functions
void LED::setup() {
    FastLED.addLeds<NEOPIXEL, pin>(leds, numLeds);
    pinMode(pin, OUTPUT);
}

void LED::runTransition(int cooldown, int cooldownTime) {

    int progress = cooldown - millis();

    for (int i = 0; i < numLeds; i++) {
        float progress = ((float) cooldown - millis()) / cooldownTime;
        leds[i] = leds[i].lerp8(targets[i], progress);
    }

    FastLED.show();
}

void LED::runLight() {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = CRGB::White;
    }

    FastLED.show();
}


// Private member functions
