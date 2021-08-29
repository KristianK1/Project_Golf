class Battery_state{
protected:
  //CS == Charging state
  bool CS;
  
  double TOTAL_CHARGE=10.0*3.7/5*0.8;
  double CHARGING_CURRENT=0.95*0.85;
  double GSM_discharge=0.33;
  double GPS_discharge=0.045;
  double BASE_discharge=0.11;

  double initial_charge;
  double current_charge;
  int Charge_pin;
  long unsigned int timer;

  bool GPS_state;
  bool GSM_state;

  
public:
  Battery_state(int pin){
    Charge_pin=pin;
    pinMode(Charge_pin, OUTPUT);
    CS=false;
    digitalWrite(Charge_pin, LOW);
    initial_charge=0.1*TOTAL_CHARGE;
    current_charge=initial_charge;
    timer=millis();
    GPS_state=false;
    GSM_state=false;
  }

  virtual ~Battery_state(){}

  void setGPSstate(bool s){
    update_CS(true);
    GPS_state=s;
  }

  void setGSMstate(bool s){
    update_CS(true);
    GSM_state=s;
  }
  double get_percentage(){
    return current_charge/TOTAL_CHARGE*100;
  }
  bool get_CS(){
    return CS;
  }
  void set_CS(bool state){
    update_CS(true);
    digitalWrite(Charge_pin, state);
    CS=state;
  }
  
  int update_CS(bool important){
    if(important==false){
      if(millis()-timer<5000) return 0; //manje od 5 sekundi nemoj nista zbog pogreske malog diferecijala
    }
    if(millis()-timer>1800000){
      current_charge=initial_charge;
      send_error_message("too much time");
      return 2; //previse je vremena proslo od updatanja, trebalo bi sendat error na GSM 30*60*1000 = 1.800.000
    }
    current_charge-=(millis()-timer)*0.001/60/60*BASE_discharge;
    if(GPS_state){
      //send_error_message("GPS is on");
      current_charge-=(millis()-timer)*0.001/60/60*GPS_discharge;
    }
    if(GSM_state){
      //send_error_message("GSM is on");
      current_charge-=(millis()-timer)*0.001/60/60*GSM_discharge;  
    }
    if(CS){
      //send_error_message("charging");
      current_charge+=(millis()-timer)*0.001/60/60*CHARGING_CURRENT;
    }
    if(current_charge>TOTAL_CHARGE) current_charge=TOTAL_CHARGE;

    if(current_charge<0.3*TOTAL_CHARGE){
      if(get_CS()==false){
        CS=true;
      }
      send_error_message("EMPTY BATTERY");  
    }
    if(current_charge>0.99*TOTAL_CHARGE){
      if(get_CS()==true){
        set_CS(false);
      }
    }
    timer=millis();
    //send_error_message((String)(current_charge*1000000));
  }
  
  
  virtual void send_error_message(String message) = 0;
    
};
