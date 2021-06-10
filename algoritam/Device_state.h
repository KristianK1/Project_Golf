#include "Location.h"
#define pi 3.14159265358979323846

class Device_state{
private:
    Location last_recorded_location;
    boolean state; //0=normal 1=ignore
    
    double degToRad(double deg){return deg/180*pi;}
public:
    Device_state(Location mLRS, boolean mState): last_recorded_location(mLRS), state(mState){}
    boolean getState(){ return state;}
    
    Location getLRL(){ return last_recorded_location; }
    
    void setLRL(Location newL){ last_recorded_location=newL;}
    void setState(boolean Nstate){ state=Nstate;}
    
    double distance(Location L){
        double distance_deg_X=L.getX()-last_recorded_location.getX();
        double distance_deg_Y=L.getY()-last_recorded_location.getY();

        double distance_km_X=distance_deg_X/180*pi*6371*cos(degToRad(last_recorded_location.getY()));
        double distance_km_Y=distance_deg_Y/180*pi*6371;
        
        return sqrt(distance_km_X*distance_km_X+distance_km_Y*distance_km_Y); //flat earth
    }
};