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
    ~ButtonController();

    // Declaration of member functions
    ButtonState update();

private:
    int pin;

};

#endif