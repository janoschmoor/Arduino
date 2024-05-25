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

    enum BedState {
        STARTUP,
        LIGHT,
    };

    BedState state;

};

#endif