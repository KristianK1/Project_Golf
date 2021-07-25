#include <Arduino.h>
#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
#include"Device_state.h"
Device_state *MyDevice;
int input1=19;
int input2=21;
int input3=22;
int input4=23;
int charge_pp;
int push_p=18;
int GSM_pp=32;
int GPS_pp=33;

#line 24 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
void setup();
#line 38 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
void loop();
#line 12 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
void IRAM_ATTR input1RISING(){
  MyDevice->unlock();
}

void IRAM_ATTR input2RISING(){
  MyDevice->lock();
}

void IRAM_ATTR pushed(){

}

void setup() {
  // put your setup code here, to run once:
  MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp);
  attachInterrupt(input1, input1RISING, RISING);
  attachInterrupt(input2, input2RISING, RISING);
  attachInterrupt(push_p, pushed, RISING);
  MyDevice->Wakeup_message();
  delay(5000);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  MyDevice->Device_loop();
}

