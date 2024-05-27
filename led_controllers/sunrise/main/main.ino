#include "Bed.h"
Bed bed;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(A0));
    bed.setup();
}

void loop() {
    bed.main();
}
