#include "SIM800L_S2.h"
#include "Location.h"
#include "codes.h"

SIM800L_S2 internet;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  
  SerialBT.begin("ESP32test");
  internet.setPowerpin(32);
  internet.turn_off();
  delay(3000);
  internet.turn_on();
  delay(3000);
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
      delay(10000);
    }
    delay(300);
  }
}
