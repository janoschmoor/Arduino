#include <FastLED.h>
#define NUM_LEDS 150
CRGB leds[NUM_LEDS];
Dot dots[];

class Dot {
    int pos;
    // Add any additional member variables here

    public:
        Dot(int initialPos) {
            pos = initialPos;
            // Initialize any additional member variables here
        }

    void update() {
        // Add code to render the dot here
    }

    void render() {
        // Add code to render the dot here
    }
};

void setup() {
    FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);

    Dot dots[5] = {Dot(0), Dot(1), Dot(2), Dot(3), Dot(4)};

    
}

void loop() {


    FastLED.show();
}