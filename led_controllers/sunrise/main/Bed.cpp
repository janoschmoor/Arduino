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

void Bed::setup() {
    button.setup();

    state = STARTUP;
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

void Bed::handleStateTransition(ButtonState buttonState) {
    switch (buttonState) {
        case STARTUP:
            if (buttonState == PRESSED) {
                state = LIGHT;
            }
            break;
        case LIGHT:
            if (buttonState == PRESSED) {
                state = STARTUP;
            }
            break;
    }
}