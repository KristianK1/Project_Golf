#include"Bluetooth_comm.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Bluetooth_comm *ESP_BT;

void setup() {
  Serial.begin(115200);
  Serial.println("The device started, now you can pair it with bluetooth!");
  ESP_BT=new Bluetooth_comm();
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2, OUTPUT);
}

void loop() {
  ESP_BT->reciveing();
  ESP_BT->checking();
  ESP_BT->update_state();
  digitalWrite(2, ESP_BT->getBTstate());
  delay(20);
}
