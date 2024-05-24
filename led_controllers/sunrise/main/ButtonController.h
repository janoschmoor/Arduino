#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <Arduino.h>

enum ButtonState {
    IDLE,
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS
};

class ButtonController {
public:
    // Constructor(s) and destructor
    ButtonController(int pin);

    // Declaration of member functions
    void setup();
    ButtonState update();

private:
    int pin;
    const int debounceDelay = 30;

    bool buttonState = LOW;
    bool lastButtonState = LOW;
    unsigned long lastDebounceTime = 0;

    ButtonState currentState = IDLE;

    unsigned long buttonPressTime = 0;
    unsigned long clickTimeout = 240; // Time allowed between clicks for double-click
    unsigned long longPressThreshold = 600; // Time threshold for a long press
    unsigned long lastClickTime = 0;
    int clickCount = 0;
};

#endif