#line 1 "c:\\Users\\Kristian\\Documents\\GitHub\\Project_Golf\\its_all_coming_together_now1\\NEO_6M.h"
#include"Location.h"

class NEO_6M{
private:
    int power_pin;
    bool power_state;

    unsigned long int GPS_non_double_timer;
    unsigned long int overflow_detector=-5000;

    void GPS_data_reset(){
        Serial.flush();
    }
public:
    NEO_6M(int pp){
        power_pin=pp;
        pinMode(power_pin, OUTPUT);
        digitalWrite(power_pin, LOW);
    }

    int GPS_power(bool power){
        power_state=power;
        digitalWrite(power_pin, power_state);
    }

    bool get_power(){
        return power_state;
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


    /*void Location_print(Location x){
    SerialBT.println();
    SerialBT.println(x.getX(),8);
    SerialBT.println(x.getY(),8);
    }*/
 

    Location GPS_data(){
        Location *p=new Location [10];
        for(int i=0;i<10;i++){
            Location new_data=SingleGPSData();
            if(new_data.getX()!=181){
            //SerialBT.println();
            //SerialBT.println(new_data.getX());
            //SerialBT.println(new_data.getY()); 
            p[i]=new_data;
            }  
            else i--;
        }
        Location Average=average(p,5);
        Location Sigma=sigma(p,5);
        if(Sigma.getX()<0.01 && Sigma.getY()<0.01 && Average.getX()!=181){ 
            return Average;
        }
        return Location(181,91);
        }
};