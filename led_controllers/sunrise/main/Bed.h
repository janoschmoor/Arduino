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
        SLEEP,
        LIGHT, // must always be first

        RANDOM_DOTS,

        TRANSITION, // special state must always be last
    };
    
    void handleInput(ButtonState);
    void setState(BedState);
    void advanceState();
    void endTransition();

    // LED led;
    BedState currentState;
    BedState nextState;
    int cooldown;
    const int cooldownTime = 1000;
};

#endif