#include"Battery_state.h"
#include"codes.h"
#include"NEO_6M.h"
#include"SIM800L_S2.h"
#include"Bluetooth_comm.h"
class Device_state: Battery_state, SIM800L_S2, NEO_6M, codes, Bluetooth_comm {
private:
    bool GSM_isON, GPS_isON;
    
    int U1, U2, U3, U4;
    int akc;
    int lock_state; // 0 - unlocked, 1 - locked, else - unkown
    bool lock_changed;
    long int last_time_pushed;
    bool moving;
    bool stopped_moving;
    bool locks_attached=false;

    Location *last_sent;
    Location *current_location;

    bool first_block=false; //da samo jedanput attacha na pocetku (nakon 20 sekundi)
public:
    Device_state(int u1, int u2, int u3, int u4, int charging, int akc_pin, int GSM_powerpin, int GPS_powerpin): 
                    Battery_state(charging), SIM800L_S2(GSM_powerpin), NEO_6M(GPS_powerpin), codes(), Bluetooth_comm(){
        lock_changed=false;
        GSM_isON=false;
        GPS_isON=false;
        lock_state=2; // unkown if it is locked
        U1=u1;
        U2=u2;
        U3=u3;
        U4=u4;
        akc=akc_pin;
        pinMode(u1, INPUT);
        pinMode(u2, INPUT);
        pinMode(u3, INPUT);
        pinMode(u4, INPUT);
        pinMode(akc, INPUT);
        moving=false;
        stopped_moving=false;
        last_sent= new Location(-181,-91);
        current_location = new Location(181, 91);
        last_time_pushed=millis();
    }
    void GPS_power(bool state){
        if(GPS_isON!=state){
            GPS_isON=state;
            NEO_6M::GPS_power(state);
            Battery_state::setGPSstate(state); //battery    
        }
    }

    void GSM_power(bool state){
        if(GSM_isON!=state){
            GSM_isON=state;
            SIM800L_S2::GSM_power(state);
            Battery_state::setGSMstate(state);    
        }
    }

    void send_error_message(String message){
        Send_message(message);
    }

    void unlock(){
        if(lock_state!=0){
            lock_state=0; //unlocked
            
            send_error_message("otkljucan");
            lock_changed=true;
        }
    }

    void lock(){
        if(lock_state!=1){
            lock_state=1;
            send_error_message("zakljucan");
            lock_changed=true;
        }
    }

    int akc_loop(){
        //vraca nulu ako nista ne treba napravit
        //vraca jedan ako treba detachat
        //vraca dva ako treba attachat
        
        if(millis()<20*1000){
            return 0;
        }
        if(millis()>20*1000 && first_block==false){
            first_block=true;
            send_error_message("FIRST ATTACH");
            return 1; //ako se negdje u prvih 20 sekundi attachaju interupti jebiga onda
        }
        if(millis()-last_time_pushed>1.5*60*1000){
            moving=false;
            
            if(stopped_moving==true){
                stopped_moving=false;
                setCS(false);                
                *last_sent= Location(-181,-91);
                if(lock_state==false){
                    if(BT_state==0){
                        setLink(small_link(3));
                    }
                }
                else if(lightsState()==true){
                    if(BT_state==0){
                        setLink(small_link(2));
                    }
                }
            }


            //send_error_message("ponovno u stanju mirovanja");
            return 2;
        }
        if(millis()-last_time_pushed>5*1000){
            return 2;
        }
        return 0;
    }

    void setLastTimePushed(){
        last_time_pushed=millis();
        moving=true;
    }

    void locks_loop(){
        if(lock_changed){
            send_error_message("status brave promjenjen");
            if(lock_state==false){
                if(isMoveing()==false){
                    if(getBTstate()==0){
                        setLink(small_link(1));
                    }
                }
            }
            lock_changed=false;
        }
    }

    void GSM_loop(){
        if(getLink()!=""){
            //SerialBT->println("uso");
            if(GSM_isON==false){
                GSM_power(true);
                SerialBT->println("Upaljen GSM");
            }
            if(millis() - getAccessTimer()>50){
                access();
                setAccessTimer();
            }
        }
        GSM_autoshutdown();
    }
    
    bool link_exists(){
        return (getLink()!="");
    }
    
    void GPS_loop(){
        //Location A(18.715807,45.557249), B(18.719415, 45.557323);
        // double dd=distance(A,B);
        // send_error_message("udaljenost od damira do pocetka ulice:" + String(dd, DEC)+" km" );

      
        if(isMoveing()==false && get_GPS_power()==true){
            GPS_power(false);
        }
        if(isMoveing()){
            if(get_GPS_power()==false){
                GPS_power(true);
            }
            *current_location = GPS_data();
            if(getBTstate()==0){
                if(current_location->getX()<180 && current_location->getX()>-180){
                    send_error_message("Ocitana je nova lokacija");
                    //imamo novu lokaciju
                    double distance_new_last=distance(*last_sent, *current_location);
                    send_error_message("brzinaMINREAD:"+(String)current_location->getSpeed());
                    send_error_message("X:"+String(current_location->getX(),DEC));
                    send_error_message("Y:"+String(current_location->getY(),DEC));
                    
                    
                    double speed_RN=current_location->getSpeed();
                    send_error_message("udaljenost od zadnje:" + String(distance_new_last, DEC)+" km" );
                    double needed_distance;
                    send_error_message((String)speed_RN);
                    if(speed_RN<=7){
                        needed_distance=0.05;
                        send_error_message("less then 7kmh");
                    }
                    else if(speed_RN>7 && speed_RN<=60){
                        needed_distance=0.02*(speed_RN-7)+0.05;
                        send_error_message("between 7 and 60");
                    }
                    else if(speed_RN>60 && speed_RN<=100){
                        needed_distance=0.05*(speed_RN-60)+1.11;
                        send_error_message("between 60 and 100");
                    }
                    else if(speed_RN>100 && speed_RN<=160){
                        needed_distance=0.1*(speed_RN-100)+3.11;
                        send_error_message("between 100 and 160");
                    }
                    else{
                        send_error_message("above 160");
                        needed_distance=0.1*(160-100)+3.11;        
                    }
                    
                    if(distance_new_last > needed_distance){
                        if(link_exists()==false){
                            if(getBTstate()==0){
                                setLink(loc_to_link(current_location->getX(), current_location->getY(), 0));
                                *last_sent=*current_location;
                                send_error_message("setan je link na novu lokaciju");

                            }
                        }
                    }
                }
            }
        }
    }

    void Battery_loop(){
        update_CS(false);
        //send_error_message((String)(get_percentage()*1000));
    }
    void BT_loop(){
      Bluetooth_loop();
    }

    int getBTstate(){
        return BT_state;
    }

    void Wakeup_message(){
        setLink(small_link(4));
    }

    void Pushed_message(){
        setLink(small_link(5));
    }
    void GSM_autoshutdown_main(){
        GSM_power(false);
        if(GSM_isON)
        send_error_message("GSM_isON!!");
        else
        send_error_message("GSM_isOFF!!");
        
        
        SerialBT->println("GSM timeout turn off");
    }

    bool isMoveing(){ return moving; }

    bool lightsState(){
        send_error_message("stanje svjetala " + (String)(digitalRead(U3)^1));
        return digitalRead(U3)^1;
    }

    void setStoppedMoving(){
       stopped_moving=true; 
    }

    void setCS(bool state){
        set_CS(state);
    }
    void setLocksAttached(bool state){
        locks_attached=state; 
    }

    bool getLocksAttached(){
        return locks_attached;
    }
};
