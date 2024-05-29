#ifndef BALCONY_H
#define BALCONY_H

#include "ButtonController.h"
const int BUTTON_PIN = 9; // TODO change this to the correct pin
ButtonController button(BUTTON_PIN);

class Balcony {
public:
    // Constructor(s) and destructor
    Balcony();

    // Declaration of member functions
    void setup();
    void update();

private:



}


#endif