# 1 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino"
# 2 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino" 2

# 4 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\ocitavanje_brzine\\ocitavanje_brzine.ino" 2


TinyGPSPlus gps;
  BluetoothSerial SerialBT;
void setup(){
    Serial.begin(9600);
    SerialBT.begin("ESP");
    pinMode(2, 0x02);
    digitalWrite(2, 0x1);
 pinMode(33, 0x02);
       digitalWrite(33, 0x0);
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
