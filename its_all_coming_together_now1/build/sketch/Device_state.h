#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\Device_state.h"
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
        digitalWrite(u1, INPUT);
        digitalWrite(u2, INPUT);
        digitalWrite(u3, INPUT);
        digitalWrite(u4, INPUT);
        digitalWrite(akc, INPUT);
        moving=false;
        last_sent= new Location(-181,-91);
        current_location = new Location(181,91);
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
            lock_changed=true;
        }
    }

    void lock(){
        if(lock_state!=1){
            lock_state=1;
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
        if(millis()-last_time_pushed>60*1000){
            moving=false;
            send_error_message("ponovno u stanju mirovanja");
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
            if(lock_state==false){
                if(getBTstate()==0){
                    setLink(small_link(1));
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
            access();
            delay(50);
        }
        GSM_autoshutdown();
    }
    
    bool link_exists(){
        return (getLink()!="");
    }
    
    void GPS_loop(){
        if(isMoveing()){
            if(get_GPS_power()==false){
                GPS_power(true);
            }

        }

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
};