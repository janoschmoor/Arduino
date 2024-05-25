#include "Bed.h"

#include "LED.h"
const int LED_PIN = 10;
const int NUM_LEDS = 60;
LED led(LED_PIN, NUM_LEDS);

#include "ButtonController.h"
const int BUTTON_PIN = 9;
ButtonController button(BUTTON_PIN);

// Constructor
Bed::Bed() {}

// Public member functions
void Bed::setup() {
    button.setup();

    resetState();
}

void Bed::main() {

    ButtonState buttonState = button.main();
    

    switch () {
        case STARTUP:

            break;
        case LIGHT:
            
            break;
    }
}

// Private member functions
void Bed::handleInput(ButtonState buttonState) {
    // switch (buttonState) {
    //     case SINGLE_CLICK:
            
    //         break;
        
    // }
}
void Bed::resetState() {
    currentState = TRANSITION;
    nextState = TRANSITION;
    cooldown = millis() + cooldownTime;
}