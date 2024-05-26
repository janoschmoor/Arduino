#ifndef BED_H
#define BED_H

#include "ButtonController.h"

class Bed {
public:
    // Constructor(s) and destructor
    Bed();

    // Declaration of member functions
    void setup();
    void main();


private:

    enum BedState {
        TRANSITION,
        LIGHT,
    };
    
    void handleInput(ButtonState);
    void resetState();
    void endTransition();

    // LED led;
    BedState currentState;
    BedState nextState;
    int cooldown;
    const int cooldownTime = 1000;
};

#endif