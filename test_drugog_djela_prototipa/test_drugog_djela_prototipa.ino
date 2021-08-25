#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32test"); //Bluetooth device name
    pinMode(25, OUTPUT);
      
  digitalWrite(25, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(19) || digitalRead(21)){
    SerialBT.print(digitalRead(19));
    SerialBT.print(digitalRead(21));
    delay(20);
  }
}
