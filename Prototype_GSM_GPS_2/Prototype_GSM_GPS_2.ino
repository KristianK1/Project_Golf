#include "SIM800L_S2.h"
#include "Location.h"
#include "codes.h"


SIM800L_S2 internet;
//String Link="http://api.thingspeak.com/update?api_key=" + thingspeak_API_key + "&field1="+"2000";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(33, LOW);
  pinMode(33, OUTPUT);
  SerialBT.begin("ESP32test");
  internet.setPowerpin(32);
  //internet.setLink(Link);
  internet.turn_off();
  delay(3000);
  internet.turn_on();
  delay(3000);
  Serial.println("POCETAK");
  SerialBT.println("pocetak");
}

void loop() {
  // put your main code here, to run repeatedly:

  Location current_loc(181,91);
  //long int timer=millis();
  while(current_loc.getX()==181) {
    SerialBT.println("učitavanje");
    current_loc=GPS();
  }
  String s=loc_to_link(current_loc,4);
  internet.setLink(s);
  SerialBT.println(s);


  int q=1;
  while(q!=3){
    q=internet.access();
    SerialBT.println("\nizasao");
    if(q==2){
      internet.turn_off();
      delay(3000);
      internet.turn_on();
      delay(12000);
      internet.reset_recive();
    }
    if(q==3) {
      SerialBT.println("\n\n\n\n uspjeh");
      delay(40000);
    }
    delay(300);
  }
}
