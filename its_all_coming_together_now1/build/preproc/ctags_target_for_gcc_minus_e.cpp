# 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
# 2 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino" 2
Device_state *MyDevice;
int input1=19;
int input2=21;
int input3=22;
int input4=23;
int charge_pp=25;
int push_p=18;
int GSM_pp=32;
int GPS_pp=33;

void __attribute__((section(".iram1" "." "16"))) input1RISING(){
  MyDevice->unlock();
}

void __attribute__((section(".iram1" "." "17"))) input2RISING(){
  MyDevice->lock();
}

void __attribute__((section(".iram1" "." "18"))) pushed(){
  MyDevice->send_error_message("udaren");
  detachInterrupt(push_p);
  if(MyDevice->isMoveing()==false){
    if(MyDevice->link_exists()==false){
      MyDevice->Pushed_message();
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

void setup() {
  delay(5000);
  Location ZG(15.966568, 45.815399);
  Location SB(18.01556, 45.16028);
  Location VK(15.993320, 45.201960);
  Serial.begin(9600);
  Serial.println(cos(90));
  Serial.println(distance(ZG,SB));
  delay(50000);
  // put your setup code here, to run once:
  MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp);
  //MyDevice->Wakeup_message();
  delay(5000);
  pinMode(2, 0x02);
  digitalWrite(2, 0x1);

  attachInterrupt(input1, input1RISING, 0x01);
  attachInterrupt(input2, input2RISING, 0x01);
}

void loop() {
  // put your main code here, to run repeatedly:
  MyDevice->locks_loop();
  MyDevice->GSM_loop();
  akc_loop_main();
  delay(100);
}
