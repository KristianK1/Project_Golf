#include <TinyGPS++.h>

#include "BluetoothSerial.h"


TinyGPSPlus gps;
  BluetoothSerial SerialBT;
void setup(){
    Serial.begin(9600);
    SerialBT.begin("ESP");
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
 pinMode(33, OUTPUT);
       digitalWrite(33, LOW);
}

void loop(){
    while(Serial.available()>0) {
        gps.encode(Serial.read());
            SerialBT.println(gps.speed.kmph());
            SerialBT.println(gps.location.lat());
            SerialBT.println(gps.location.lng());
            delay(100);

    }
}