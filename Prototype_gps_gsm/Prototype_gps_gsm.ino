#include "BluetoothSerial.h"
#include"SIM800_KK_ESP.h"
#include "Location.h"
#include "codes.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//BluetoothSerial SerialBT;

SIM800L_KK *SIM800LL;

int GSM(String link){
  SIM800LL->setLink(link);
  int q=0;
  q=SIM800LL->access();
  if(q==0) SerialBT.println("\n\n\nExit code: Failed");
  if(q==1) SerialBT.println("\n\n\nExit code: Success");
  if(q==2) ; //not yet
  if(q==3) SerialBT.println("\n\n\nExit code: reset");
  return q;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial2.begin(9600); // connect gps sensor
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);

  //Location loccc(121.123456,-44.998855);
  //SerialBT.println(big_packet(loccc.getX(), loccc.getY(), 2));
  
  SIM800LL=new SIM800L_KK();
  delay(1000);
}




void loop() {
  // put your main code here, to run repeatedly:
  Location current_loc(181,91);
  long int timer=millis();
  while(current_loc.getX()==181 && (millis()-timer)>6000) current_loc=GPS();

  int ret=0;
  String link;
  if(current_loc.getX()==181) {
    link=small_link(0);
    SerialBT.println("krute");
  }
  else link=loc_to_link(current_loc, 4);
  
  while(ret!=1) {
    ret=GSM(link);
    delay(50);
  }
  switch(ret){
    case 0: delay(10000);
            break;
    case 1: delay(15000);
            break;
    case 3: delay(5000);
            break;
  }
}
