#include "Location.h"
#define N 5
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial2.begin(9600); // connect gps sensor
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Location p[N];
  for(int i=0;i<N;i++){
    Location new_data=Load_data_from_GPS();
    if(new_data.getX()!=181){
      Serial.println();
      Serial.println(new_data.getX());
      Serial.println(new_data.getY());
      p[i]=new_data;
    }  
    else i--;
  }
  Location Average=average(p,N);
  Location Sigma=sigma(p,N);
  if(Sigma.getX()<0.01 && Sigma.getY()<0.01){ 
    Location_print(Average);
    Location_print(Sigma);   
  }
    while(1);
}
