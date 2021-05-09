#include "SIM800L_S2.h"
#include "thingspeak_API_key.h"

SIM800L_S2 internet;
String Link="http://api.thingspeak.com/update?api_key=" + thingspeak_API_key + "&field1="+"2000";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  SerialBT.begin("ESP32test");
  internet.setPowerpin(32);
  internet.setLink(Link);
  internet.turn_off();
    delay(3000);
    internet.turn_on();
    delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int q=internet.access();
  SerialBT.println("izasao");
  if(q==0){
    internet.turn_off();
    delay(3000);
    internet.turn_on();
    delay(3000);
    internet.reset_recive();
  }
  if(q==3) {
    SerialBT.println("uspjeh");
    delay(60000);
  }
  delay(1000);
}
