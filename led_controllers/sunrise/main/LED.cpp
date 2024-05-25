#include "LED.h"
#include "FastLED.h"



// Constructor
LED::LED(int buttonPin, int numLeds) {
    pin = buttonPin;
    numLeds = numLeds;
}

void ButtonController::setup() {
    pinMode(pin, INPUT);
}