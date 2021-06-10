# 1 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
# 2 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino" 2






BluetoothSerial *SerialBT;
Bluetooth_comm *ESP_BT;

void setup() {
  Serial.begin(115200);
  Serial.println("The device started, now you can pair it with bluetooth!");
  SerialBT=new BluetoothSerial();
  SerialBT->begin("ESP32"); //Bluetooth device name
  ESP_BT=new Bluetooth_comm(SerialBT);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2, 0x02);
}

void loop() {
  ESP_BT->reciveing();
  ESP_BT->checking();
  digitalWrite(2, ESP_BT->getBTstate());
  delay(20);
}
