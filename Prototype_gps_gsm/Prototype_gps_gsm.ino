#include "BluetoothSerial.h"
#include"SIM800_KK_ESP.h"
#include "Location.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//BluetoothSerial SerialBT;

#define N 5

String Link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&field1=";
int i=0;
SIM800L_KK *object;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial2.begin(9600); // connect gps sensor
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  
  object=new SIM800L_KK(); 
}
Location GPS(){
  Location p[N];
  for(int i=0;i<N;i++){
    Location new_data=Load_data_from_GPS();
    if(new_data.getX()!=181){
      SerialBT.println();
      SerialBT.println(new_data.getX());
      SerialBT.println(new_data.getY());
      p[i]=new_data;
    }  
    else i--;
  }
  Location Average=average(p,N);
  Location Sigma=sigma(p,N);
  if(Sigma.getX()<0.01 && Sigma.getY()<0.01 && Average.getX()!=181){ 
    //Location_print(Average);
    //Location_print(Sigma);   
    return Average;
  }
  return Location(181,91);
}

String loc_to_link(Location location){
  //String link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&status=http://maps.google.com/maps?q=loc:47.557240,18.719575";
  String link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&status=http://maps.google.com/maps?q=loc:";
  link=link+String(location.getY(),7)+","+String(location.getX(),7);
  
  return link;
}

void GSM(String link){
  object->setLink(link);
  int q=0;
  while(q!=1){
     q=object->access();
     if(q==0) SerialBT.println("\n\n\nExit code: Failed");
     if(q==1) SerialBT.println("\n\n\nExit code: Success");
     if(q==3) SerialBT.println("\n\n\nExit code: reset");
     delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Location current_loc=GPS();
  GSM(loc_to_link(current_loc)); //provjeri jel 181,91
  
  SerialBT.println("\n\n\n\n\n\n\n\n\n\nGOTOV LOOP");
  delay(1000);
}
