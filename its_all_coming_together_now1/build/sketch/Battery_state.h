#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\Battery_state.h"
class Battery_state{
private:
  //CS == Charging state
  bool CS;
  
  float TOTAL_CHARGE=10.0*3.7/5*0.8;
  float CHARGING_CURRENT=0.95*0.85;
  float GSM_discharge=0.33;
  float GPS_discharge=0.045;
  float BASE_discharge=0.11;

  float initial_charge;
  float current_charge;
  int Charge_pin;
  long unsigned int timer;

  bool GPS_state;
  bool GSM_state;
  
  String message;

  bool expand_message(String addmess){
    message+=millis() + addmess;
  }
public:
  Battery_state(int pin){
    Charge_pin=pin;
    pinMode(Charge_pin, OUTPUT);
    digitalWrite(Charge_pin, LOW);
    initial_charge=0.1*TOTAL_CHARGE;
    timer=millis();
    GPS_state=false;
    GSM_state=false;
    message="";
  }
  void setGPSstate(bool s){
    update_CS();
    GPS_state=s;
  }
  void setGSMstate(bool s){
    update_CS();
    GSM_state=s;
  }
  float get_percentage(){
    return current_charge/TOTAL_CHARGE;
  }
  bool get_CS(){
    return CS;
  }
  void set_CS(boolean state){
    update_CS();
    digitalWrite(Charge_pin, state);
    CS=state;
  }
  
  int update_CS(){
    if(millis()-timer<5000) return 0; //manje od 5 sekundi nemoj nista zbog pogreske malog diferecijala
    if(millis()-timer>1800000){
      current_charge=initial_charge;
      return 2; //previse je vremena proslo od updatanja, trebalo bi sendat error na GSM 30*60*1000 = 1.800.000
    }
    current_charge-=(millis()-timer)*0.001/60/60*BASE_discharge;
    if(GPS_state){
      current_charge-=(millis()-timer)*0.001/60/60*GPS_discharge;
    }
    if(GSM_state){
      current_charge-=(millis()-timer)*0.001/60/60*GSM_discharge;  
    }
    if(CS){
      current_charge+=(millis()-timer)*0.001/60/60*CHARGING_CURRENT;
    }
    if(current_charge>TOTAL_CHARGE) current_charge=TOTAL_CHARGE;
  }


};
