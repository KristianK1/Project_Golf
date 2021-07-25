#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\NEO_6M.h"
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
                //SerialBT.println(gps.speed.kmph());
                new_location.setSpeed(gps.speed.kmph());
                GPS_non_double_timer=millis();
            }
            }
        }
        return new_location;
    }

public:
    NEO_6M(int pp){
        Serial.begin(9600);
        power_pin=pp;
        power_state=false;
        pinMode(power_pin, OUTPUT);
        digitalWrite(power_pin, LOW);
        new_locations = new Location[5];
        new_loc_counter=0;
    }
    virtual ~NEO_6M(){
        delete(new_locations);
    }
    int GPS_power(bool power){
        power_state=power;
        digitalWrite(power_pin, power_state);
    }

    bool get_power(){
        return power_state;
    }

    bool begin_colecting_data(){
        new_loc_counter=0;
        GPS_data();
    }
    
    Location GPS_data(){
        Location new_data=SingleGPSData();
        if(new_data.getX()!=181){
            new_locations[new_loc_counter]=new_data;
            new_loc_counter++;
        }
        if(new_loc_counter>=5){
            Location Average=average(new_locations,5);
            Location Sigma=sigma(new_locations,5);

            if(Sigma.getX()<0.01 && Sigma.getY()<0.01 && Average.getX()!=181){ 
                return Average;
            }
            else{
                new_loc_counter=0;
            }
        }
        
        return Location(181,91);
    }
};