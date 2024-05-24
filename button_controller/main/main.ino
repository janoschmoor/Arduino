#include "ButtonController.h"

const int BUTTON_PIN = 2;

ButtonController button(BUTTON_PIN);

void setup() {
    Serial.begin(9600);
    button.setup();
}

void loop() {
    ButtonState state = button.update();
    switch (state) {
        case IDLE:
            Serial.println("IDLE");
            break;
        case SINGLE_CLICK:
            Serial.println("SINGLE_CLICK");
            break;
        case DOUBLE_CLICK:
            Serial.println("DOUBLE_CLICK");
            break;
        case LONG_PRESS:
            Serial.println("LONG_PRESS");
            break;
    }
    delay(10);
}
