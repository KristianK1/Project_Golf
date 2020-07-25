#include <SoftwareSerial.h>
#include"klase.h"
SoftwareSerial GSMSerial(10, 11);
SoftwareSerial GPSSerial(4,3);

int ulaz1=A1;
int ulaz2=A2;
int ulaz3=A3;

int input_time=0;
int istek_minute=3;
Koordinate trenutne_koor, prosle_koor, nove_koor;

Koordinate polje[10];

bool citanje_ulaza(){
  if(digitalRead(ulaz1)||digitalRead(ulaz2)||digitalRead(ulaz3)){
    input_time=millis();
    return HIGH;
  }
  else if(input_time-millis()<(istek_minute*60*1000)){
      return HIGH;
  }
  else
    return LOW;
}

void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  GPSSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(citanje_ulaza())
  {
    //new_koor=GPS_read();
    if(trenutne_koor!=nove_koor){
      prosle_koor=trenutne_koor;
      trenutne_koor=prosle_koor;
    }
  }
}
