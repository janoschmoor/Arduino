#include "Bed.h"
Bed bed;

void setup() {
    randomSeed(analogRead(A0));
    bed.setup();
}

void loop() {
    bed.main();
}
