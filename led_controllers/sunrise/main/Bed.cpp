#include "Bed.h"

#include "LED.h"
LED led;

#include "ButtonController.h"
const int BUTTON_PIN = 9;
ButtonController button(BUTTON_PIN);


// Constructor
Bed::Bed() {}

// Public member functions
void Bed::setup() {
    led.setup();
    button.setup();

    setState(LIGHT);
}

void Bed::main() {

    ButtonState buttonState = button.main();
    handleInput(buttonState);
    
    switch (currentState) {
        case TRANSITION:
            led.runTransition(cooldown, cooldownTime);
            if (millis() > cooldown) {
                endTransition();
            }
            break;
        case LIGHT:
            led.runLight();
            break;
        case SLEEP:
            led.runSleep();
            break;

        case RANDOM_DOTS:
            led.runRandomDots();
            break;
    }
}


// // Private member functions
void Bed::handleInput(ButtonState buttonState) {
    switch (buttonState) {
        case LONG_PRESS:
            if (currentState == LIGHT) {
                setState(SLEEP);
            } else {
                setState(LIGHT);
            }
            break;
        case SINGLE_CLICK:
            advanceState();
            break;
        
    }
}

void Bed::setState(BedState state) {
    currentState = TRANSITION;
    nextState = state;
    cooldown = millis() + cooldownTime;
}

void Bed::advanceState() {
    int next = static_cast<int>(currentState) + 1;
    if (next >= static_cast<int>(TRANSITION)) {
        next = static_cast<int>(LIGHT);
    }
    setState(static_cast<BedState>(next));
}

void Bed::endTransition() {
    currentState = nextState;
}