// #include <FastLED.h>

#include "LED.h"
const int LED_PIN = 10;
const int NUM_LEDS = 60;
LED led(LED_PIN, NUM_LEDS);

#include "ButtonController.h"
const int BUTTON_PIN = 9;
ButtonController button(BUTTON_PIN);





//
//      < RUN THE SKETCH >
//

// enum GlState { IDLE, TRANSITION, WHITE, DOTS, COLOR };
// GlState currentGlState = IDLE;

int state;
int nextstate;
long cooldown;

void setup() {
  // led
  FastLED.addLeds<NEOPIXEL, 10>(leds, NUM_LEDS);
  last_time = millis();

  // button
  button.setup();

  // prep state
  cooldown = millis() + 1000;
  state = 0;
  nextstate = 1;

  // Serial.begin(9600);

  randomSeed(analogRead(A0));
}


void loop() {
  switch(state) {
    case 0:
      runTransition();
      break;
    case 1:
      runDots();
      break;
  }

  ButtonState state = button.update();
  switch (state) {
    case IDLE:
      // Serial.println("IDLE");
      break;
    case SINGLE_CLICK:
      Serial.println("SINGLE_CLICK");
      state = 0;
      nextstate = 1;
      cooldown = millis() + 1000;
      resetLED();
      break;
    case DOUBLE_CLICK:
      Serial.println("DOUBLE_CLICK");
      break;
    case LONG_PRESS:
      Serial.println("LONG_PRESS");
      break;
  }


  
}

void runTransition() {

  long threshhold = 1000 - (cooldown - millis());

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ((float)i * 1000 / NUM_LEDS < threshhold) ? CRGB::White : CRGB::Black;
  }

  FastLED.show();
  delay(3);

  // next state logic
  if (cooldown < millis()) {
    state = nextstate;
    nextstate = 0;
    for (int i = 0; i < 3; i++) {
      dots[i] = Dot(random(NUM_LEDS - 4) + 2, random(1000) / 50.0 - 10.0, CHSV(random(255), 255, 255));
    }
  }
}
void runDots() {

  float delta = ((float) millis() - (float) last_time) / 1000;
  last_time = millis();

  // simulate 
  for (int i = 0; i < sizeof(dots) / sizeof(dots[0]); i++) {
    dots[i].update(delta);

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





//              HELPER
void resetLED() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    targets[i] = CRGB::Black;
    brightness[i] = 0.0;
  }
  FastLED.show();
  delay(3);
}
