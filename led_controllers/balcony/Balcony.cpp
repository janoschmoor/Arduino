#include "Balcony.h"


Balcony::Balcony() {

}

void Balcony::setup() {

}

void Balcony::update() {

    ButtonState state = button.update();

    switch (state) {
        case SINGLE_CLICK:
            // TODO: Add code to handle single click
            break;
    }

}