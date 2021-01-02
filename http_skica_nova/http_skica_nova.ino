#include"SIM800L_KK.h"

String Link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&field1=";
int i=0;
SIM800L_KK *object;


void setup() {
  // put your setup code here, to run once:
  object=new SIM800L_KK(4,5); 
  Serial.begin(9600);
}

void loop() {
  object->setLink(Link+String(i));
  int q=object->access();
  if(1==q){
    i++;
    Serial.println("Uspjesno poslano");
    delay(10000);
  }
  //if(q==2) Serial.println("ne jos");
  if(q==0) {
    Serial.println("Failed");
    delay(10000);
  }
  if(q==3) Serial.println("reset");
  delay(100);
}
