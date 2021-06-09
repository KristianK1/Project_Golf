#include <Arduino.h>
#line 1 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
#include"Bluetooth_comm.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial *SerialBT;
Bluetooth_comm *ESP_BT;

#line 11 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
void setup();
#line 21 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
void loop();
#line 11 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("The device started, now you can pair it with bluetooth!");
  SerialBT=new BluetoothSerial(); 
  SerialBT->begin("ESP32"); //Bluetooth device name
  ESP_BT=new Bluetooth_comm(SerialBT);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2, OUTPUT);
}

void loop() {
  ESP_BT->reciveing();
  ESP_BT->checking();
  digitalWrite(2, ESP_BT->getBTstate());
  delay(20);
}
