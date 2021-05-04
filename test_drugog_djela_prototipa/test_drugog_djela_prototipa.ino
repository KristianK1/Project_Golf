#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32test"); //Bluetooth device name
  
  
  digitalWrite(32, HIGH);
  pinMode(32, OUTPUT);
  digitalWrite(33, HIGH);
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(2, OUTPUT);
      
  digitalWrite(25, HIGH);
  digitalWrite(2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(19) || digitalRead(21) || digitalRead(22) || digitalRead(23) || digitalRead(18)){
    SerialBT.print(digitalRead(19));
    SerialBT.print(digitalRead(21));
    SerialBT.print(digitalRead(22));
    SerialBT.print(digitalRead(23));
    SerialBT.print("   ");
    SerialBT.println(digitalRead(18));
    delay(2);
  }
}
