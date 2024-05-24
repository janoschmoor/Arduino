#include "ButtonController.h"

// Constructor
ButtonController::ButtonController(int pin) {
    this.pin = pin;
}

void ButtonController::setup() {
    pinMode(pin, INPUT);
}

ButtonState ButtonController::update() {

    currentState = IDLE;

    int reading = digitalRead(pin);
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


    return currentState;
}
