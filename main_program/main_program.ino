#include"Device_state.h"
Device_state *MyDevice;
int input1=19;
int input2=21;
int input3=22;
int input4=23; //tu ce ici 12V
int charge_pp=25;
int push_p=18;
int GSM_pp=32;
int GPS_pp=33;

unsigned long int locks_timer;

// void IRAM_ATTR input1RISING(){
//   detachInterrupt(input1);
//   detachInterrupt(input2);
//   MyDevice->unlock();
//   locks_timer=millis();
//   MyDevice->setLocksAttached(false);
// }

// void IRAM_ATTR input2RISING(){
//   detachInterrupt(input2);
//   detachInterrupt(input1);
//   MyDevice->lock();
//   locks_timer=millis();
//   MyDevice->setLocksAttached(false);
// }

//TODO return this
// void IRAM_ATTR pushed(){
//   detachInterrupt(push_p);
//   MyDevice->send_error_message("udaren");
//   MyDevice->setStoppedMoving();
//   //if(MyDevice->device_get_percentage()<0.75){
//     //MyDevice->setCS(true);
//     MyDevice->send_error_message("gurnut");
//   //}
//   if(MyDevice->getBTstate()==0){
//     if(MyDevice->isMoveing()==false){
//       if(MyDevice->link_exists()==false){
//         MyDevice->Pushed_message();
//       }
//     }
//   }
//   MyDevice->setLastTimePushed();
// }

//TODO return this
// void akc_loop_main(){
//   int temp=MyDevice->akc_loop();
//   if(temp==1){
//     MyDevice->send_error_message("pocetno attachanje");
//     attachInterrupt(push_p, pushed, RISING);
//   }
//   else if(temp==2){
//     //MyDevice->send_error_message("reatach");
//     attachInterrupt(push_p, pushed, RISING);
//   }
// }

void setup() {
 
  // put your setup code here, to run once:
  MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp, 100.0, false);
  //MyDevice->Wakeup_message();
  //delay(5000);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  MyDevice->GPS_power(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  // MyDevice->locks_loop();
  try{
    MyDevice->GSM_loop();
  } catch(String e){
    if(e == "GSM ne funkcionira"){
      double batteryPercentage = MyDevice->device_get_percentage();
      int isCharging = MyDevice->getCS();
      free(MyDevice);
      MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp, batteryPercentage, isCharging);
    }else{
      throw("rlly throw");
    }
  }
  // akc_loop_main();
  // MyDevice->check12V_loop();
  MyDevice->GPS_loop();
  MyDevice->Battery_loop();
  MyDevice->BT_loop();
  delay(100);
  digitalWrite(2, digitalRead(push_p));
}
