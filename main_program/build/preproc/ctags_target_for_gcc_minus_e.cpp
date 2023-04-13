# 1 "d:\\Project_Golf\\main_program\\main_program.ino"
# 2 "d:\\Project_Golf\\main_program\\main_program.ino" 2
Device_state *MyDevice;
int input1=19;
int input2=21;
int input3=22;
int input4=23;
int charge_pp=25;
int push_p=18;
int GSM_pp=32;
int GPS_pp=33;

unsigned long int locks_timer;

void __attribute__((section(".iram1" "." "16"))) input1RISING(){
  detachInterrupt(input1);
  detachInterrupt(input2);
  MyDevice->unlock();
  locks_timer=millis();
  MyDevice->setLocksAttached(false);
}

void __attribute__((section(".iram1" "." "17"))) input2RISING(){
  detachInterrupt(input2);
  detachInterrupt(input1);
  MyDevice->lock();
  locks_timer=millis();
  MyDevice->setLocksAttached(false);
}

void __attribute__((section(".iram1" "." "18"))) pushed(){
  detachInterrupt(push_p);
  MyDevice->send_error_message("udaren");
  MyDevice->setStoppedMoving();
  //if(MyDevice->device_get_percentage()<0.75){
    //MyDevice->setCS(true);
    MyDevice->send_error_message("gurnut");
  //}
  if(MyDevice->getBTstate()==0){
    if(MyDevice->isMoveing()==false){
      if(MyDevice->link_exists()==false){
        MyDevice->Pushed_message();
      }
    }
  }
  MyDevice->setLastTimePushed();
}

void akc_loop_main(){
  int temp=MyDevice->akc_loop();
  if(temp==1){
    MyDevice->send_error_message("pocetno attachanje");
    attachInterrupt(push_p, pushed, 0x01);
  }
  else if(temp==2){
    //MyDevice->send_error_message("reatach");
    attachInterrupt(push_p, pushed, 0x01);
  }
}

void main_locks_loop(){
  if(millis()-locks_timer>1500){
      if(MyDevice->getLocksAttached()==false){
        MyDevice->setLocksAttached(true);
        MyDevice->send_error_message("locks attached");
        attachInterrupt(input1, input1RISING, 0x01);
        attachInterrupt(input2, input2RISING, 0x01);
      }
    }
}
void setup() {

  // put your setup code here, to run once:
  MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp);
  //MyDevice->Wakeup_message();
  //delay(5000);
  pinMode(2, 0x02);
  digitalWrite(2, 0x1);

  attachInterrupt(input1, input1RISING, 0x01);
  attachInterrupt(input2, input2RISING, 0x01);
  MyDevice->setLocksAttached(true);
  MyDevice->GPS_power(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  MyDevice->locks_loop();
  main_locks_loop();
  MyDevice->GSM_loop();
  akc_loop_main();
  MyDevice->GPS_loop();
  MyDevice->Battery_loop();
  MyDevice->BT_loop();
  delay(100);
  digitalWrite(2, digitalRead(push_p));


}
