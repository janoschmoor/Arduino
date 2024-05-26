#include "LED.h"
// #include <FastLED.h>
// #include "Bed.h"

// Constructor
LED::LED() {}

// Public member functions
void LED::setup() {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void LED::runTransition(int cooldown, int cooldownTime) {
    int progress = cooldown - millis();
    for (int i = 0; i < NUM_LEDS; i++) {
        float progress = ((float) cooldown - millis()) / cooldownTime;
        leds[i] = leds[i].lerp8(targets[i], progress);
    }
    FastLED.show();
}

void LED::runLight() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
    }

    FastLED.show();
}


// Private member functions
