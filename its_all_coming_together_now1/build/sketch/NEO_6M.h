#include"Location.h"

class NEO_6M{
protected:
    int power_pin;
    bool power_state;

    Location *new_locations;
    int new_loc_counter;

    unsigned long int GPS_non_double_timer;
    unsigned long int overflow_detector=-5000;

    void GPS_data_reset(){
        Serial.flush();
    }

    Location SingleGPSData(){
        //Serial.flush();
        Location new_location(181,91);
        //delay(1000);
        while(Serial.available() > 0){ 
            if (gps.encode(Serial.read()) && gps.location.age()<5000){
            if((millis()-GPS_non_double_timer)>1000 || (millis()>overflow_detector)){
                new_location.setX(gps.location.lng());
                new_location.setY(gps.location.lat());
                send_error_message("nova lokacija");
                new_location.setSpeed(gps.speed.kmph());
                GPS_non_double_timer=millis();
            }
            }
        }
        return new_location;
    }

public:
    virtual void send_error_message(String message) = 0;
    NEO_6M(int pp){
        Serial.begin(9600);
        power_pin=pp;
        power_state=false;
        pinMode(power_pin, OUTPUT);
        digitalWrite(power_pin, HIGH); //ugasi na pocetku
        new_locations = new Location[5];
        new_loc_counter=0;
    }
    virtual ~NEO_6M(){
        delete(new_locations);
    }
    int GPS_power(bool power){
        power_state=power;

        if(power==false){
            new_loc_counter=0;
        }
        if(power==true) send_error_message("GPS upaljen");
        else send_error_message("GPS ugasen");
        digitalWrite(power_pin, power_state^1);
    }

    bool get_GPS_power(){
        return power_state;
    }

    bool begin_colecting_data(){
        new_loc_counter=0;
        GPS_data();
    }
    
    Location GPS_data(){
        Location new_data=SingleGPSData();
        if(new_data.getX()!=181){
            send_error_message("dobro mjerenje");
            new_locations[new_loc_counter]=new_data;
            new_loc_counter++;
            String error=(String)new_loc_counter;
            for(int i=0;i<4;i++) error+=error;
            send_error_message(error);
        }
        
        if(new_loc_counter>=5){
            Location Average=average(new_locations,5);
            double minSpeed=new_locations[0].getSpeed();
            for(int i=0;i<new_loc_counter;i++){
                send_error_message((String)new_locations[i].getSpeed());
              if(minSpeed>new_locations[i].getSpeed()){
                minSpeed=new_locations[i].getSpeed();
              }
            }
            send_error_message("speedmin"+(String)minSpeed);
            Average.setSpeed(minSpeed);
            send_error_message("speedmin"+(String)Average.getSpeed());
            Location Sigma=sigma(new_locations,5);
            if(Sigma.getX()<0.01 && Sigma.getY()<0.01 && Average.getX()!=181){ 
                new_loc_counter=0;
                send_error_message("prihvaena mjerenja");
                return Average;
            }
            else{
                new_loc_counter=0;
                send_error_message("odbijena mjerenja");
            }
        }
        
        return Location(181,91);
    }
};
