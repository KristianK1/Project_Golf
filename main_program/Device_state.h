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
    long int first_time_pushed;
    long int last_time_pushed;
    bool moving;
    bool stopped_moving;
    bool locks_attached=false;

    Location *last_sent;
    Location *current_location;
    Location *last_saved;
    String location_buffer;

    bool first_block=false; //da samo jedanput attacha na pocetku (nakon 20 sekundi)

    int powerSupply_12V_lastState = -1;
    long int powerSupply_12V_lastChecked;

public:
    Device_state(int u1, int u2, int u3, int u4, int charging, int akc_pin, int GSM_powerpin, int GPS_powerpin): 
                    Battery_state(charging, u1), SIM800L_S2(GSM_powerpin), NEO_6M(GPS_powerpin), codes(), Bluetooth_comm(){
        lock_changed=false;
        GSM_isON=false;
        GPS_isON=false;
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
        last_saved = new Location(181,91);

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

    int akc_loop(){
        //vraca nulu ako nista ne treba napravit
        //vraca jedan ako treba detachat
        //vraca dva ako treba attachat
        
        if(millis()<3*1000){
            return 0;
        }
        if(millis()>3*1000 && first_block==false){
            first_block=true;
            send_error_message("FIRST ATTACH");
            return 1; //ako se negdje u prvih 20 sekundi attachaju interupti jebiga onda
        }
        if(millis()-last_time_pushed>2*60*1000){ //idealno 2.5 minute
            moving=false;
            
            if(stopped_moving==true){
                stopped_moving=false;
                first_time_pushed = 0;
                send_error_message("ponovno u stanju mirovanja");
                //setCS(false);                
                *last_sent= Location(-181,-91);
            }
            return 2;
        }
        if(millis()-last_time_pushed>7*1000){
            return 2;
        }
        return 0;
    }

    void setLastTimePushed(){
        if(moving == false){
            first_time_pushed = millis();
        }
        last_time_pushed=millis();
        if(last_time_pushed - first_time_pushed > 1000 * 60 * 15){
            set_CS(true);
        }
        moving=true;
    }

    void GSM_loop(){
        if(getLink()!=""){
            //SerialBT->println("uso");
            if(GSM_isON==false){
                GSM_power(true);
                SerialBT->println("Upaljen GSM");
            }
            if(millis() - getAccessTimer()>100){
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

        // if(isMoveing()==false && get_GPS_power()==true){
        //     GPS_power(false);
        // }
        if(isMoveing()){
            // if(get_GPS_power()==false){
            //     GPS_power(true);
            // }
            *current_location = GPS_data();
            if(getBTstate()==0){
                if(current_location->getX()<180 && current_location->getX()>-180){
                    double distance_new_last=distance(*last_sent, *current_location);
                    double distance_new_last_saved = distance(*last_saved, *current_location);
                    
                    send_error_message("\nPocetak obrade GPS lokacije");
                    double speed_RN=current_location->getSpeed();
                    send_error_message("udaljenost od zadnje spremljene:" + String(distance_new_last_saved, DEC)+" km" );
                    send_error_message("udaljenost od zadnje poslane:" + String(distance_new_last, DEC)+" km" );
                    
                    double needed_distance;
                    send_error_message("Trenutna brzina: " + (String)speed_RN);
                    if(speed_RN<=7){
                        needed_distance=0.05;
                        //send_error_message("less then 7kmh");
                    }
                    else if(speed_RN>7 && speed_RN<=60){
                        needed_distance=0.013*(speed_RN-7)+0.05;
                        //send_error_message("between 7 and 60");
                    }
                    else if(speed_RN>60 && speed_RN<=100){
                        needed_distance=0.04*(speed_RN-60)+0.74;
                        //send_error_message("between 60 and 100");
                    }
                    else if(speed_RN>100 && speed_RN<=150){
                        needed_distance=0.07*(speed_RN-100)+2.34;
                        //send_error_message("between 100 and 150");
                    }
                    else{
                        //send_error_message("above 150");
                        needed_distance=5.84;          
                    }
                
                    send_error_message("da posalje: " + String(distance_new_last/needed_distance*100,DEC) + "%");
                    if(distance_new_last > needed_distance && link_exists()==false && SIM800L_S2::access_ok()){
                        //send_error_message("prije provjere <5");
                        send_error_message(location_buffer);
                        //send_error_message("duzina buffera: " + String(location_buffer.length(), DEC) + " slova");
                        
                        
                        if(location_buffer.length()<2){
                            setLink(loc_to_link(current_location->getX(), current_location->getY(), 0));
                            *last_sent=*current_location;
                            *last_saved = *current_location;
                            send_error_message("setan je link na novu lokaciju");
                            location_buffer = "";    
                        }
                        else{
                            if(distance(*last_saved, *current_location)<0.05){ //da pri "paljenju auta" ne posalje dvije "iste" lokacije
                                location_buffer += big_packet(current_location->getX(), current_location->getY(),0);
                            }
                            setLink(string_to_link(location_buffer));
                            send_error_message("(vise njih) Setan je link na " + location_buffer);
                            *last_sent = *current_location;
                            *last_saved = *current_location;
                            location_buffer ="";
                        }
                    }
                    else if((distance_new_last_saved > (needed_distance/5)) && distance_new_last_saved>0.05){
                        //save_to_string
                        *last_saved = *current_location;
                        send_error_message("sejvana lokacija za kasnije");  
                        location_buffer += big_packet(current_location->getX(), current_location->getY(),0);
                        location_buffer += '*';
                        send_error_message(location_buffer);
                        
                    }
                }
            }
        }
        else location_buffer = "";
    }
    

    void Battery_loop(){
        update_CS(false);
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
        if(SIM800L_S2::access_ok()){
            setLink(small_link(5));
        }
        else{
            send_error_message("Preblizu prethodnog slanja");
        }
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

    // bool lightsState(){
    //     send_error_message("stanje svjetala " + (String)(digitalRead(U3)^1));
    //     return (digitalRead(U3)^1);
    // }

    void setStoppedMoving(){
       stopped_moving=true; 
    }

    void setCS(bool state){
        Battery_state::set_CS(state);
    }

    void setLocksAttached(bool state){
        locks_attached=state; 
    }

    bool getLocksAttached(){
        return locks_attached;
    }

    double device_get_percentage(){
        return get_percentage();
    }

    void begin_charging_on_request(){
        Battery_state::set_percentage_low();
    }
    
    void setBatteryX(){
        Battery_state::set_battery_to_above_charging();
    }

    void check12V_loop(){
        if(millis() - powerSupply_12V_lastChecked > 60 * 1000) {   //1 minute
            bool newState = check12V_availability();
            if(powerSupply_12V_lastState == -1){
                //nije izmjereno nikada
                if(newState){
                    //ima struje, sve okej
                }
                else{
                    //nema struje, nista okej
                    if(getLink()!=""){
                        setLink(small_link(6));
                    }
                    else{
                        return;
                    }
                }
            }
            else if(powerSupply_12V_lastState == 0){
                if(newState){
                    //bratilo se nazad
                }
                else{
                    //ostalo isto -> nema struje
                }
            }
            else if(powerSupply_12V_lastChecked == 1){
                if(newState){
                    // ostalo isto -> ima struje
                }
                else{
                    //otisla struja
                    if(getLink()!=""){
                        setLink(small_link(6));
                    }
                    else{

                    }
                }
            }
            powerSupply_12V_lastChecked = newState;
        } 
    }

    bool check12V_availability(){
        return (digitalRead(Battery_state::Charge_pin)^1); //flip because of the shematic
    }
};
