
#include "ButtonController.h"
const int BUTTON_PIN = 9; // TODO change this to the correct pin
ButtonController button(BUTTON_PIN);

void setup() {
    button.setup();
}

void loop() {

    ButtonState state = button.update();

    switch (state) {
        case SINGLE_CLICK:
            // TODO: Add code to handle single click
            break;
    }

}