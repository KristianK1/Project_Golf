# 1 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino"
# 2 "d:\\Zavrsni_rad_FERIT_Kristian_Kliskovic\\Arduino_programi\\Project_Golf\\bluetooth_comms\\bluetooth_comms.ino" 2




Bluetooth_comm *ESP_BT;

void setup() {
  Serial.begin(115200);
  Serial.println("The device started, now you can pair it with bluetooth!");
  ESP_BT=new Bluetooth_comm();
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2, 0x02);
}

void loop() {
  ESP_BT->reciveing();
  ESP_BT->checking();
  ESP_BT->update_state();
  digitalWrite(2, ESP_BT->getBTstate());
  delay(20);
}
