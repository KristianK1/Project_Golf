#include"Battery_state.h"
#include"Location.h"
#include"codes.h"
#include"SIM800L_S2.h"
#include"Bluetooth_comm.h"
class Device_state{
private:
    Battery_state *MyBat;
    SIM800L_S2 *MyInt;
    int U1, U2, U3, U4;
    int akc;



public:

    void unlock(){

    }

    void lock(){
        
    }
    Device_state(int u1, int u2, int u3, int u4, int charging, int akc_pin, int GSM_powerpin, int GPS_powerpin){
        MyBat=new Battery_state(charging);
        MyInt= new SIM800L_S2();
        MyInt->setPowerpin(GPS_powerpin);
        GPS_power(GPS_powerpin, false);
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