# 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino"
# 2 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\its_all_coming_together_now1.ino" 2
Device_state *MyDevice;
int input1=19;
int input2=21;
int input3=22;
int input4=23;
int charge_pp;
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

}

void setup() {
  // put your setup code here, to run once:
  MyDevice=new Device_state(input1, input2, input3, input4, charge_pp, push_p, GSM_pp, GPS_pp);
  attachInterrupt(input1, input1RISING, 0x01);
  attachInterrupt(input2, input2RISING, 0x01);
  attachInterrupt(push_p, pushed, 0x01);
  MyDevice->Wakeup_message();
  delay(5000);
  pinMode(2, 0x02);
  digitalWrite(2, 0x1);


}

void loop() {
  // put your main code here, to run repeatedly:
  MyDevice->Device_loop();
}
