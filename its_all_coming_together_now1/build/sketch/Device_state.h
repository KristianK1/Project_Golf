#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\Device_state.h"
#include"Battery_state.h"
#include"codes.h"
#include"NEO_6M.h"
#include"SIM800L_S2.h"
#include"Bluetooth_comm.h"
class Device_state: Battery_state, SIM800L_S2, NEO_6M, codes, Bluetooth_comm {
private:
    bool GSM_isON, GPS_isON;
    //Battery_state *MyBat;
    //SIM800L_S2 *MyInt;
    //NEO_6M *MyGPS;
    codes *MyCodes;
    int U1, U2, U3, U4;
    int akc;
    int lock_state; // 0 - unlocked, 1 - locked, else - unkown
    bool lock_changed;

public:

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
    Device_state(int u1, int u2, int u3, int u4, int charging, int akc_pin, int GSM_powerpin, int GPS_powerpin): 
                    Battery_state(charging), SIM800L_S2(GSM_powerpin), NEO_6M(GPS_powerpin), codes(), Bluetooth_comm(){
        lock_changed=false;
        GSM_isON=false;
        GPS_isON=false;
        lock_state=2; // unkown if it is locked
        //MyBat=new Battery_state(charging);
        
        //MyInt= new SIM800L_S2();
        //GSM_setPowerpin(GSM_powerpin);
        //MyGPS=new NEO_6M(GPS_powerpin);
        //MyCodes=new codes();
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
    
    void Device_loop(){
        if(lock_changed){
            if(lock_state==false){
                if(getBTstate()==0){
                    setLink(small_link(1));
                }
            }
            lock_changed=false;
        }


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
    void Wakeup_message(){
        setLink(small_link(4));
    }
    void GSM_autoshutdown_main(){
        GSM_power(false);
        SerialBT->println("GSM timeout turn off");
    }
};