#include "Device_state.h"

void setup(){
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void loop(){
    Location rijeka(14.457664,45.328979); // rijeka
    Location zagreb(15.981721, 45.813342);
    Location SB(18.011876, 45.156616);
    Device_state uredaj(SB, 0);
    Serial.println("hello");

    Serial.println(uredaj.distance(zagreb));
    digitalWrite(2, digitalRead(2)^1);
    delay(500);
}