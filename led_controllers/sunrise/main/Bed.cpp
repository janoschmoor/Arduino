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

    resetState();
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
    }
}


// // Private member functions
void Bed::handleInput(ButtonState buttonState) {
    switch (buttonState) {
        case LONG_PRESS:
            resetState();
            break;
        
    }
}

void Bed::resetState() {
    currentState = TRANSITION;
    nextState = LIGHT;
    cooldown = millis() + cooldownTime;
}

void Bed::endTransition() {
    currentState = nextState;
}