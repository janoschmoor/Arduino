#include <FastLED.h>
#define NUM_LEDS 60 // 60
CRGB leds[NUM_LEDS];
CRGB targets[NUM_LEDS];
float brightness[NUM_LEDS];

long last_time;
const float fade = 0.2; // 0.1 fades absolute 10% per second

bool buttonIsPressed = false;

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





// CONTROL BUTTON
const int buttonPin = 9;
const int debounceDelay = 50;

bool buttonState = LOW;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;

enum ButtonState { IDLE, SINGLE_CLICK, DOUBLE_CLICK, LONG_PRESS };
ButtonState currentState = IDLE;

unsigned long buttonPressTime = 0;
unsigned long clickTimeout = 300; // Time allowed between clicks for double-click
unsigned long longPressThreshold = 1000; // Time threshold for a long press
unsigned long lastClickTime = 0;
int clickCount = 0;


 //
//      < RUN THE SKETCH >
//

int state;
int nextstate;
long cooldown;

void setup() {
  // led
  FastLED.addLeds<NEOPIXEL, 10>(leds, NUM_LEDS);
  last_time = millis();

  // button
  pinMode(buttonPin, INPUT);

  // prep state
  cooldown = millis() + 1000;
  state = 0;
  nextstate = 1;

  randomSeed(analogRead(A0));
}


void loop() {

  // int buttonState = digitalRead(9);
  // if (buttonState == HIGH && !buttonIsPressed) {
  //   buttonIsPressed = true;
  // } else if (buttonState == LOW && buttonIsPressed) {
  //   buttonIsPressed = false;
  //   // temp
  //   state = 0;
  //   nextstate = 1;
  //   cooldown = millis() + 1000;
    
  //   resetLED();
  // }

  void checkButton();

  switch(state) {
    case 0:
      runTransition();
      break;
    case 1:
      runDots();
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

//              BUTTON
void checkButton() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        buttonPressTime = millis();
      } else {
        unsigned long pressDuration = millis() - buttonPressTime;
        if (pressDuration > longPressThreshold) {
          currentState = LONG_PRESS;
        } else {
          clickCount++;
          lastClickTime = millis();
        }
      }
    }
  }

  lastButtonState = reading;

  if ((millis() - lastClickTime) > clickTimeout) {
    if (clickCount == 1) {
      currentState = SINGLE_CLICK;
    } else if (clickCount == 2) {
      currentState = DOUBLE_CLICK;
    }
    clickCount = 0;
  }

  executeAction();
}
void executeAction() {
  switch (currentState) {
    case SINGLE_CLICK:
      Serial.println("Single Click Detected");
      // Add your action here
      break;
    case DOUBLE_CLICK:
      Serial.println("Double Click Detected");
      // Add your action here
      break;
    case LONG_PRESS:
      Serial.println("Long Press Detected");
      // Add your action here
      break;
    default:
      break;
  }
  currentState = IDLE;
}
