#include "LED.h"
// #include <FastLED.h>
// #include "Bed.h"


Dot dots[] = {
  Dot(),
  Dot(),
  Dot()
};




// Constructor
LED::LED() {}

// Public member functions
void LED::setup() {
    FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
    last_time = millis();
    randomize();
}

void LED::randomize() {
    for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
        float speed = (float)random(50, 100) / 10.0;
        if (random(0,2) == 0) {
          speed *= -1;
        }
        dots[i].setup(random(2, NUM_LEDS-2), speed, CHSV(random(0, 255), 255, 255), leds, targets, brightness);
    }
    for (int i = 0; i < NUM_LEDS; i++) {
        targets[i] = CRGB::Black;
        brightness[i] = 0.0;
    }
}

void LED::runTransition(long cooldown, int cooldownTime) {
    int ratio = 1.0;
    float progress = ((float) cooldown - millis()) / (cooldownTime * ratio);
    for (int i = 0; i < NUM_LEDS; i++) {
        float position = abs(i - (float) NUM_LEDS / 2.0);
        if ((float) position / (NUM_LEDS / 2.0) > progress) {
          leds[i] = CRGB::White;
        } else {
          leds[i] = CRGB::Black;
        }
    }
    FastLED.show();
    delay(3);
}

void LED::runLight() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(3);
}

void LED::runSleep() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(3);
}

void LED::runRandomDots() {
    float delta = ((float) millis() - (float) last_time) / 1000;
    last_time = millis();

    // simulate 
    for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
        dots[i].update(delta, NUM_LEDS);

        CRGB target = dots[i].color;
        for (int j = 0; j < sizeof(dots) / sizeof(dots[0]); j++) {
            if (i != j) {
                float distance = abs(dots[i].position - dots[j].position);
                float blendAmt = pow(1.1, -distance) / 2.0; // adjust first float for steeper or shallower blending
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


// Private member functions
