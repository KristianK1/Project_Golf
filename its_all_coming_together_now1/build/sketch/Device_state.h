#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\Device_state.h"
#include"Battery_state.h"
#include"codes.h"
#include"NEO_6M.h"
#include"SIM800L_S2.h"
#include"Bluetooth_comm.h"
class Device_state{
private:
    Battery_state *MyBat;
    SIM800L_S2 *MyInt;
    NEO_6M *MyGPS;
    int U1, U2, U3, U4;
    int akc;
    int lock_state; // 0 - unlocked, 1 - locked, else - unkown


public:

    void unlock(){
        if(lock_state==1){
            lock_state=0; //unlocked
        }
    }

    void lock(){
        if(lock_state==0){
            lock_state=1; 
        }
    }
    Device_state(int u1, int u2, int u3, int u4, int charging, int akc_pin, int GSM_powerpin, int GPS_powerpin){
        lock_state=2; // unkown
        MyBat=new Battery_state(charging);
        MyInt= new SIM800L_S2();
        MyInt->setPowerpin(GSM_powerpin);
        MyGPS=new NEO_6M(GPS_powerpin);
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
};