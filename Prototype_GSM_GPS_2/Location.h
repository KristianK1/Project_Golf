#include <TinyGPS++.h>
TinyGPSPlus gps;

class Location{
  friend Location operator+(Location lhs, Location rhs);
  friend Location operator-(Location lhs, Location rhs);
  friend Location operator*(Location lhs, Location rhs);
  friend Location operator/(Location lhs, int rhs);
private:
  double X;  //  <-180,180]
  double Y;  //   [-90,90]
  double speed_kmh;
public:
  Location(double mX, double mY): X(mX), Y(mY){}
  Location(const Location &mLoc){
    this->X=mLoc.X;
    this->Y=mLoc.Y;
  }
  Location(){
    X=0;
    Y=0;
    speed_kmh=0;
  }
  void setX(double mX){
    X=mX;
  }
  void setY(double mY){
    Y=mY;
  }
  void setSpeed(double mSpeed){
    speed_kmh=mSpeed;
  }
  double getX(){
    return X;
  }
  double getY(){
    return Y;
  }
  double getSpeed(){
    return speed_kmh ;
  }
  void prefix(){
    while(this->getX()>180){
      this->setX(this->getX()-360);
    }
    while(this->getX()<=-180){
      this->setX(this->getX()+360);
    }
    
    while(this->getY()>90){
      this->setX(this->getX()-180);
    }
    while(this->getY()<-90){
      this->setY(this->getY()+180);
    }
  }
};


Location operator+(Location lhs, Location rhs){
  Location sum;
  sum.setX(lhs.getX()+rhs.getX());
  sum.setY(lhs.getY()+rhs.getY());
  return sum;
}

Location operator-(Location lhs, Location rhs){
  rhs.setX(-1*rhs.getX());
  rhs.setY(-1*rhs.getY());
  return lhs+rhs;
}


Location operator*(Location lhs, Location rhs){
  Location result;
  result.setX(lhs.getX()*rhs.getX());
  result.setY(lhs.getY()*rhs.getY());
  return result;
}

Location operator/(Location lhs, int rhs){
  Location result;
  result.setX(lhs.getX()/rhs);
  result.setY(lhs.getY()/rhs);
  return result;
}

Location sqrtt(Location input){
  input.setX(sqrt(input.getX()));
  input.setY(sqrt(input.getY()));
  return input;
}

Location abss(Location input){  
  input.setX(input.getX()*(input.getX()>0? 1:-1));
  input.setY(input.getY()*(input.getY()>0? 1:-1));
  return input;
}

Location average(Location *p, int n){  
  if(n<=0) return Location(181,91);

  Location sum;
  for(int i=0;i<n;i++){
    sum.setX(sum.getX()+p[i].getX()/n);
    sum.setY(sum.getY()+p[i].getY()/n);
    sum.setSpeed(sum.getSpeed()+p[i].getSpeed()/n);
  }
  sum.prefix();
  return sum;
}

Location sigma(Location *p, int n){
  if(n<=1) return Location(181,91);
  Location Average=average(p,n);
  Location sigma(0,0);
  
  for(int i=0;i<n;i++){
    Location new_data;
    if(n>=30) new_data=((p[i]-Average)*(p[i]-Average))/n;
    if(n<30) new_data=((p[i]-Average)*(p[i]-Average))/(n-1);

    //Serial.println(new_data.getX());
    sigma=sigma+new_data;
  }
  try{
    sigma=sqrtt(sigma);
  }
  catch(String str){
    SerialBT.println(str);
    return Location(181,91);
  }
  return sigma;
}

void GPS_data_reset(){
  Serial.flush();
}


unsigned long int GPS_non_double_timer;
unsigned long int overflow_detector=-5000;
Location Load_data_from_GPS(){
  //Serial.flush();
  Location new_location(181,91);
  //delay(1000);
  while(Serial.available() > 0){ 
    if (gps.encode(Serial.read()) && gps.location.age()<5000){
      if((millis()-GPS_non_double_timer)>1000 || (millis()>overflow_detector)){
        new_location.setX(gps.location.lng());
        new_location.setY(gps.location.lat());
        SerialBT.println(gps.speed.kmph());
        new_location.setSpeed(gps.speed.kmph());
        GPS_non_double_timer=millis();
      }
    }
  }
  return new_location;
}

Location GPS(){
  Location *p=new Location [10];
  for(int i=0;i<10;i++){
    Location new_data=Load_data_from_GPS();
    if(new_data.getX()!=181){
      SerialBT.println();
      SerialBT.println(new_data.getX());
      SerialBT.println(new_data.getY()); 
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

/*void Location_print(Location x){
  SerialBT.println();
  SerialBT.println(x.getX(),8);
  SerialBT.println(x.getY(),8);
  
}*/
