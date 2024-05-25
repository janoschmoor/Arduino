#ifndef BED_H
#define BED_H

class Bed {
public:
    // Constructor(s) and destructor
    Bed();

    // Declaration of member functions
    void setup();
    void main();


private:

    void handleInput(ButtonState);
    void resetState();
    void endTransition();

    enum BedState {
        TRANSITION,
        LIGHT,
    };

    BedState currentState;
    BedState nextState;

    int cooldown;
    const int cooldownTime = 1000;


};

#endif