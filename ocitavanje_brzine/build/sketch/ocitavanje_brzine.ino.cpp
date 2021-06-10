#include <Arduino.h>
#line 1 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino"
#include <TinyGPS++.h>

#include "BluetoothSerial.h"


TinyGPSPlus gps;
  BluetoothSerial SerialBT;
#line 8 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino"
void setup();
#line 17 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino"
void loop();
#line 8 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino"
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
